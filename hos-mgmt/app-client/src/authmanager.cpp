#include "src/authmanager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QHostAddress>

// 假设 authmanager.h 中有：
// QTcpSocket m_socket;
// QNetworkAccessManager m_nam;
// QString m_apiBase = "http://127.0.0.1:8080";
// bool m_isAuthenticated = false;
// int m_userId = 0;
// int m_remainingAttempts = 5;

AuthManager::AuthManager(QObject *parent)
    : QObject(parent),
    m_apiBase(QStringLiteral("http://127.0.0.1:8080")),
    m_isAuthenticated(false),
    m_userId(0),
    m_remainingAttempts(5)
{
    // TCP socket 连接（可选，保留以兼容原先 TCP 实现）
    connect(&m_socket, &QTcpSocket::readyRead, this, &AuthManager::onReadyRead);
    connect(&m_socket, &QTcpSocket::connected, this, &AuthManager::onConnected);
    connect(&m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &AuthManager::onErrorOccurred);

    // HTTP: QNetworkAccessManager 不需要额外连接（使用 lambda 回调）
    // 你可以选择注释掉下面这行，如果不想默认建立 TCP 连接：
    // m_socket.connectToHost(QHostAddress("127.0.0.1"), 8080);
}

// ------------------------- TCP-style requests (older) -------------------------

// 如果你头文件声明了使用 UserType 的接口，保留并实现（优先走 TCP，如果未连接则回退到 HTTP）。
void AuthManager::requestLogin(UserType userType, const QString &username, const QString &password)
{
    QJsonObject request;
    request["type"] = "login";
    request["userType"] = (userType == Patient) ? "patient" : "doctor";
    request["username"] = username;
    request["password"] = password;

    QJsonDocument doc(request);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);

    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write(payload);
        m_socket.flush();
        qDebug() << "AuthManager: sent login over TCP";
    } else {
        // TCP 未连接：退回到 HTTP POST
        qDebug() << "AuthManager: TCP not connected, using HTTP fallback for login";
        // reuse HTTP variant; convert userType to string
        requestLogin(username, password); // This will call the HTTP string-based login
    }
}

void AuthManager::requestRegister(UserType userType, const QString &username, const QString &password,
                                  const QString &phone, const QString &address, int age, const QString &gender)
{
    QJsonObject request;
    request["type"] = "register";
    request["userType"] = (userType == Patient) ? "patient" : "doctor";
    request["username"] = username;
    request["password"] = password;
    request["phone"] = phone;
    request["address"] = address;
    request["age"] = age;
    request["gender"] = gender;

    QJsonDocument doc(request);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);

    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write(payload);
        m_socket.flush();
        qDebug() << "AuthManager: sent register over TCP";
    } else {
        qDebug() << "AuthManager: TCP not connected, using HTTP fallback for register";
        // call HTTP-string variant
        requestRegister((userType == Patient) ? QStringLiteral("patient") : QStringLiteral("doctor"),
                        username, password, phone, address, age, gender);
    }
}

// ------------------------- HTTP-style requests (QNetworkAccessManager) -------------------------

// requestRegister with string userType (HTTP)
void AuthManager::requestRegister(const QString &userType, const QString &username, const QString &password,
                                  const QString &phone, const QString &address, int age, const QString &gender)
{
    QJsonObject obj;
    obj["username"] = username;
    obj["password"] = password;
    obj["userType"] = userType;
    obj["phone"]    = phone;
    obj["address"]  = address;
    obj["age"]      = age;
    obj["gender"]   = gender;

    QJsonDocument doc(obj);
    QNetworkRequest req(QUrl(m_apiBase + "/api/auth/register"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_nam.post(req, doc.toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "register network error:" << reply->errorString();
            emit registerFailed(reply->errorString());
            return;
        }
        QByteArray data = reply->readAll();
        QJsonDocument d = QJsonDocument::fromJson(data);
        if (!d.isObject()) {
            emit registerFailed("响应格式错误");
            return;
        }
        QJsonObject o = d.object();
        if (o.value("success").toBool()) {
            emit registerSuccess();
        } else {
            emit registerFailed(o.value("reason").toString("注册失败"));
        }
    });
}

// requestLogin string-based (HTTP)
void AuthManager::requestLogin(const QString &username, const QString &password)
{
    QJsonObject obj;
    obj["username"] = username;
    obj["password"] = password;

    QJsonDocument doc(obj);
    QNetworkRequest req(QUrl(m_apiBase + "/api/auth/login"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_nam.post(req, doc.toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "login network error:" << reply->errorString();
            emit loginFailed(reply->errorString());
            return;
        }
        QByteArray data = reply->readAll();
        QJsonDocument d = QJsonDocument::fromJson(data);
        if (!d.isObject()) {
            emit loginFailed("响应格式错误");
            return;
        }
        QJsonObject o = d.object();
        if (!o.value("success").toBool()) {
            emit loginFailed(o.value("reason").toString("登录失败"));
            return;
        }
        // 登录成功 (HTTP)
        m_isAuthenticated = true;
        emit isAuthenticatedChanged();
        m_userId = o.value("userId").toInt();
        QString userType = o.value("userType").toString();
        // emit both forms if available
        emit loginSuccess(m_userId, userType);
        if (userType == QStringLiteral("patient"))
            emit loginSuccess(Patient);
        else if (userType == QStringLiteral("doctor"))
            emit loginSuccess(Doctor);
    });
}

// ------------------------- Health submit (HTTP) -------------------------

void AuthManager::submitHealthData(double heightCm, double weightKg, int lungMl, const QString &bp)
{
    if (!m_isAuthenticated || m_userId <= 0) {
        emit healthSubmitFailed("未登录或 userId 无效");
        return;
    }
    QJsonObject obj;
    obj["userId"] = m_userId;
    obj["height"] = heightCm;
    obj["weight"] = weightKg;
    obj["lung"]   = lungMl;
    obj["bp"]     = bp;

    QJsonDocument doc(obj);
    QNetworkRequest req(QUrl(m_apiBase + "/api/health/submit"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_nam.post(req, doc.toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "health submit error:" << reply->errorString();
            emit healthSubmitFailed(reply->errorString());
            return;
        }
        QByteArray data = reply->readAll();
        QJsonDocument d = QJsonDocument::fromJson(data);
        if (!d.isObject()) {
            emit healthSubmitFailed("响应格式解析错误");
            return;
        }
        QJsonObject o = d.object();
        if (!o.value("success").toBool()) {
            emit healthSubmitFailed(o.value("reason").toString("提交失败"));
            return;
        }
        double bmi = o.value("bmi").toDouble();
        QString lungLevel = o.value("lungLevel").toString();
        QString bpLevel = o.value("bpLevel").toString();
        QString overall = o.value("overall").toString();
        emit healthSubmitSuccess(bmi, lungLevel, bpLevel, overall);
    });
}

// ------------------------- TCP socket helpers -------------------------

void AuthManager::onConnected()
{
    qDebug() << "Connected to server (TCP).";
}

void AuthManager::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qDebug() << "Socket error:" << m_socket.errorString();
    emit loginFailed("无法连接到服务器");
}

void AuthManager::onReadyRead()
{
    QByteArray data = m_socket.readAll();
    // TCP 回来的 JSON 我们直接解析并复用 processResponseObject
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) {
        emit loginFailed("服务器响应格式错误");
        return;
    }
    QJsonObject resp = doc.object();
    processResponseObject(resp);
}

// 统一处理来自 TCP/HTTP 的响应 JSON 对象
void AuthManager::processResponseObject(const QJsonObject &resp)
{
    QString type = resp.value("type").toString();
    bool success = resp.value("success").toBool();
    QString reason = resp.value("reason").toString();

    if (type == "login") {
        if (success) {
            // 如果服务端返回 userId/userType，优先使用
            m_isAuthenticated = true;
            emit isAuthenticatedChanged();

            if (resp.contains("userId"))
                m_userId = resp.value("userId").toInt();

            QString userTypeStr = resp.value("userType").toString();
            if (!userTypeStr.isEmpty()) {
                emit loginSuccess(m_userId, userTypeStr);
                if (userTypeStr == "patient")
                    emit loginSuccess(Patient);
                else if (userTypeStr == "doctor")
                    emit loginSuccess(Doctor);
            } else {
                // 如果 server 没返回字符串型 userType，尝试从 boolean/其它字段推断（兼容旧协议）
                bool isPatient = (resp.value("userType").toString() == "patient");
                emit loginSuccess(isPatient ? Patient : Doctor);
            }
        } else {
            // 失败：可能返回 remainingAttempts
            int rem = resp.value("remainingAttempts").toInt(m_remainingAttempts);
            setRemainingAttempts(rem);
            emit loginFailed(reason);
        }
    } else if (type == "register") {
        if (success) {
            emit registerSuccess();
        } else {
            emit registerFailed(reason);
        }
    } else if (type == "health_submit") {
        if (success) {
            double bmi = resp.value("bmi").toDouble();
            QString lungLevel = resp.value("lungLevel").toString();
            QString bpLevel = resp.value("bpLevel").toString();
            QString overall = resp.value("overall").toString();
            emit healthSubmitSuccess(bmi, lungLevel, bpLevel, overall);
        } else {
            emit healthSubmitFailed(reason);
        }
    } else {
        qDebug() << "Unknown response type:" << type;
    }
}

// ------------------------- utility -------------------------

void AuthManager::setRemainingAttempts(int attempts)
{
    if (m_remainingAttempts != attempts) {
        m_remainingAttempts = attempts;
        emit remainingAttemptsChanged();
    }
}

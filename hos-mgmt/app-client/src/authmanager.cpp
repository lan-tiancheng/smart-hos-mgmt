#include "authmanager.h"
#include <QJsonDocument>
#include <QUrl>
#include <QDebug>
#include <QNetworkRequest>
#include <QTimer>

// ------------------------- 构造函数 -------------------------

AuthManager::AuthManager(QObject *parent)
    : QObject(parent)
{
    connect(&m_socket, &QTcpSocket::readyRead, this, &AuthManager::onReadyRead);
    connect(&m_socket, &QTcpSocket::connected, this, &AuthManager::onConnected);
    connect(&m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &AuthManager::onErrorOccurred);
}

// ------------------------- 配置 -------------------------

void AuthManager::setApiBase(const QString &url)
{
    m_apiBase = url;
    qDebug() << "AuthManager: API base set to" << m_apiBase;
}

// ------------------------- TCP 请求（内部） -------------------------

void AuthManager::requestLogin(UserType userType, const QString &username, const QString &password)
{
    if (m_socket.state() != QAbstractSocket::ConnectedState) {
        emit loginFailed("无法连接到服务器。");
        return;
    }

    QJsonObject request;
    request["type"] = "login";
    request["userType"] = (userType == Patient) ? "patient" : "doctor";
    request["username"] = username;
    request["password"] = password;

    sendTcpJson(request);
}

void AuthManager::requestRegister(UserType userType, const QString &username, const QString &password,
                                  const QString &phone, const QString &address, int age, const QString &gender)
{
    if (m_socket.state() != QAbstractSocket::ConnectedState) {
        emit registerFailed("无法连接到服务器。");
        return;
    }

    QJsonObject request;
    request["type"] = "register";
    request["userType"] = (userType == Patient) ? "patient" : "doctor";
    request["username"] = username;
    request["password"] = password;
    request["phone"] = phone;
    request["address"] = address;
    request["age"] = age;
    request["gender"] = gender;

    sendTcpJson(request);
}

// ------------------------- HTTP 请求（暴露给 QML） -------------------------

void AuthManager::requestLogin(const QString &username, const QString &password)
{
    if (m_apiBase.isEmpty()) {
        qWarning() << "AuthManager: API base URL is not set!";
        emit loginFailed("客户端错误：API 基础地址未设置");
        return;
    }

    QJsonObject obj;
    obj["type"] = "login";
    obj["username"] = username;
    obj["password"] = password;

    qDebug() << "POST" << (m_apiBase + "/login") << "payload:" << QJsonDocument(obj).toJson(QJsonDocument::Compact);
    postHttpJson("/login", obj, [this](QNetworkReply *reply) { onHttpLoginFinished(reply); }, 15000);
}

void AuthManager::requestRegister(const QString &userType, const QString &username, const QString &password,
                                  const QString &phone, const QString &address, int age, const QString &gender)
{
    if (m_apiBase.isEmpty()) {
        qWarning() << "AuthManager: API base URL is not set!";
        emit registerFailed("客户端错误：API 基础地址未设置");
        return;
    }

    QJsonObject obj;
    obj["type"] = "register";
    obj["userType"] = userType;
    obj["username"] = username;
    obj["password"] = password;
    obj["phone"] = phone;
    obj["address"] = address;
    obj["age"] = age;
    obj["gender"] = gender;

    qDebug() << "POST" << (m_apiBase + "/register") << "payload:" << QJsonDocument(obj).toJson(QJsonDocument::Compact);
    postHttpJson("/register", obj, [this](QNetworkReply *reply) { onHttpRegisterFinished(reply); }, 15000);
}

void AuthManager::submitHealthData(double heightCm, double weightKg, int lungMl, const QString &bp)
{
    if (!m_isAuthenticated || m_userId <= 0) {
        emit healthSubmitFailed("未登录或 userId 无效");
        return;
    }
    if (m_apiBase.isEmpty()) {
        qWarning() << "AuthManager: API base URL is not set!";
        emit healthSubmitFailed("客户端错误：API 基础地址未设置");
        return;
    }

    QJsonObject obj;
    obj["type"] = "health_submit";
    obj["userId"] = m_userId;
    obj["height"] = heightCm;
    obj["weight"] = weightKg;
    obj["lung"] = lungMl;
    obj["bp"] = bp;

    qDebug() << "POST" << (m_apiBase + "/health") << "payload:" << QJsonDocument(obj).toJson(QJsonDocument::Compact);
    postHttpJson("/health", obj, [this](QNetworkReply *reply) { onHttpHealthSubmitFinished(reply); }, 15000);
}

// ------------------------- TCP/HTTP 公共函数 -------------------------

void AuthManager::sendTcpJson(const QJsonObject &obj)
{
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact) + "\n";
    m_socket.write(data);
    m_socket.flush();
}

void AuthManager::postHttpJson(const QString &path,
                               const QJsonObject &obj,
                               std::function<void(QNetworkReply*)> callback,
                               int timeoutMs)
{
    if (m_apiBase.isEmpty()) {
        qWarning() << "AuthManager: API base URL is not set!";
        return;
    }

    QNetworkRequest req{ QUrl(m_apiBase + path) };
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = m_nam.post(req, QJsonDocument(obj).toJson(QJsonDocument::Compact));

    // 标注请求信息，方便日志和超时判断
    reply->setProperty("requestPath", path);
    reply->setProperty("timedOut", false);

    // 打印网络错误
    connect(reply, &QNetworkReply::errorOccurred, this, [reply](QNetworkReply::NetworkError code){
        Q_UNUSED(code);
        qWarning() << "HTTP error on" << reply->property("requestPath").toString() << ":" << reply->errorString();
    });

    // 超时控制：超时则 abort，finished 会照常触发
    auto timer = new QTimer(reply);
    timer->setSingleShot(true);
    timer->start(timeoutMs > 0 ? timeoutMs : 15000);
    connect(timer, &QTimer::timeout, reply, [this, reply]() {
        if (reply->isRunning()) {
            reply->setProperty("timedOut", true);
            qWarning() << "HTTP request timed out:" << reply->property("requestPath").toString();
            reply->abort(); // 将触发 finished -> handleHttpReply -> 发出失败信号
        }
    });

    connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
        callback(reply);
    });
}

// ------------------------- TCP 槽函数 -------------------------

void AuthManager::onConnected()
{
    qDebug() << "Connected to server (TCP).";
}

void AuthManager::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qDebug() << "Socket error:" << m_socket.errorString();
    emit loginFailed("TCP 连接失败：" + m_socket.errorString());
}

void AuthManager::onReadyRead()
{
    m_pendingBuffer.append(m_socket.readAll());

    while (true) {
        int idx = m_pendingBuffer.indexOf('\n');
        if (idx == -1) break;

        QByteArray jsonData = m_pendingBuffer.left(idx);
        m_pendingBuffer.remove(0, idx + 1);

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            QString type = obj.value("type").toString();

            if (type == "login") {
                processLoginResponse(obj);
            } else if (type == "register") {
                processRegisterResponse(obj);
            } else if (type == "health_submit") {
                processHealthSubmitResponse(obj);
            }
        }
    }
}

// ------------------------- HTTP 槽函数 -------------------------

void AuthManager::onHttpLoginFinished(QNetworkReply* reply)
{
    handleHttpReply(reply, [this](const QJsonObject &obj) { processLoginResponse(obj); },
                    [this](const QString &err) { emit loginFailed(err); });
}

void AuthManager::onHttpRegisterFinished(QNetworkReply* reply)
{
    handleHttpReply(reply, [this](const QJsonObject &obj) { processRegisterResponse(obj); },
                    [this](const QString &err) { emit registerFailed(err); });
}

void AuthManager::onHttpHealthSubmitFinished(QNetworkReply* reply)
{
    handleHttpReply(reply, [this](const QJsonObject &obj) { processHealthSubmitResponse(obj); },
                    [this](const QString &err) { emit healthSubmitFailed(err); });
}

void AuthManager::handleHttpReply(QNetworkReply* reply,
                                  std::function<void(const QJsonObject&)> onSuccess,
                                  std::function<void(const QString&)> onError)
{
    if (reply->error() != QNetworkReply::NoError) {
        if (reply->property("timedOut").toBool()) {
            onError(QStringLiteral("请求超时，请检查网络或服务器是否运行"));
        } else {
            onError(reply->errorString());
        }
        reply->deleteLater();
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument d = QJsonDocument::fromJson(data);
    if (!d.isObject()) {
        onError("响应格式错误。");
    } else {
        onSuccess(d.object());
    }
    reply->deleteLater();
}

// ------------------------- 响应处理 -------------------------

void AuthManager::processLoginResponse(const QJsonObject &resp)
{
    bool success = resp.value("success").toBool();
    if (success) {
        m_isAuthenticated = true;
        emit isAuthenticatedChanged();
        m_userId = resp.value("userId").toInt();
        emit currentUserIdChanged();
        QString userTypeStr = resp.value("userType").toString();
        UserType userType = (userTypeStr == "patient") ? Patient : Doctor;

        emit loginSuccess(m_userId, userType);
    } else {
        int rem = resp.value("remainingAttempts").toInt(m_remainingAttempts);
        setRemainingAttempts(rem);
        emit loginFailed(resp.value("reason").toString("登录失败"));
    }
}

void AuthManager::processRegisterResponse(const QJsonObject &resp)
{
    bool success = resp.value("success").toBool();
    if (success) {
        emit registerSuccess();
    } else {
        emit registerFailed(resp.value("reason").toString("注册失败"));
    }
}

void AuthManager::processHealthSubmitResponse(const QJsonObject &resp)
{
    bool success = resp.value("success").toBool();
    if (success) {
        emit healthSubmitSuccess(
            resp.value("bmi").toDouble(),
            resp.value("lungLevel").toString(),
            resp.value("bpLevel").toString(),
            resp.value("overall").toString()
            );
    } else {
        emit healthSubmitFailed(resp.value("reason").toString("提交失败"));
    }
}

// ------------------------- getter/setter -------------------------

bool AuthManager::isAuthenticated() const { return m_isAuthenticated; }
int AuthManager::remainingAttempts() const { return m_remainingAttempts; }
int AuthManager::currentUserId() const { return m_userId; }

void AuthManager::setRemainingAttempts(int attempts)
{
    if (m_remainingAttempts != attempts) {
        m_remainingAttempts = attempts;
        emit remainingAttemptsChanged();
    }
}

#include "authmanager.h"
#include "databasemanager.h"
#include "qjsondocument.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QTimer>
#include <QJSValue>

// ------------------------- 构造与配置 -------------------------

AuthManager::AuthManager(QObject *parent)
    : QObject(parent)
{
    connect(&m_socket, &QTcpSocket::readyRead, this, &AuthManager::onReadyRead);
    connect(&m_socket, &QTcpSocket::connected, this, &AuthManager::onConnected);
    connect(&m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &AuthManager::onErrorOccurred);
}

void AuthManager::setApiBase(const QString &url)
{
    m_apiBase = url;
    qDebug() << "AuthManager: API base set to" << m_apiBase;
}

// --- 根据职业获取数据库连接 ---
QSqlDatabase AuthManager::getProfessionDatabase(const QString& profession) {
    QString dbName = QString("%1.db").arg(profession.toLower());
    QString connName = QString("%1_connection").arg(profession.toLower());
    QSqlDatabase db;
    if (QSqlDatabase::contains(connName)) {
        db = QSqlDatabase::database(connName);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", connName);
        db.setDatabaseName(dbName);
        db.open();
        // 自动建表（仅首次创建数据库时）
        QSqlQuery q(db);
        q.exec(R"(
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE,
                password TEXT,
                gender TEXT,
                phone TEXT,
                address TEXT,
                age INTEGER
            )
        )");
    }
    return db;
}

void AuthManager::requestRegister(const QString &profession, const QString &username, const QString &password,
                                  const QString &phone, const QString &address, int age, const QString &gender)
{
    // 构造 JSON 参数
    QJsonObject obj;
    obj["userType"] = profession; // "patient" 或 "doctor"
    obj["username"] = username;
    obj["password"] = password;
    obj["phone"] = phone;
    obj["address"] = address;
    obj["age"] = age;
    obj["gender"] = gender;

    // 发送 HTTP 请求到后端注册接口
    QNetworkRequest request(QUrl(m_apiBase + "/api/auth/register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_nam.post(request, QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onHttpRegisterFinished(reply);
    });
}

void AuthManager::requestLogin(const QString &profession, const QString &username, const QString &password)
{
    QJsonObject obj;
    obj["userType"] = profession;
    obj["username"] = username;
    obj["password"] = password;

    QNetworkRequest request(QUrl(m_apiBase + "/api/auth/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_nam.post(request, QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onHttpLoginFinished(reply);
    });
}

void AuthManager::submitHealthData(double heightCm, double weightKg, int lungMl, const QString &bp)
{
    QJsonObject obj;
    obj["userId"] = m_userId;
    obj["height"] = heightCm;
    obj["weight"] = weightKg;
    obj["lung"] = lungMl;
    obj["bp"] = bp;

    QNetworkRequest request(QUrl(m_apiBase + "/api/health/submit"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_nam.post(request, QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onHttpHealthSubmitFinished(reply);
    });
}

void AuthManager::getPatientInfo(QJSValue callback)
{
    QUrl url(m_apiBase + "/api/patient/info?userId=" + QString::number(m_userId) + "&profession=patient");
    QNetworkRequest request(url);

    QNetworkReply* reply = m_nam.get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, callback]() mutable {
        QByteArray data = reply->readAll();
        reply->deleteLater();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isObject()) {
            QJsonObject obj = doc.object();
            QJsonObject infoObj = obj.value("info").toObject();  // 关键修正
            QJSValueList args;
            args << QJSValue(infoObj.value("username").toString())
                 << QJSValue(infoObj.value("phone").toString())
                 << QJSValue(infoObj.value("address").toString())
                 << QJSValue(QString::number(infoObj.value("age").toInt()))
                 << QJSValue(infoObj.value("gender").toString());
            if (callback.isCallable())
                callback.call(args);
        } else {
            QJSValueList emptyArgs;
            if (callback.isCallable())
                callback.call(emptyArgs);
        }
    });
}



void AuthManager::updatePatientInfo(const QString &username,
                                    const QString &phone,
                                    const QString &address,
                                    const QString &age,
                                    const QString &gender,
                                    QJSValue callback)
{
    QJsonObject obj;
    obj["userId"] = m_userId;
    obj["profession"] = "patient"; // 必须加上
    obj["username"] = username;
    obj["phone"] = phone;
    obj["address"] = address;
    obj["age"] = age.toInt();
    obj["gender"] = gender;

    QNetworkRequest request(QUrl(m_apiBase + "/api/patient/update"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_nam.post(request, QJsonDocument(obj).toJson());
    connect(reply, &QNetworkReply::finished, this, [reply, callback]()mutable {
        QByteArray data = reply->readAll();
        reply->deleteLater();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject resp = doc.object();
        bool success = resp.value("success").toBool();
        if (callback.isCallable())
            callback.call(QJSValueList() << QJSValue(success));
    });
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

    reply->setProperty("requestPath", path);
    reply->setProperty("timedOut", false);

    auto timer = new QTimer(reply);
    timer->setSingleShot(true);
    timer->start(timeoutMs > 0 ? timeoutMs : 15000);
    connect(timer, &QTimer::timeout, reply, [reply]() {
        if (reply->isRunning()) {
            reply->setProperty("timedOut", true);
            qWarning() << "HTTP request timed out:" << reply->property("requestPath").toString();
            reply->abort();
        }
    });

    connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
        callback(reply);
    });
}

// ------------------------- TCP 槽函数（HTTP 模式下仅日志） -------------------------

void AuthManager::onConnected()
{
    qDebug() << "Connected to server (TCP).";
}

void AuthManager::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qWarning() << "[TCP] Socket error (ignored in HTTP mode):" << m_socket.errorString();
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
            if (type == "login")       processLoginResponse(obj);
            else if (type == "register") processRegisterResponse(obj);
            else if (type == "health_submit") processHealthSubmitResponse(obj);
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

// 统一 HTTP 回包处理
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
        onError(QStringLiteral("响应格式错误。"));
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

        QString userTypeStr = resp.value("userType").toString("patient");
        m_userType = (userTypeStr == "patient") ? Patient : Doctor;
        emit currentUserTypeChanged();

        emit loginSuccess(m_userId, m_userType);
    } else {
        int rem = resp.value("remainingAttempts").toInt(m_remainingAttempts);
        setRemainingAttempts(rem);
        emit loginFailed(resp.value("reason").toString(QStringLiteral("登录失败")));
    }
}

void AuthManager::processRegisterResponse(const QJsonObject &resp)
{
    bool success = resp.value("success").toBool();
    if (success) {
        emit registerSuccess();
    } else {
        emit registerFailed(resp.value("reason").toString(QStringLiteral("注册失败")));
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
        emit healthSubmitFailed(resp.value("reason").toString(QStringLiteral("提交失败")));
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

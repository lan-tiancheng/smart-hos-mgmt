// authmanager.cpp
#include "src/authmanager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QUrl>
#include <QDebug>
#include <QHostAddress>
#include <QJsonArray>

AuthManager::AuthManager(QObject *parent)
    : QObject(parent),
    m_apiBase(QStringLiteral("http://127.0.0.1:8080")),
    m_isAuthenticated(false),
    m_userId(0),
    m_remainingAttempts(5)
{
    connect(&m_socket, &QTcpSocket::readyRead, this, &AuthManager::onReadyRead);
    connect(&m_socket, &QTcpSocket::connected, this, &AuthManager::onConnected);
    connect(&m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &AuthManager::onErrorOccurred);
}

// 实现 onReadyRead 函数
void AuthManager::onReadyRead()
{
    QByteArray data = m_socket.readAll();
    qDebug() << "Received data from server:" << data;

    // 尝试解析JSON响应
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON parse error:" << parseError.errorString();
        return;
    }

    if (!doc.isObject()) {
        qDebug() << "Received data is not a JSON object";
        return;
    }

    QJsonObject resp = doc.object();
    processResponseObject(resp);
}

// 实现 onConnected 函数
void AuthManager::onConnected()
{
    qDebug() << "Connected to server (TCP).";
}

// 实现 onErrorOccurred 函数
void AuthManager::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    qDebug() << "Socket error:" << m_socket.errorString();
    emit loginFailed("无法连接到服务器");
}

// 实现其他缺失的函数
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
        requestLogin(username, password);
    }
}

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

void AuthManager::sendMessage(int toUserId, const QString &message)
{
    if (!m_isAuthenticated) {
        emit messageSentFailed("未登录");
        return;
    }

    QJsonObject obj;
    obj["type"] = "send_message";
    obj["fromUserId"] = m_userId;
    obj["toUserId"] = toUserId;
    obj["message"] = message;
    obj["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonDocument doc(obj);

    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write(doc.toJson(QJsonDocument::Compact));
        m_socket.flush();
    } else {
        // HTTP 实现
        QNetworkRequest req(QUrl(m_apiBase + "/api/message/send"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = m_nam.post(req, doc.toJson());
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            reply->deleteLater();
            if (reply->error() != QNetworkReply::NoError) {
                emit messageSentFailed(reply->errorString());
                return;
            }

            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            if (!responseDoc.isObject()) {
                emit messageSentFailed("无效响应格式");
                return;
            }

            QJsonObject responseObj = responseDoc.object();
            if (responseObj.value("success").toBool()) {
                emit messageSentSuccess(responseObj.value("messageId").toInt());
            } else {
                emit messageSentFailed(responseObj.value("reason").toString("发送失败"));
            }
        });
    }
}

void AuthManager::requestConversations()
{
    if (!m_isAuthenticated) {
        return;
    }

    QJsonObject obj;
    obj["type"] = "get_conversations";
    obj["userId"] = m_userId;

    QJsonDocument doc(obj);

    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write(doc.toJson(QJsonDocument::Compact));
        m_socket.flush();
    } else {
        // HTTP 实现
        QNetworkRequest req(QUrl(m_apiBase + "/api/message/conversations"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = m_nam.post(req, doc.toJson());
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            reply->deleteLater();
            if (reply->error() != QNetworkReply::NoError) {
                return;
            }

            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            if (responseDoc.isObject()) {
                QJsonObject responseObj = responseDoc.object();
                if (responseObj.value("success").toBool()) {
                    emit conversationListReceived(responseObj.value("conversations").toArray());
                }
            }
        });
    }
}

void AuthManager::requestMessages(int otherUserId)
{
    if (!m_isAuthenticated) {
        return;
    }

    QJsonObject obj;
    obj["type"] = "get_messages";
    obj["userId"] = m_userId;
    obj["otherUserId"] = otherUserId;

    QJsonDocument doc(obj);

    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write(doc.toJson(QJsonDocument::Compact));
        m_socket.flush();
    } else {
        QNetworkRequest req(QUrl(m_apiBase + "/api/message/list"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = m_nam.post(req, doc.toJson());
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            reply->deleteLater();
            if (reply->error() != QNetworkReply::NoError) {
                return;
            }

            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            if (responseDoc.isObject()) {
                QJsonObject responseObj = responseDoc.object();
                if (responseObj.value("success").toBool()) {
                    int conversationId = responseObj.value("conversationId").toInt();
                    emit messagesReceived(conversationId, responseObj.value("messages").toArray());
                }
            }
        });
    }
}

void AuthManager::setRemainingAttempts(int attempts)
{
    if (m_remainingAttempts != attempts) {
        m_remainingAttempts = attempts;
        emit remainingAttemptsChanged();
    }
}

void AuthManager::processMessage(const QJsonObject &messageObj)
{
    int fromUserId = messageObj.value("fromUserId").toInt();
    QString fromUsername = messageObj.value("fromUsername").toString();
    QString message = messageObj.value("message").toString();

    emit messageReceived(fromUserId, fromUsername, message);
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
    } else if (type == "message") {
        processMessage(resp);
    } else if (type == "conversation_list") {
        QJsonArray conversations = resp.value("conversations").toArray();
        emit conversationListReceived(conversations);
    } else if (type == "message_list") {
        int conversationId = resp.value("conversationId").toInt();
        QJsonArray messages = resp.value("messages").toArray();
        emit messagesReceived(conversationId, messages);
    } else if (type == "video_call_request") {
        processVideoCallRequest(resp);
    } else if (type == "video_call_response") {
        bool accepted = resp.value("accepted").toBool();
        int callId = resp.value("callId").toInt();
        if (accepted) {
            emit videoCallAccepted(callId);
        } else {
            emit videoCallRejected(callId);
        }
    } else if (type == "video_call_started") {
        int callId = resp.value("callId").toInt();
        emit videoCallStarted(callId);
    } else if (type == "video_call_ended") {
        int callId = resp.value("callId").toInt();
        emit videoCallEnded(callId);
    } else {
        qDebug() << "Unknown response type:" << type;
    }
}

// 处理视频呼叫请求
void AuthManager::processVideoCallRequest(const QJsonObject &callObj)
{
    int callId = callObj.value("callId").toInt();
    int fromUserId = callObj.value("fromUserId").toInt();
    QString fromUsername = callObj.value("fromUsername").toString();

    emit videoCallRequested(callId, fromUserId, fromUsername);
}

void AuthManager::logout()
{
    m_isAuthenticated = false;
    m_userId = 0;
    emit isAuthenticatedChanged();
    emit logoutSuccess();

    // 关闭TCP连接
    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.disconnectFromHost();
    }
}

// 实现 startVideoCall 函数
void AuthManager::startVideoCall(int otherUserId)
{
    if (!m_isAuthenticated) {
        emit videoCallError("未登录");
        return;
    }

    QJsonObject obj;
    obj["type"] = "video_call_request";
    obj["fromUserId"] = m_userId;
    obj["toUserId"] = otherUserId;

    QJsonDocument doc(obj);

    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write(doc.toJson(QJsonDocument::Compact));
        m_socket.flush();
    } else {
        QNetworkRequest req(QUrl(m_apiBase + "/api/video/call"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = m_nam.post(req, doc.toJson());
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            reply->deleteLater();
            if (reply->error() != QNetworkReply::NoError) {
                emit videoCallError(reply->errorString());
                return;
            }

            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            if (!responseDoc.isObject()) {
                emit videoCallError("无效响应格式");
                return;
            }

            QJsonObject responseObj = responseDoc.object();
            if (responseObj.value("success").toBool()) {
                int callId = responseObj.value("callId").toInt();
                emit videoCallStarted(callId);
            } else {
                emit videoCallError(responseObj.value("reason").toString("呼叫失败"));
            }
        });
    }
}

// 实现 acceptVideoCall 函数
void AuthManager::acceptVideoCall(int callId)
{
    if (!m_isAuthenticated) {
        return;
    }

    QJsonObject obj;
    obj["type"] = "video_call_response";
    obj["callId"] = callId;
    obj["accepted"] = true;

    QJsonDocument doc(obj);

    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write(doc.toJson(QJsonDocument::Compact));
        m_socket.flush();
    } else {
        QNetworkRequest req(QUrl(m_apiBase + "/api/video/response"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = m_nam.post(req, doc.toJson());
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            reply->deleteLater();
            if (reply->error() != QNetworkReply::NoError) {
                emit videoCallError(reply->errorString());
                return;
            }

            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            if (responseDoc.isObject()) {
                QJsonObject responseObj = responseDoc.object();
                if (responseObj.value("success").toBool()) {
                    int callId = responseObj.value("callId").toInt();
                    emit videoCallAccepted(callId);
                }
            }
        });
    }
}

// 实现 rejectVideoCall 函数
void AuthManager::rejectVideoCall(int callId)
{
    if (!m_isAuthenticated) {
        return;
    }

    QJsonObject obj;
    obj["type"] = "video_call_response";
    obj["callId"] = callId;
    obj["accepted"] = false;

    QJsonDocument doc(obj);

    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write(doc.toJson(QJsonDocument::Compact));
        m_socket.flush();
    } else {
        QNetworkRequest req(QUrl(m_apiBase + "/api/video/response"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = m_nam.post(req, doc.toJson());
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            reply->deleteLater();
            if (reply->error() != QNetworkReply::NoError) {
                return;
            }

            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            if (responseDoc.isObject()) {
                QJsonObject responseObj = responseDoc.object();
                if (responseObj.value("success").toBool()) {
                    int callId = responseObj.value("callId").toInt();
                    emit videoCallRejected(callId);
                }
            }
        });
    }
}

void AuthManager::endVideoCall(int callId)
{
    if (!m_isAuthenticated) {
        return;
    }

    QJsonObject obj;
    obj["type"] = "video_call_end";
    obj["callId"] = callId;

    QJsonDocument doc(obj);

    if (m_socket.state() == QAbstractSocket::ConnectedState) {
        m_socket.write(doc.toJson(QJsonDocument::Compact));
        m_socket.flush();
    } else {
        QNetworkRequest req(QUrl(m_apiBase + "/api/video/end"));
        req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        QNetworkReply *reply = m_nam.post(req, doc.toJson());
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            reply->deleteLater();
            // 处理通话结束响应
        });
    }
}

#include "ChatClient.h"
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QTimer>
#include <QAbstractSocket>

ChatClient::ChatClient(QObject* parent) : QObject(parent) {
    connect(&m_ws, SIGNAL(connected()), this, SLOT(onWsConnected()));
    connect(&m_ws, SIGNAL(disconnected()), this, SLOT(onWsDisconnected()));
    connect(&m_ws, SIGNAL(textMessageReceived(QString)), this, SLOT(onWsTextMessage(QString)));
    connect(&m_ws, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onWsError()));
}

void ChatClient::configure(const QString& baseUrl, qint64 userId, Role role) {
    m_baseUrl = baseUrl;
    if (m_baseUrl.endsWith('/')) m_baseUrl.chop(1);
    m_userId = userId;
    m_role = role;
}

QString ChatClient::roleToString(Role r) const {
    return r == Role::Doctor ? "doctor" : "patient";
}

void ChatClient::connectWebSocket() {
    if (m_userId <= 0) {
        emit errorOccurred("UserId not configured");
        return;
    }
    QString wsUrl = m_baseUrl;
    if (wsUrl.startsWith("https://"))
        wsUrl.replace(0, 5, "wss");
    else if (wsUrl.startsWith("http://"))
        wsUrl.replace(0, 4, "ws");
    wsUrl += "/ws";
    QUrl url(wsUrl);
    QUrlQuery q;
    q.addQueryItem("user_id", QString::number(m_userId));
    url.setQuery(q);
    m_ws.open(url);
}

void ChatClient::disconnectWebSocket() {
    m_ws.close();
}

void ChatClient::onWsConnected() {
    m_connected = true;
    emit connectedChanged(true);
}

void ChatClient::onWsDisconnected() {
    m_connected = false;
    emit connectedChanged(false);
}

void ChatClient::onWsTextMessage(const QString& text) {
    QJsonParseError err;
    const auto doc = QJsonDocument::fromJson(text.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        emit errorOccurred(QString("Invalid WS JSON: %1").arg(err.errorString()));
        return;
    }
    const QJsonObject obj = doc.object();
    const QString event = obj.value("event").toString();
    const QJsonObject data = obj.value("data").toObject();
    if (event == "message:new") {
        emit messageReceived(data);
    } else if (event == "receipt:read") {
        emit readReceiptReceived(data);
    }
}

void ChatClient::onWsError() {
    emit errorOccurred(QString("WebSocket error: %1").arg(m_ws.errorString()));
}

QNetworkRequest ChatClient::makeRequest(const QString& path) const {
    QUrl url(m_baseUrl + path);
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("X-User-Id", QByteArray::number(m_userId));
    req.setRawHeader("X-User-Role", roleToString(m_role).toUtf8());
    return req;
}

void ChatClient::httpGet(const QString& path, std::function<void(const QJsonValue&)> cb) {
    auto* reply = m_nam.get(makeRequest(path));
    connect(reply, &QNetworkReply::finished, this, [this, reply, cb]() {
        if (reply->error() != QNetworkReply::NoError) {
            emit errorOccurred(QString("HTTP GET %1 failed: %2").arg(reply->url().toString(), reply->errorString()));
            reply->deleteLater();
            return;
        }
        const QByteArray raw = reply->readAll();
        QJsonParseError err;
        const auto doc = QJsonDocument::fromJson(raw, &err);
        if (err.error != QJsonParseError::NoError) {
            emit errorOccurred(QString("Invalid JSON from %1: %2").arg(reply->url().toString(), err.errorString()));
            reply->deleteLater();
            return;
        }
        if (cb) cb(doc.isArray() ? QJsonValue(doc.array()) : QJsonValue(doc.object()));
        reply->deleteLater();
    });
}

void ChatClient::httpPost(const QString& path, const QJsonObject& body, std::function<void(const QJsonValue&)> cb) {
    QNetworkRequest req = makeRequest(path);
    const QByteArray data = QJsonDocument(body).toJson(QJsonDocument::Compact);
    auto* reply = m_nam.post(req, data);
    connect(reply, &QNetworkReply::finished, this, [this, reply, cb]() {
        if (reply->error() != QNetworkReply::NoError) {
            emit errorOccurred(QString("HTTP POST %1 failed: %2").arg(reply->url().toString(), reply->errorString()));
            reply->deleteLater();
            return;
        }
        const QByteArray raw = reply->readAll();
        if (raw.isEmpty()) {
            if (cb) cb(QJsonValue());
            reply->deleteLater();
            return;
        }
        QJsonParseError err;
        const auto doc = QJsonDocument::fromJson(raw, &err);
        if (err.error != QJsonParseError::NoError) {
            emit errorOccurred(QString("Invalid JSON from %1: %2").arg(reply->url().toString(), err.errorString()));
            reply->deleteLater();
            return;
        }
        if (cb) cb(doc.isArray() ? QJsonValue(doc.array()) : QJsonValue(doc.object()));
        reply->deleteLater();
    });
}

void ChatClient::createConversation(qint64 doctorId, qint64 patientId) {
    QJsonObject body{
        {"doctor_id", static_cast<double>(doctorId)},
        {"patient_id", static_cast<double>(patientId)}
    };
    httpPost("/api/conversations", body, [this](const QJsonValue& v){
        emit conversationReady(v.toObject());
    });
}

void ChatClient::listMyConversations() {
    const QString role = roleToString(m_role);
    const QString path = QString("/api/conversations?role=%1&user_id=%2").arg(role).arg(m_userId);
    httpGet(path, [this](const QJsonValue& v){
        if (v.isArray()) emit conversationsLoaded(v.toArray());
        else emit errorOccurred("Unexpected conversations payload");
    });
}

void ChatClient::listMessages(qint64 conversationId, qint64 beforeId, int limit) {
    QString path = QString("/api/messages?conversation_id=%1").arg(conversationId);
    if (beforeId > 0) path += QString("&before_id=%1").arg(beforeId);
    if (limit > 0) path += QString("&limit=%1").arg(limit);
    httpGet(path, [this](const QJsonValue& v){
        if (v.isArray()) emit messagesLoaded(v.toArray());
        else emit errorOccurred("Unexpected messages payload");
    });
}

void ChatClient::sendMessage(qint64 conversationId, const QString& type, const QString& content, const QJsonObject& meta) {
    QJsonObject body{
        {"conversation_id", static_cast<double>(conversationId)},
        {"type", type},
        {"content", content}
    };
    if (!meta.isEmpty()) {
        body.insert("meta", meta);
    }
    httpPost("/api/messages", body, [this](const QJsonValue& v){
        emit messageSent(v.toObject());
    });
}

void ChatClient::markRead(qint64 messageId) {
    QJsonObject body{{"message_id", static_cast<double>(messageId)}};
    httpPost("/api/messages/read", body, nullptr);
}

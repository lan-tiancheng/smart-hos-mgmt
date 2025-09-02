#pragma once
#include <QObject>
#include <QUrl>
#include <QtWebSockets/QWebSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <functional>

class ChatClient : public QObject {
    Q_OBJECT
public:
    enum class Role { Doctor, Patient };
    Q_ENUM(Role)

    explicit ChatClient(QObject* parent = nullptr);

    void configure(const QString& baseUrl, qint64 userId, Role role);
    void connectWebSocket();
    void disconnectWebSocket();

    // REST
    void createConversation(qint64 doctorId, qint64 patientId);
    void listMyConversations();
    void listMessages(qint64 conversationId, qint64 beforeId = 0, int limit = 50);
    void sendMessage(qint64 conversationId, const QString& type = QString("text"), const QString& content = QString(), const QJsonObject& meta = QJsonObject());
    void markRead(qint64 messageId);

signals:
    void connectedChanged(bool connected);
    void errorOccurred(const QString& msg);

    void conversationReady(const QJsonObject& conv);
    void conversationsLoaded(const QJsonArray& list);
    void messagesLoaded(const QJsonArray& list);
    void messageSent(const QJsonObject& msg);

    void messageReceived(const QJsonObject& msg);
    void readReceiptReceived(const QJsonObject& receipt);

private slots:
    void onWsConnected();
    void onWsDisconnected();
    void onWsTextMessage(const QString& text);
    void onWsError();

private:
    QString roleToString(Role r) const;
    QNetworkRequest makeRequest(const QString& path) const;
    void httpGet(const QString& path, std::function<void(const QJsonValue&)> cb);
    void httpPost(const QString& path, const QJsonObject& body, std::function<void(const QJsonValue&)> cb);

private:
    QString m_baseUrl {"http://127.0.0.1:8000"};
    qint64 m_userId {0};
    Role m_role {Role::Doctor};

    QWebSocket m_ws;
    QNetworkAccessManager m_nam;
    bool m_connected {false};
};

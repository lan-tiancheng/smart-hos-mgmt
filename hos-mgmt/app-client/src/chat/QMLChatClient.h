#pragma once
#include <QObject>
#include "chat/ChatClient.h"

class QMLChatClient : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool connected READ isConnected NOTIFY connectedChanged)
public:
    explicit QMLChatClient(QObject* parent = nullptr);

    Q_INVOKABLE void configure(const QString& baseUrl, qint64 userId, const QString& role);
    Q_INVOKABLE void connectWebSocket();
    Q_INVOKABLE void disconnectWebSocket();
    Q_INVOKABLE void createConversation(qint64 doctorId, qint64 patientId);
    Q_INVOKABLE void listMyConversations();
    Q_INVOKABLE void listMessages(qint64 conversationId, qint64 beforeId = 0, int limit = 50);
    Q_INVOKABLE void sendMessage(qint64 conversationId, const QString& content);
    Q_INVOKABLE void markRead(qint64 messageId);

    bool isConnected() const { return m_connected; }

signals:
    void connectedChanged(bool connected);
    void errorOccurred(const QString& msg);

    void conversationReady(const QVariant& conv);
    void conversationsLoaded(const QVariant& list);
    void messagesLoaded(const QVariant& list);
    void messageSent(const QVariant& msg);

    void messageReceived(const QVariant& msg);
    void readReceiptReceived(const QVariant& receipt);

private:
    ChatClient* m_client {nullptr};
    bool m_connected {false};
};

#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "chat/ChatClient.h"

class ChatWindow : public QWidget {
    Q_OBJECT
public:
    explicit ChatWindow(const QString& baseUrl, qint64 userId, ChatClient::Role role, QWidget* parent = nullptr);

private slots:
    void onConnectedChanged(bool ok);
    void onConversationsLoaded(const QJsonArray& list);
    void onMessagesLoaded(const QJsonArray& list);
    void onMessageReceived(const QJsonObject& msg);
    void onMessageSent(const QJsonObject& msg);
    void onReadReceipt(const QJsonObject& rec);

    void onSelectConversation();
    void onSend();
    void onConnectWs();

private:
    ChatClient* m_client {nullptr};
    QLabel* m_status {nullptr};
    QListWidget* m_convs {nullptr};
    QListWidget* m_msgs {nullptr};
    QLineEdit* m_input {nullptr};
    QPushButton* m_btnSend {nullptr};
    QPushButton* m_btnConnect {nullptr};
};

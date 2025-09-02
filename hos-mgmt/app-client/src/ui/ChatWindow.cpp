#include "ChatWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidgetItem>

ChatWindow::ChatWindow(const QString& baseUrl, qint64 userId, ChatClient::Role role, QWidget* parent)
    : QWidget(parent) {
    setWindowTitle(QString("Chat - %1 #%2").arg(role == ChatClient::Role::Doctor ? "doctor" : "patient").arg(userId));
    resize(840, 560);

    m_client = new ChatClient(this);
    m_client->configure(baseUrl, userId, role);

    auto* layout = new QVBoxLayout(this);
    m_status = new QLabel("WS: disconnected", this);
    layout->addWidget(m_status);

    auto* hl = new QHBoxLayout();
    m_convs = new QListWidget(this);
    m_msgs = new QListWidget(this);
    hl->addWidget(m_convs, 2);
    hl->addWidget(m_msgs, 3);
    layout->addLayout(hl);

    auto* sendLine = new QHBoxLayout();
    m_input = new QLineEdit(this);
    m_btnSend = new QPushButton("Send", this);
    sendLine->addWidget(m_input, 1);
    sendLine->addWidget(m_btnSend);
    layout->addLayout(sendLine);

    m_btnConnect = new QPushButton("Connect WS", this);
    layout->addWidget(m_btnConnect);

    // signals
    connect(m_client, SIGNAL(connectedChanged(bool)), this, SLOT(onConnectedChanged(bool)));
    connect(m_client, SIGNAL(conversationsLoaded(QJsonArray)), this, SLOT(onConversationsLoaded(QJsonArray)));
    connect(m_client, SIGNAL(messagesLoaded(QJsonArray)), this, SLOT(onMessagesLoaded(QJsonArray)));
    connect(m_client, SIGNAL(messageReceived(QJsonObject)), this, SLOT(onMessageReceived(QJsonObject)));
    connect(m_client, SIGNAL(messageSent(QJsonObject)), this, SLOT(onMessageSent(QJsonObject)));
    connect(m_client, SIGNAL(readReceiptReceived(QJsonObject)), this, SLOT(onReadReceipt(QJsonObject)));
    connect(m_client, SIGNAL(errorOccurred(QString)), m_status, SLOT(setText(QString)));

    connect(m_btnConnect, SIGNAL(clicked()), this, SLOT(onConnectWs()));
    connect(m_btnSend, SIGNAL(clicked()), this, SLOT(onSend()));
    connect(m_convs, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectConversation()));

    // 初始加载会话
    m_client->listMyConversations();
}

void ChatWindow::onConnectedChanged(bool ok) {
    m_status->setText(QString("WS: %1").arg(ok ? "connected" : "disconnected"));
}

void ChatWindow::onConversationsLoaded(const QJsonArray& list) {
    m_convs->clear();
    for (const auto& it : list) {
        const auto obj = it.toObject();
        const qint64 convId = static_cast<qint64>(obj.value("id").toDouble());
        const auto text = QString("#%1 D%2-P%3 unread(D=%4,P=%5)")
                              .arg(convId)
                              .arg(static_cast<qint64>(obj.value("doctor_id").toDouble()))
                              .arg(static_cast<qint64>(obj.value("patient_id").toDouble()))
                              .arg(static_cast<int>(obj.value("unread_count_doctor").toDouble()))
                              .arg(static_cast<int>(obj.value("unread_count_patient").toDouble()));
        auto* item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, QVariant::fromValue(convId));
        m_convs->addItem(item);
    }
}

void ChatWindow::onSelectConversation() {
    auto* item = m_convs->currentItem();
    if (!item) return;
    const qint64 convId = item->data(Qt::UserRole).toLongLong();
    m_msgs->clear();
    m_client->listMessages(convId);
}

void ChatWindow::onMessagesLoaded(const QJsonArray& list) {
    m_msgs->clear();
    for (const auto& it : list) {
        const auto m = it.toObject();
        const qint64 id = static_cast<qint64>(m.value("id").toDouble());
        const QString senderRole = m.value("sender_role").toString();
        const qint64 senderId = static_cast<qint64>(m.value("sender_id").toDouble());
        const QString content = m.value("content").toString();
        m_msgs->addItem(QString("[%1] %2(%3): %4").arg(id).arg(senderRole).arg(senderId).arg(content));
    }
}

void ChatWindow::onMessageReceived(const QJsonObject& m) {
    auto* item = m_convs->currentItem();
    const qint64 thisConv = item ? item->data(Qt::UserRole).toLongLong() : 0;
    const qint64 convId = static_cast<qint64>(m.value("conversation_id").toDouble());
    if (thisConv > 0 && convId == thisConv) {
        const qint64 id = static_cast<qint64>(m.value("id").toDouble());
        const QString role = m.value("sender_role").toString();
        const qint64 senderId = static_cast<qint64>(m.value("sender_id").toDouble());
        const QString content = m.value("content").toString();
        m_msgs->addItem(QString("[%1] %2(%3): %4").arg(id).arg(role).arg(senderId).arg(content));
        // 回执
        m_client->markRead(id);
    }
    // 刷新会话（未读计数）
    m_client->listMyConversations();
}

void ChatWindow::onMessageSent(const QJsonObject& m) {
    const qint64 id = static_cast<qint64>(m.value("id").toDouble());
    const QString content = m.value("content").toString();
    m_msgs->addItem(QString("[%1] me: %2").arg(id).arg(content));
}

void ChatWindow::onReadReceipt(const QJsonObject& rec) {
    const qint64 msgId = static_cast<qint64>(rec.value("message_id").toDouble());
    const qint64 reader = static_cast<qint64>(rec.value("reader_id").toDouble());
    m_status->setText(QString("Read receipt: message %1 read by %2").arg(msgId).arg(reader));
}

void ChatWindow::onSend() {
    auto* item = m_convs->currentItem();
    if (!item) return;
    const qint64 convId = item->data(Qt::UserRole).toLongLong();
    const QString content = m_input->text().trimmed();
    if (content.isEmpty()) return;
    m_client->sendMessage(convId, "text", content);
    m_input->clear();
}

void ChatWindow::onConnectWs() {
    m_client->connectWebSocket();
}

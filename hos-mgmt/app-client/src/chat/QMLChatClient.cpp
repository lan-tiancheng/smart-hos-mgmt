#include "QMLChatClient.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>

QMLChatClient::QMLChatClient(QObject* parent): QObject(parent) {
    m_client = new ChatClient(this);

    connect(m_client, &ChatClient::connectedChanged, this, [this](bool ok){
        m_connected = ok;
        emit connectedChanged(ok);
    });
    connect(m_client, &ChatClient::errorOccurred, this, &QMLChatClient::errorOccurred);

    connect(m_client, &ChatClient::conversationReady, this, [this](const QJsonObject& conv){
        emit conversationReady(QVariant::fromValue(conv));
    });
    connect(m_client, &ChatClient::conversationsLoaded, this, [this](const QJsonArray& arr){
        emit conversationsLoaded(QVariant::fromValue(arr));
    });
    connect(m_client, &ChatClient::messagesLoaded, this, [this](const QJsonArray& arr){
        emit messagesLoaded(QVariant::fromValue(arr));
    });
    connect(m_client, &ChatClient::messageSent, this, [this](const QJsonObject& msg){
        emit messageSent(QVariant::fromValue(msg));
    });

    connect(m_client, &ChatClient::messageReceived, this, [this](const QJsonObject& msg){
        emit messageReceived(QVariant::fromValue(msg));
    });
    connect(m_client, &ChatClient::readReceiptReceived, this, [this](const QJsonObject& rec){
        emit readReceiptReceived(QVariant::fromValue(rec));
    });
}

void QMLChatClient::configure(const QString& baseUrl, qint64 userId, const QString& role) {
    ChatClient::Role r = (role.toLower() == "patient") ? ChatClient::Role::Patient : ChatClient::Role::Doctor;
    m_client->configure(baseUrl, userId, r);
}

void QMLChatClient::connectWebSocket() {
    m_client->connectWebSocket();
}

void QMLChatClient::disconnectWebSocket() {
    m_client->disconnectWebSocket();
}

void QMLChatClient::createConversation(qint64 doctorId, qint64 patientId) {
    m_client->createConversation(doctorId, patientId);
}

void QMLChatClient::listMyConversations() {
    m_client->listMyConversations();
}

void QMLChatClient::listMessages(qint64 conversationId, qint64 beforeId, int limit) {
    m_client->listMessages(conversationId, beforeId, limit);
}

void QMLChatClient::sendMessage(qint64 conversationId, const QString& content) {
    m_client->sendMessage(conversationId, "text", content);
}

void QMLChatClient::markRead(qint64 messageId) {
    m_client->markRead(messageId);
}

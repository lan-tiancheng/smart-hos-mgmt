#include "ClientSession.h"
#include "common/Protocol.h"
#include <QJsonDocument>
#include <QDebug>

ClientSession::ClientSession(QObject* parent) : QObject(parent) {}

bool ClientSession::start(qintptr socketDescriptor) {
    socket_ = new QTcpSocket(this);
    if (!socket_->setSocketDescriptor(socketDescriptor)) return false;
    connect(socket_, &QTcpSocket::readyRead, this, &ClientSession::onReadyRead);
    connect(socket_, &QTcpSocket::disconnected, this, &ClientSession::onDisconnected);
    return true;
}

void ClientSession::onReadyRead() {
    buffer_.append(socket_->readAll());
    int idx;
    while ((idx = buffer_.indexOf('\n')) != -1) {
        QByteArray line = buffer_.left(idx);
        buffer_.remove(0, idx + 1);
        processLine(line);
    }
}

void ClientSession::processLine(const QByteArray& line) {
    QJsonParseError err;
    auto doc = QJsonDocument::fromJson(line, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        QJsonObject resp = Protocol::error("unknown", 400, "invalid json");
        socket_->write(Protocol::toLine(resp));
        return;
    }
    QJsonObject req = doc.object();
    QJsonObject resp = router_.route(req);
    socket_->write(Protocol::toLine(resp));
}

void ClientSession::onDisconnected() {
    socket_->deleteLater();
    deleteLater();
}
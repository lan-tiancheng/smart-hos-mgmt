#include "ClientSocket.h"
#include "common/Protocol.h"
#include <QJsonDocument>

ClientSocket::ClientSocket(QObject* parent) : QObject(parent) {
    connect(&sock_, &QTcpSocket::readyRead, this, &ClientSocket::onReadyRead);
}

void ClientSocket::connectToServer(const QString& host, quint16 port) {
    sock_.connectToHost(host, port);
}

void ClientSocket::send(const QJsonObject& obj) {
    sock_.write(Protocol::toLine(obj));
}

void ClientSocket::onReadyRead() {
    buf_.append(sock_.readAll());
    int idx;
    while ((idx = buf_.indexOf('\n')) != -1) {
        QByteArray line = buf_.left(idx);
        buf_.remove(0, idx + 1);
        auto doc = QJsonDocument::fromJson(line);
        if (doc.isObject() && onMessage_) onMessage_(doc.object());
    }
}
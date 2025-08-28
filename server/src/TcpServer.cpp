#include "TcpServer.h"
#include "ClientSession.h"
#include <QHostAddress>
#include <QDebug>

TcpServer::TcpServer(QObject* parent) : QTcpServer(parent) {}

bool TcpServer::start(quint16 port) {
    if (!listen(QHostAddress::Any, port)) {
        qCritical() << "Listen failed:" << errorString();
        return false;
    }
    return true;
}

void TcpServer::incomingConnection(qintptr socketDescriptor) {
    auto* session = new ClientSession(this);
    if (!session->start(socketDescriptor)) {
        qWarning() << "Failed to start session";
        session->deleteLater();
    }
}
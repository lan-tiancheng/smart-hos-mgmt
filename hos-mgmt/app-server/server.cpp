#include "server.h"
#include "qtcpsocket.h"
#include <QDebug>

Server::Server(QObject *parent)
    : QObject(parent)
{
    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, &QTcpServer::newConnection,
            this, &Server::newConnection);
}

void Server::startServer()
{
    quint16 port = 8080;
    const QByteArray envPort = qgetenv("HOS_SERVER_PORT");
    if (!envPort.isEmpty()) {
        bool ok = false;
        quint16 p = static_cast<quint16>(envPort.toUShort(&ok));
        if (ok && p > 0) port = p;
    }

    if (!m_tcpServer->listen(QHostAddress::Any, port)) {
        qWarning() << "Server could not start on port" << port << ":" << m_tcpServer->errorString();
    } else {
        qInfo() << "Server started! Listening on port" << m_tcpServer->serverPort() << "...";
    }
}

void Server::newConnection()
{
    QTcpSocket *clientSocket = m_tcpServer->nextPendingConnection();
    qDebug() << "New client connected from:" << clientSocket->peerAddress().toString();
    // TODO: 在这里处理客户端请求
}

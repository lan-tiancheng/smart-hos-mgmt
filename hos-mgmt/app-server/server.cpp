#include "server.h"
#include "qtcpsocket.h"
#include <QDebug>

Server::Server(QObject *parent)
    : QObject(parent)
{
    m_tcpServer = new QTcpServer(this);
    // 连接 newConnection 信号到 newConnection 槽
    connect(m_tcpServer, &QTcpServer::newConnection,
            this, &Server::newConnection);
}

void Server::startServer()
{
    if (!m_tcpServer->listen(QHostAddress::Any, 8080)) {
        qDebug() << "Server could not start! Error:" << m_tcpServer->errorString();
    } else {
        qDebug() << "Server started! Listening on port 8080...";
    }
}

void Server::newConnection()
{
    QTcpSocket *clientSocket = m_tcpServer->nextPendingConnection();
    qDebug() << "New client connected from:" << clientSocket->peerAddress().toString();

    // TODO: 在这里处理客户端请求
}

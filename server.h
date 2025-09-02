#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void startServer();

private slots:
    void newConnection();

private:
    QTcpServer *m_tcpServer;
};

#endif // SERVER_H

#pragma once
#include <QTcpServer>

class TcpServer : public QTcpServer {
    Q_OBJECT
public:
    explicit TcpServer(QObject* parent = nullptr);
    bool start(quint16 port);

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

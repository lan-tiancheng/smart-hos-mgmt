#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "DataType.h"
#include "tcpthread.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);

    void set_st_client(client *c_indoor);
    void set_st_service(service *s_indoor);

    client *client_indoor;
    service *service_indoor;

private:
    void incomingConnection(int handle);
    TcpThread *tcpthread;

signals:
    void getData();
    void sndQues(QString);

public slots:
    void getDataSlots();
    void revQues(QString);

};

#endif // TCPSERVER_H

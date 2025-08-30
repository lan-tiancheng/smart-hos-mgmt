#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>
#include <QtNetwork>
#include <QTcpSocket>
#include "DataType.h"

class TcpThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpThread(int handle,QObject *parent = 0);

    void set_st_client(client *c_indoor);
    void set_st_service(service *s_indoor);

signals:
    void getdata();

public slots:
    void mes_from_client();
    void recQuestion(QString i);

protected:
    void run();
    //void mes_to_client(service *s,QString type);

private:
    QTcpSocket *tcpsocket;
    int isrunning;
    client *client_indoor;
    service *service_indoor;

};

#endif // TCPTHREAD_H

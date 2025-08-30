#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
}
void TcpServer::incomingConnection(int handle){
    tcpthread = new TcpThread(handle,this);
    connect(tcpthread,SIGNAL(finished()),tcpthread,SLOT(deleteLater()));
    connect(tcpthread,SIGNAL(getdata()),this,SLOT(getDataSlots()));

    connect(this,SIGNAL(sndQues(QString)),tcpthread,SLOT(recQuestion(QString)));

    tcpthread->set_st_client(client_indoor);
    tcpthread->set_st_service(service_indoor);
    tcpthread->start();
}
void TcpServer::set_st_client(client *c_indoor){
    client_indoor = c_indoor;

}

void TcpServer::set_st_service(service *s_indoor){
    service_indoor = s_indoor;

}

void TcpServer::getDataSlots(){
    emit getData();
}

void TcpServer::revQues(QString i)
{
    emit sndQues(i);
}

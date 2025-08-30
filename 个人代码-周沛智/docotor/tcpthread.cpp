#include "tcpthread.h"

TcpThread::TcpThread(int Handle,QObject *parent) :
    QThread(parent)
{
    tcpsocket = new QTcpSocket(this);
    tcpsocket->setSocketDescriptor(Handle);
    connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(mes_from_client()));
    isrunning = 1;
}

void TcpThread::run(){
    while(isrunning){
        sleep(1);
    }
}

void TcpThread::mes_from_client()
{
    QDataStream in(tcpsocket);
    in.setVersion(QDataStream::Qt_5_0);
    quint8 bt0,bt1,bt2;
    in>>bt0>>bt1>>bt2;
    qDebug()<<bt0<<bt1<<bt2;
    client_indoor->ecgI = ((bt0<<16)+(bt1<<8)+bt2);
    client_indoor->ecgII = ((bt0<<16)+(bt1<<8)+bt2);
    client_indoor->ecgIII = 0;
    client_indoor->ecgAVL = ((bt0<<16)+(bt1<<8)+bt2)/2;
    client_indoor->ecgAVR = -((bt0<<16)+(bt1<<8)+bt2);
    client_indoor->ecgAVF = ((bt0<<16)+(bt1<<8)+bt2)/2;
    client_indoor->ecgV1 = ((bt0<<16)+(bt1<<8)+bt2);
    client_indoor->ecgV2 = ((bt0<<16)+(bt1<<8)+bt2);
    client_indoor->ecgV3 = ((bt0<<16)+(bt1<<8)+bt2);
    client_indoor->ecgV4 = ((bt0<<16)+(bt1<<8)+bt2);
    client_indoor->ecgV5 = ((bt0<<16)+(bt1<<8)+bt2);
    client_indoor->ecgV6 = ((bt0<<16)+(bt1<<8)+bt2);

    emit getdata();
    //tcpsocket->write("sym");

}

//void TcpThread::mes_to_client(service *s,QString type){
//    QByteArray block;
//    QDataStream out(&block,QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_0);

//    out << type;

//    if(type == "INDOOR"){
//        out << s->Server_IP
//            << s->Weather
//            << s->Command;
//    }

//    out.device()->seek(0);
//    tcpsocket->write(block);
//}


void TcpThread::set_st_client(client *c_indoor){
    client_indoor = c_indoor;

}

void TcpThread::set_st_service(service *s_indoor){
    service_indoor = s_indoor;

}

void TcpThread::recQuestion(QString i)
{
    char*  ch;
    QByteArray ba = i.toLatin1();
    ch=ba.data();

    tcpsocket->write(ch);
    qDebug()<<i;
}

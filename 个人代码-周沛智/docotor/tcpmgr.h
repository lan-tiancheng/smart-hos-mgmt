#ifndef TCPMGR_H
#define TCPMGR_H


#include <QTcpSocket>
#include "singleton.h"
#include "global.h"
#include <QJsonArray>
#include <functional>
#include <QObject>
class TcpMgr:public QObject, public Singleton<TcpMgr>,
        public std::enable_shared_from_this<TcpMgr>
{
    Q_OBJECT
public:
    TcpMgr();
private:
    QTcpSocket _socket;
    QString _host;
    uint16_t _port;
    QByteArray _buffer;
    bool _b_recv_pending;
    quint16 _message_id;
    quint16 _message_len;
    void initHandlers();
    void handleMsg(ReqId id, int len, QByteArray data);
    QMap<ReqId, std::function<void(ReqId id, int len, QByteArray data)>> _handlers;
public slots:
    void slot_tcp_connect(ServerInfo);
    void slot_send_data(ReqId reqId, QString data);
signals:
    void sig_con_success(bool bsuccess);
    void sig_send_data(ReqId reqId, QString data);

    void sig_login_failed(int);
    void sig_swich_chatdlg();
    void sig_edit_doctor_selfintr_failed();
    void dataUpdated();
    void apperSuccess();








    void sig_make_first_list(QVector<QVector<QString>> data);
};

#endif // TCPMGR_H

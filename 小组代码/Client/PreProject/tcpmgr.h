#ifndef TCPMGR_H
#define TCPMGR_H

#include "userdata.h"
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

    void sig_friend_apply(std::shared_ptr<AddFriendApply>);//新添加
    void sig_add_auth_friend(std::shared_ptr<AuthInfo>);
    void sig_auth_rsp(std::shared_ptr<AuthRsp>);
    void sig_text_chat_msg(std::shared_ptr<TextChatMsg> msg);
    void sig_user_search(std::shared_ptr<SearchInfo>);
};

#endif // TCPMGR_H

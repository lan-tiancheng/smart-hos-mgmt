#ifndef HTTPMGR_H
#define HTTPMGR_H

#include"singleton.h"
#include<QString>
#include<QUrl>
#include<QObject>
#include<QNetworkAccessManager>
#include<QJsonObject>
#include<QJsonDocument>
//CRTP实现
class HttpMgr:public QObject,public Singleton<HttpMgr>,public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url,QJsonObject json,ReqId req_id,Moudles mod);

private:
    friend class Singleton<HttpMgr>;

    HttpMgr();
    QNetworkAccessManager _manager;

private slots:
    void slotHttpFinish(ReqId id,QString res,ErrorCode err,Moudles mod);
signals:
    void sigHttpFinish(ReqId id,QString res,ErrorCode err,Moudles mod);
    void sigRegModFinish(ReqId id,QString res,ErrorCode err);
    void sig_reset_mod_finish(ReqId id,QString res,ErrorCode err);
    void sig_login_mod_finish(ReqId id,QString res,ErrorCode err);
    void sig_updata_info_reg_mod_finish(ReqId id,QString res,ErrorCode err);
};

#endif // HTTPMGR_H

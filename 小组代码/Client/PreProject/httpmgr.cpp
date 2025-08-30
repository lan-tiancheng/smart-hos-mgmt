#include "httpmgr.h"



HttpMgr::~HttpMgr()
{

}

HttpMgr::HttpMgr()
{
    connect(this,&HttpMgr::sigHttpFinish,this,&HttpMgr::slotHttpFinish);
}



void HttpMgr::slotHttpFinish(ReqId id, QString res, ErrorCode err, Moudles mod)
{
    if(mod==Moudles::REGISTERMOD){
        //发送信号通知指定模块http响应结束
        emit sigRegModFinish(id,res,err);
    }
    if(mod==Moudles::RESETMOD){
        emit sig_reset_mod_finish(id,res,err);
    }

    if(mod==Moudles::LOGINMOD){
        emit sig_login_mod_finish(id,res,err);
    }

    if(mod==Moudles::UPDATAINFOATREG){
        emit sig_updata_info_reg_mod_finish(id,res,err);
    }
}
void HttpMgr::PostHttpReq(QUrl url,QJsonObject json,ReqId req_id,Moudles mod)
{
    QByteArray data=QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(data.length()));
    auto self=shared_from_this();
    QNetworkReply* reply=_manager.post(request,data);

    QObject::connect(reply,&QNetworkReply::finished,[self,reply,req_id,mod](){
        if(reply->error()!=QNetworkReply::NoError){
            qDebug()<<reply->errorString();
            //发送信号完成
            emit self->sigHttpFinish(req_id,"",ErrorCode::ERR_NETWORK,mod);
            reply->deleteLater();
            return;
        }

        //No error
        QString res=reply->readAll();

        emit self->sigHttpFinish(req_id,res,ErrorCode::SUCCESS,mod);
        reply->deleteLater();
        return;
    });
}

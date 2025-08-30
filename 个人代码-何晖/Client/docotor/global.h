#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include "QStyle"
#include<QRegularExpression>
#include <memory>
#include<iostream>
#include<mutex>
#include<QByteArray>
#include<QNetworkReply>
#include<QJsonObject>
#include<QDir>
#include<QSettings>

extern std::function<void(QWidget*)> repolish;

extern std::function<QString(QString)> xorString;
enum ReqId{
    ID_GET_VARIFY_CODE = 1001, //获取验证码
    ID_REG_USER = 1002, //注册用户
    ID_RESET_PWD = 1003, //重置密码
    ID_LOGIN_USER = 1004, //用户登录
    ID_CHAT_LOGIN = 1005, //登陆聊天服务器
    ID_CHAT_LOGIN_RSP= 1006, //登陆聊天服务器回包
    ID_SEARCH_USER_REQ = 1007, //用户搜索请求
    ID_SEARCH_USER_RSP = 1008, //搜索用户回包
    ID_ADD_FRIEND_REQ = 1009,  //添加好友申请
    ID_ADD_FRIEND_RSP = 1010, //申请添加好友回复
    ID_NOTIFY_ADD_FRIEND_REQ = 1011,  //通知用户添加好友申请
    ID_AUTH_FRIEND_REQ = 1013,  //认证好友请求
    ID_AUTH_FRIEND_RSP = 1014,  //认证好友回复
    ID_NOTIFY_AUTH_FRIEND_REQ = 1015, //通知用户认证好友申请
    ID_TEXT_CHAT_MSG_REQ  = 1017,  //文本聊天信息请求
    ID_TEXT_CHAT_MSG_RSP  = 1018,  //文本聊天信息回复
    ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019, //通知用户文本聊天信息
    ID_USER_ADD_INFO=1020,
    ID_DOCTOR_LOGIN=1021,//医生登录
    ID_DOCTOR_REV=1022,//医生登录的回包
    ID_DOCTOR_SEND_EDIT_SELFINFO=1023,//医生修改个人信息
    ID_DOCTOR_CALL_PAINTINFO=1024,//医生申请病人挂号信息
    ID_WRITE_PAINT_CHECKRESULT=1025,//医生写诊断
    ID_WRITE_PAINT_ADVICE=1026,
    ID_hospital=1027,

};

enum Moudles{
    REGISTERMOD=0,
    RESETMOD=1,
    LOGINMOD=2,
    UPDATAINFOATREG=3,
};

enum TipErr{
    TIP_SUCCESS = 0,
    TIP_EMAIL_ERR = 1,
    TIP_PWD_ERR = 2,
    TIP_CONFIRM_ERR = 3,
    TIP_PWD_CONFIRM = 4,
    TIP_VARIFY_ERR = 5,
    TIP_USER_ERR = 6,
    TIP_USER_YEAR_ERR=7,
    TIP_USER_data_ERR=8,
    TIP_IDCARD_ERR=9,
    TIP_PHONE_ERR=10,
};

enum ClickLbState{
    Normal = 0,
    Selected = 1
};

enum ErrorCode{
    SUCCESS=0,
    ERR_JSON=1,
    ERR_NETWORK=2,
};

struct ServerInfo{
    QString Host;
    QString Port;
    QString Token;
    int Uid;
};

extern QString gate_url_prefix;

#endif // GLOBAL_H

#ifndef SPEECH_H
#define SPEECH_H

#include <QObject>

#include "http.h"

#include <QFile>

#include <QMap>

#include <QByteArray>
#include <QMessageBox>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QHostInfo>

#include <QDebug>

#include <QMessageBox>
//获取access_token相关
const QString BaiduSpeechUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString BaiduSpeechClientID = "rppVhHTVvkrE0KNrmdsbiiuJ";
const QString BaiduSpeechClientSecret = "duQ4I1SF3Rkfw1xqmejH5tMrXGW9CYXn";

//普通话测试
const QString BaiduSpeechSatrtUrl = "http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";


class Speech : public QObject
{
    Q_OBJECT
public:
    explicit Speech(QObject *parent = nullptr);

signals:

public slots:

public:
    QString speechIdentify(QString audioFile);

private:
    QString getJsonValue(QByteArray &data, QString &key);

private:
    QString accessToken;

};

#endif // SPEECH_H

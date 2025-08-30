#include "speech.h"

Speech::Speech(QObject *parent) : QObject(parent)
{

}

QString Speech::speechIdentify(QString audioFile)
{
    if(audioFile.isEmpty())
    {
        QMessageBox::warning(NULL,"警告(speech)","文件不存在");
        return QString("");
    }

    /* 组装access token的Url */
    QString TokenUrl = QString(BaiduSpeechUrl).arg(BaiduSpeechClientID).arg(BaiduSpeechClientSecret);

    /**************获取token值时不用参数，但自定义http函数需要传入**************/
    QMap<QString, QString>header;
    header.insert(QString("Content-Type"),QString("audio/pcm;rate=16000"));//Content-Type: audio/pcm;rate=16000键值对       PCM方式上传音频

    QByteArray requestData;//用于存放上传的数据，即录音信息
    QByteArray replyData;//定义存放Http请求结果的字节数组
    /**************获取token值不用的参数，但自定义http_postRequst函数需要传入**************/

    //获取token值，获取一次使用30天
    if(accessToken.isEmpty() == true)//如果还未获取token值
    {
        bool ret = Http::http_postRequst(TokenUrl, header, requestData, replyData);
        if(ret)
        {
            QString key = "access_token";
            accessToken = getJsonValue(replyData,key);
            replyData.clear();
            qDebug() << "获取的token ——" << accessToken;//调试
        }
    }


    /* 识别语音请求    将获取的token值组装到新的url中用于发送语音识别请求*/
    QString speechUrl = QString(BaiduSpeechSatrtUrl).arg(QHostInfo::localHostName()).arg(accessToken);

    qDebug()<<"speechUrl"<<speechUrl;

    /* 把录音文件转换成QByteArray */
    QFile file;
    file.setFileName(audioFile);//获取保存的录音文件
    file.open(QIODevice::ReadOnly);
    requestData = file.readAll();//读取录音文件中的内容
    file.close();

    if(requestData.isEmpty())
    {
        return QString("语音数据为空");
    }

    /* 再次发送请求       语音识别请求 */
    bool ret = Http::http_postRequst(speechUrl, header, requestData, replyData);
    if(ret)
    {
        QString key = "result";
        //解析获取的json信息为QString
          qDebug()<<"hello xjh "<<replyData;
        QString text = getJsonValue(replyData,key);//自定义函数,下方
        return text;//返回识别后的结果
    }else{
        QMessageBox::warning(NULL,"警告(speech)","识别失败");
    }
    return QString("");
}


QString Speech::getJsonValue(QByteArray &data, QString &key)    //自定义json解析函数
{
    QJsonParseError parseError;//json错误判定对象
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data,&parseError);//转换成json文档
    QString retStr = "";
    if(parseError.error == QJsonParseError::NoError)//判断无误
    {
        if(jsonDocument.isObject())
        {
            /*  将jsonDocument 转换成json对象 */
            QJsonObject jsonObj = jsonDocument.object();

            if(jsonObj.contains(key))
            {
                QJsonValue jsonVal = jsonObj.value(key);
                if(jsonVal.isString())
                {
                    return jsonVal.toString();
                }
                else if(jsonVal.isArray())//检查是否为数组
                {
                    QJsonArray arr = jsonVal.toArray();
                    for(int index = 0; index<arr.size(); index++)
                    {
                        QJsonValue subValue = arr.at(index);
                        if(subValue.isString())
                        {
                            retStr += subValue.toString()+" ";
                        }
                    }
                    return retStr;
                }
            }
            else
            {
                qDebug() << "不包含关键字：" << key;
            }//contains(key)
        }
        else
        {
            qDebug() << "不是json对象";
        }//isObject
    }
    else
    {
        qDebug() << "未成功解析JSON";
    }//NoError
    qDebug() << "未成功解析JSON：" << data.data();
    return QString("");
}

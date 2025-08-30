#include "tcpmgr.h"
#include <QAbstractSocket>
#include<QJsonDocument>
#include"usermgr.h"

TcpMgr::TcpMgr():_host(""),_port(0),_b_recv_pending(false),_message_id(0),_message_len(0)
{
    QObject::connect(&_socket, &QTcpSocket::connected, [&]() {
           qDebug() << "Connected to server!";
           // 连接建立后发送消息
            emit sig_con_success(true);
       });

       QObject::connect(&_socket, &QTcpSocket::readyRead, [&]() {
           // 当有数据可读时，读取所有数据
           // 读取所有数据并追加到缓冲区
           _buffer.append(_socket.readAll());

           QDataStream stream(&_buffer, QIODevice::ReadOnly);
           stream.setVersion(QDataStream::Qt_5_0);

           forever {
                //先解析头部
               if(!_b_recv_pending){
                   // 检查缓冲区中的数据是否足够解析出一个消息头（消息ID + 消息长度）
                   if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2)) {
                       return; // 数据不够，等待更多数据
                   }

                   // 预读取消息ID和消息长度，但不从缓冲区中移除
                   stream >> _message_id >> _message_len;

                   //将buffer 中的前四个字节移除
                   _buffer = _buffer.mid(sizeof(quint16) * 2);

                   // 输出读取的数据
                   qDebug() << "Message ID:" << _message_id << ", Length:" << _message_len;

               }

                //buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
               if(_buffer.size() < _message_len){
                    _b_recv_pending = true;
                    return;
               }

               _b_recv_pending = false;
               // 读取消息体
               QByteArray messageBody = _buffer.mid(0, _message_len);
                qDebug() << "receive body msg is " << messageBody ;

               _buffer = _buffer.mid(_message_len);
               handleMsg(ReqId(_message_id),_message_len, messageBody);
           }

       });


       // 处理错误（适用于Qt 5.15之前的版本）
        QObject::connect(&_socket, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
                            [&](QTcpSocket::SocketError socketError) {
               qDebug() << "Error:" << _socket.errorString() ;
               switch (socketError) {
                   case QTcpSocket::ConnectionRefusedError:
                       qDebug() << "Connection Refused!";
                       emit sig_con_success(false);
                       break;
                   case QTcpSocket::RemoteHostClosedError:
                       qDebug() << "Remote Host Closed Connection!";
                       break;
                   case QTcpSocket::HostNotFoundError:
                       qDebug() << "Host Not Found!";
                       emit sig_con_success(false);
                       break;
                   case QTcpSocket::SocketTimeoutError:
                       qDebug() << "Connection Timeout!";
                       emit sig_con_success(false);
                       break;
                   case QTcpSocket::NetworkError:
                       qDebug() << "Network Error!";
                       break;
                   default:
                       qDebug() << "Other Error!";
                       break;
               }
         });

        // 处理连接断开
        QObject::connect(&_socket, &QTcpSocket::disconnected, [&]() {
            qDebug() << "Disconnected from server.";
        });

        QObject::connect(this, &TcpMgr::sig_send_data, this, &TcpMgr::slot_send_data);
        initHandlers();

}

void TcpMgr::initHandlers()
{
    //auto self = shared_from_this();
    _handlers.insert(ID_CHAT_LOGIN_RSP, [this](ReqId id, int len, QByteArray data){
        Q_UNUSED(len);
        qDebug()<< "handle id is "<< id << " data is " << data;
        // 将QByteArray转换为QJsonDocument
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        // 检查转换是否成功
        if(jsonDoc.isNull()){
           qDebug() << "Failed to create QJsonDocument.";
           return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if(!jsonObj.contains("error")){
            int err = ErrorCode::ERR_JSON;
            qDebug() << "Login Failed, err is Json Parse Err" << err ;
            emit sig_login_failed(err);
            return;
        }

        int err = jsonObj["error"].toInt();
        if(err != ErrorCode::SUCCESS){
            qDebug() << "Login Failed, err is " << err ;
            emit sig_login_failed(err);
            return;
        }

        QVector<QVector<QString>> pediatricsData;
        QVector<QVector<QString>> internalMedicineData;
        QVector<QVector<QString>> surgeryData;
        QVector<QVector<QString>> gynecologyData;
        QVector<QVector<QString>> dermatologyData;

        QJsonArray departments = jsonObj["departments"].toArray();

        for (const QJsonValue& value : departments) {
            QJsonObject departmentObj = value.toObject();
            QString departmentName = departmentObj["name"].toString();

            QJsonArray doctorsArray = departmentObj["doctors"].toArray();
            QVector<QVector<QString>>* targetData = nullptr;

            // 根据科室名称分配到相应的vector
            if (departmentName == "儿科") {
                targetData = &pediatricsData;
            } else if (departmentName == "内科") {
                targetData = &internalMedicineData;
            } else if (departmentName == "外科") {
                targetData = &surgeryData;
            } else if (departmentName == "妇科") {
                targetData = &gynecologyData;
            } else if (departmentName == "皮肤科") {
                targetData = &dermatologyData;
            }

            if (targetData != nullptr) {
                for (const QJsonValue& doctorValue : doctorsArray) {
                    QJsonObject obj = doctorValue.toObject();
                    QVector<QString> row;
                    row.append(QString::number(obj["id"].toInt()));
                    row.append(QString::number(obj["workID"].toInt()));
                    row.append(obj["name"].toString());
                    row.append(obj["pwd"].toString());
                    row.append(obj["email"].toString());
                    int sex = obj["sex"].toInt();
                    QString sexStr;
                    if (sex == 0) {
                        sexStr = "女";
                    } else if (sex == 1) {
                        sexStr = "男";
                    } else {
                        sexStr = "其他";
                    }
                    row.append(sexStr);
                    row.append(QString::number(obj["year"].toInt()));
                    row.append(QString::number(obj["month"].toInt()));
                    row.append(QString::number(obj["day"].toInt()));
                    row.append(obj["IDcard"].toString());
                    row.append(obj["phone"].toString());
                    row.append(QString::number(obj["department_id"].toInt()));
                    row.append(obj["intr"].toString());
                    targetData->append(row);
                }
            }
        }

        // 现在每个科室的数据都已经存储在对应的 QVector<QVector<QString>> 中
        qDebug() << "儿科数据：" << pediatricsData;
        qDebug() << "内科数据：" << internalMedicineData;
        qDebug() << "外科数据：" << surgeryData;
        qDebug() << "妇科数据：" << gynecologyData;
        qDebug() << "皮肤科数据：" << dermatologyData;

        QVector<QVector<QString>> guahaoData;

           // 提取 guahaoList 数组
           QJsonArray guahaoList = jsonObj["guahaoList"].toArray();

           for (const QJsonValue &value : guahaoList) {
               QJsonObject obj = value.toObject();
               QVector<QString> row;
               row.append(QString::number(obj["id"].toInt()));
               row.append(QString::number(obj["doctoruid"].toInt()));
               row.append(QString::number(obj["useruid"].toInt()));
               row.append(obj["doctorname"].toString());
               row.append(obj["username"].toString());
               row.append(obj["useremail"].toString());
               int sex = obj["usersex"].toInt();
               QString sexStr;
               if (sex == 0) {
                   sexStr = "女";
               } else if (sex == 1) {
                   sexStr = "男";
               } else {
                   sexStr = "其他";
               }
               row.append(sexStr);
               row.append(obj["userage"].toString());
               row.append(obj["userorderdata"].toString());
               row.append(obj["userinfo"].toString());
               row.append(obj["checkresult"].toString());
               row.append(obj["chufang"].toString());

               guahaoData.append(row);
           }

           // 将挂号信息存储到 UserMgr 单例中
           UserMgr::GetInstance()->setGuahaoData(guahaoData);

           // 这里可以进一步处理 guahaoData 或者触发 UI 更新等操作
           qDebug() << "Guahao data stored in UserMgr:";
           for (const auto &row : guahaoData) {
               qDebug() << row;
           }
           QVector<QVector<QString>> hospitalizationData;

               // 提取 hospitalizationList 数组
               QJsonArray hospitalizationList = jsonObj["hospitalizationList"].toArray();

               for (const QJsonValue &value : hospitalizationList) {
                   QJsonObject obj = value.toObject();
                   QVector<QString> row;
                   row.append(QString::number(obj["id"].toInt()));
                   row.append(QString::number(obj["doctor_uid"].toInt()));
                   row.append(QString::number(obj["patient_uid"].toInt()));
                   row.append(obj["patient_name"].toString());
                   row.append(obj["bed_number"].toString());
                   row.append(obj["admission_data"].toString());
                   row.append(obj["doctorname"].toString());
                   row.append(obj["roomnum"].toString());

                   hospitalizationData.append(row);
               }

               // 将住院信息存储到 UserMgr 单例中
               UserMgr::GetInstance()->setHospitalizationData(hospitalizationData);

               // 这里可以进一步处理 hospitalizationData 或者触发 UI 更新等操作
               qDebug() << "Hospitalization data stored in UserMgr:";
               for (const auto &row : hospitalizationData) {
                   qDebug() << row;
               }

               QJsonObject userInfoJson = jsonObj["userInfo"].toObject();

               UserInfoNew userInfo;
               userInfo.id = userInfoJson["id"].toInt();
               userInfo.uid = userInfoJson["uid"].toInt();
               userInfo.name = userInfoJson["name"].toString();
               userInfo.email = userInfoJson["email"].toString();
               userInfo.pwd = userInfoJson["pwd"].toString();
               userInfo.realName = userInfoJson["realName"].toString();
               userInfo.sex = userInfoJson["sex"].toInt();
               userInfo.year = userInfoJson["year"].toString();
               userInfo.month = userInfoJson["month"].toString();
               userInfo.data = userInfoJson["data"].toString();
               userInfo.IDcard = userInfoJson["IDcard"].toString();
               userInfo.phone = userInfoJson["phone"].toString();

               // 存储到 UserMgr
               UserMgr::GetInstance()->setUserInfo(userInfo);

               // 根据需要进一步处理数据，比如更新 UI 或存储到某个地方
               qDebug() << "User Info stored in UserMgr:";
               qDebug() << "User ID:" << userInfo.id;
               qDebug() << "UID:" << userInfo.uid;
               qDebug() << "Name:" << userInfo.name;
               qDebug() << "Email:" << userInfo.email;
               qDebug() << "Real Name:" << userInfo.realName;
               qDebug() << "Sex:" << userInfo.sex;
               qDebug() << "Year:" << userInfo.year;
               qDebug() << "Month:" << userInfo.month;
               qDebug() << "Data:" << userInfo.data;
               qDebug() << "IDcard:" << userInfo.IDcard;
               qDebug() << "Phone:" << userInfo.phone;
        UserMgr::GetInstance()->SetToken(jsonObj["token"].toString());
        UserMgr::GetInstance()->setPediatricsData(pediatricsData);
        UserMgr::GetInstance()->setInternalMedicineData(internalMedicineData);
        UserMgr::GetInstance()->setSurgeryData(surgeryData);
        UserMgr::GetInstance()->setGynecologyData(gynecologyData);
        UserMgr::GetInstance()->setDermatologyData(dermatologyData);
        emit sig_swich_chatdlg();
    });
}

void TcpMgr::handleMsg(ReqId id, int len, QByteArray data)
{
   auto find_iter =  _handlers.find(id);
   if(find_iter == _handlers.end()){
        qDebug()<< "not found id ["<< id << "] to handle";
        return ;
   }

   find_iter.value()(id,len,data);
}


void TcpMgr::slot_tcp_connect(ServerInfo si)
{
    qDebug()<< "receive tcp connect signal";
    // 尝试连接到服务器
    qDebug() << "Connecting to server...";
    _host = si.Host;
    _port = static_cast<uint16_t>(si.Port.toUInt());
    _socket.connectToHost(si.Host, _port);
}

void TcpMgr::slot_send_data(ReqId reqId, QString data)
{
    uint16_t id = reqId;

    // 将字符串转换为UTF-8编码的字节数组
    QByteArray dataBytes = data.toUtf8();

    // 计算长度（使用网络字节序转换）
    quint16 len = static_cast<quint16>(dataBytes.size());

    // 创建一个QByteArray用于存储要发送的所有数据
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    // 设置数据流使用网络字节序
    out.setByteOrder(QDataStream::BigEndian);

    // 写入ID和长度
    out << id << len;

    // 添加字节数组数据
    block.append(dataBytes);

    // 发送数据
    _socket.write(block);

    qDebug() << "Sending data: id=" << id << "len=" << len << "data=" << dataBytes;
}

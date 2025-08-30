#include "advice.h"
#include "tcpmgr.h"
#include "ui_advice.h"
#include <QMessageBox>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <usermgr.h>

advice::advice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::advice)
{
    ui->setupUi(this);

    // 连接按钮点击信号到槽函数
    connect(ui->buttonConfirm, &QPushButton::clicked, this, &advice::on_buttonConfirm_clicked);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &advice::on_buttonCancel_clicked);
}

advice::~advice()
{
    delete ui;
}

void advice::on_buttonConfirm_clicked()
{

    // 获取文本框中的内容
    QString resultText = ui->textEditResult->toPlainText();
    QJsonObject jsonObj;
    jsonObj["doctoruid"]=UserMgr::GetInstance()->getUid();
    qDebug()<<jsonObj["doctoruid"].toInt();
    jsonObj["result"]=resultText;
    jsonObj["id"]=UserMgr::GetInstance()->getguahaoidEdit();

    QJsonDocument doc(jsonObj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    //发送tcp请求给chat server
    emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_WRITE_PAINT_ADVICE, jsonString);

    // 显示确认消息
    QMessageBox::information(this, "确认", QString("确认医嘱:\n%1").arg(resultText));

    // 关闭对话框
    this->accept(); // 使用 QDialog 的 accept() 方法关闭对话框并接受操作
}

void advice::on_buttonCancel_clicked()
{
    this->reject(); // 使用 QDialog 的 reject() 方法关闭对话框而不接受操作
}

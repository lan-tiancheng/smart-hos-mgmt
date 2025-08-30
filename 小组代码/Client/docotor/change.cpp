#include "change.h"
#include "ui_change.h"
#include <QMessageBox>
#include <QJsonDocument>  // 添加这个
#include <QJsonObject>    // 添加这个
#include"tcpmgr.h"
#include <sstream>  // 这里需要包含 sstream 头文件
#include"usermgr.h"
#include <iostream>
#include <string>

change::change(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change)
{
    ui->setupUi(this);
    connect(ui->pushButtonCommit, &QPushButton::clicked, this, &change::on_pushButtonCommit_clicked);
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_edit_doctor_selfintr_failed,this,&change::slot_edit_doctor_selfintr_failed);
    connect(TcpMgr::GetInstance().get(),&TcpMgr::dataUpdated,this,&change::slot_updata_success);
}

change::~change()
{
    delete ui;
}

void change::on_pushButtonCommit_clicked()
{
    QString departmentID=ui->lineEditName->text();



    int num;
     num = departmentID.toInt();
    QString department;
    department=getDepartmentName(num);

    QJsonObject jsonObj;
    jsonObj["uid"]=UserMgr::GetInstance()->getUid();
    qDebug()<<jsonObj["uid"].toInt();
    jsonObj["name"] = ui->lineEditID->text();
    jsonObj["department"] = ui->lineEditName->text();
    jsonObj["email"]=ui->lineEditOwnerID->text();
    jsonObj["intr"]=ui->textEditSummary->toPlainText();

    QJsonDocument doc(jsonObj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    //发送tcp请求给chat server
    emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_DOCTOR_SEND_EDIT_SELFINFO, jsonString);
    // 在这里处理数据更新逻辑
    // 例如：保存数据或进行其他操作

    // 发射数据更新信号


    // 显示提示框
    //QMessageBox::information(this, "修改成功", "数据已成功修改。");

    // 关闭当前窗口
    close();
}

void change::slot_edit_doctor_selfintr_failed()
{
    //to do :添加失败弹窗以及相应逻辑
}

void change::slot_updata_success()
{
    QMessageBox::information(this, "修改成功", "数据已成功修改。");

}

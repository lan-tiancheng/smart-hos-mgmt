#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    refreshRegister();
}

Register::~Register()
{
    delete ui;
}

void Register::refreshRegister()
{
    QStringList doctorList;
    query.exec("select id from doctor");
    while(query.next())
    {
        QString doc = query.value(0).toString();
        doctorList.append(doc);
    }
    ui->comboBox_2->clear();
    ui->comboBox_2->addItems(doctorList);
}

void Register::on_pushButton_clicked()
{
    QString pUserName = ui->lineEdit->text();
    QString pName = ui->lineEdit_2->text();
    QString pSex = ui->comboBox->currentText();
    int pAge = ui->spinBox->value();
    QString pHistory = ui->lineEdit_3->text();
    QString pCareer = ui->lineEdit_4->text();
    QString pPhone = ui->lineEdit_5->text();
    QString pDoctor = ui->comboBox_2->currentText();

    QString str=QString("insert into patient values('%1','%2','%3',%4,'%5','%6','%7','%8')")
            .arg(pUserName)
            .arg(pName)
            .arg(pSex)
            .arg(pAge)
            .arg(pHistory)
            .arg(pCareer)
            .arg(pPhone)
            .arg(pDoctor);

    if(!query.exec(str))
    {
        QMessageBox::about(this,"warning","用户名已存在,注册失败！");
    }
    else
    {
        QMessageBox::about(this,"warning","注册成功！");
    }
}

void Register::on_pushButton_3_clicked()
{
    QString dUserName = ui->lineEdit_7->text();
    QString dName = ui->lineEdit_8->text();
    QString dPhone = ui->lineEdit_9->text();
    QString dHospital = ui->lineEdit_10->text();

    QString str=QString("insert into doctor values('%1','%2','%3','%4')")
            .arg(dUserName)
            .arg(dName)
            .arg(dPhone)
            .arg(dHospital);

    if(!query.exec(str))
    {
        QMessageBox::about(this,"warning","用户名已存在,注册失败！");
    }
    else
    {
        QMessageBox::about(this,"warning","注册成功！");
        refreshRegister();
    }
}

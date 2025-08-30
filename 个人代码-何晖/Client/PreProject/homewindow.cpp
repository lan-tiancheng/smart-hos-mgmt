#include "homewindow.h"
#include "ui_homewindow.h"
#include "GlobalData.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIcon>
#include <QSqlQuery>
#include "pmainwindow.h"

//int GlobalData::isSearch=0;

HomeWindow::HomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWindow)
{
    ui->setupUi(this);


    QMargins margins = ui->lineEdit->textMargins();
    //prevent textcontent behind the button
    ui->lineEdit->setTextMargins(margins.left(), margins.top(), ui->btnsearch->width(), margins.bottom());
    ui->lineEdit->setPlaceholderText(QStringLiteral("请输入搜索内容"));

    connect(ui->btnsearch,SIGNAL(clicked()),this,SLOT(search()));
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::search(){
    QString strText = ui->lineEdit->text();
    if (1){
        MedicineSearchWindow * mdWd= new MedicineSearchWindow;
        mdWd->show();
        mdWd->sendText(strText);
        int info=1;
        emit infoSearchSend(info);

        //QMessageBox::information(this, QStringLiteral("搜索"), QStringLiteral("搜索内容为%1").arg(strText));
    }
}

void HomeWindow::on_medicalexpenseBtn_clicked()
{
    MedicalExpenseWd * meWd =new MedicalExpenseWd;
    meWd->show();
    emit infoMedicalExpenseSend();
}


void HomeWindow::on_quizBtn_clicked()
{
    quizWd *qzWd=new quizWd;
    qzWd->show();
}


void HomeWindow::on_tempBtn_clicked()
{
    QMessageBox::information(this, QStringLiteral("第三组"), QStringLiteral("何晖，周沛智，董崇未，陈凯，肖昊晴"));
}


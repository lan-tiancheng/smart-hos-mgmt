#include "medicalrecord.h"
#include "ui_medicalrecord.h"

MedicalRecord::MedicalRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedicalRecord)
{
    ui->setupUi(this);
    setUserInfo();
    loadMedicalData();
}

MedicalRecord::~MedicalRecord()
{
    delete ui;
}

void MedicalRecord::loadMedicalData()
{
    query.exec("select time from medicalrecord where user ='p2'");
    while(query.next())
    {
        QString time=query.value(0).toString();
        timeList.append(time);
    }
    timeItemModel = new QStandardItemModel(this);
    int timeCount = timeList.size();
    for(int i=0;i<timeCount;i++)
    {
        QString string = static_cast<QString>(timeList.at(i));
        QStandardItem *item = new QStandardItem(string);

        timeItemModel->appendRow(item);
    }
    ui->listView->setModel(timeItemModel);
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));
}

void MedicalRecord::itemClicked(QModelIndex index)
{
    QString str = QString("select * from medicalrecord where time = %1")
            .arg(index.data().toString());
    query.exec(str);
    while(query.next())
    {
        QString user=query.value(1).toString();
        QString xinlv=query.value(2).toString();
        QString huxi=query.value(3).toString();
        QString tiwen=query.value(4).toString();
        QString xueya=query.value(5).toString();
        QString xueyang=query.value(6).toString();
        QString xuetang=query.value(7).toString();
        QString bingkuang=query.value(8).toString();
        QString jieguo=query.value(9).toString();
        QString fangan=query.value(10).toString();
        QString beizhu=query.value(11).toString();
        ui->textBrowser->setText("生理参数\n");
        ui->textBrowser->setText(ui->textBrowser->toPlainText()
                                 +"心率："+xinlv+"\t"+"呼吸："+huxi+"\t"+"体温："+tiwen+"\n"
                                 +"血压："+xueya+"\t"+"血氧："+xueyang+"\t"+"血糖："+xuetang+"\n\n"
                                 +"病情状况\n"
                                 +bingkuang+"\n\n"
                                 +"诊断结果\n"
                                 +jieguo+"\n\n"
                                 +"治疗方案\n"
                                 +fangan+"\n\n"
                                 +"备注\n"
                                 +beizhu+"\n\n"
                                 );
    }
}

void MedicalRecord::setUserInfo()
{
    ui->label_6->setText("老胡");
    ui->label_7->setText("58");
    ui->label_8->setText("女");
    ui->label_9->setText("工人");
    ui->label_10->setText("胃病");
}



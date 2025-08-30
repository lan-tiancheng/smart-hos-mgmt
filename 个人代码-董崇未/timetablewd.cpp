#include "timetablewd.h"
#include "ui_timetablewd.h"
#include "GlobalData.h"
#include "tcpmgr.h"
//#include "RegisterDataTransmit.h"
#include <QDate>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <qjsondocument.h>
#include"global.h"
#include <qjsonobject.h>
#include"usermgr.h"

/*TimetableWd::TimetableWd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimetableWd)
{
    ui->setupUi(this);
}

TimetableWd::~TimetableWd()
{
    delete ui;
}*/
QVector<RegisterDataTransmit> GlobalData:: registerdata;
TimetableWd::TimetableWd(QWidget *parent)
    : QWidget(parent),
      doctorLabel(new QLabel("医生",this)),
      calendarWidget(new QCalendarWidget(this)),
      dateLabel(new QLabel("选择日期和时间段", this)),
      timeSlotComboBox(new QComboBox(this)),
      pushButton(new QPushButton("预约", this)) {
    this->setWindowTitle("预约时间");
    // 具体时间段
    timeSlotComboBox->addItem(""); // Add an empty item to handle no selection
    timeSlotComboBox->addItem("8:00-9:00");
    timeSlotComboBox->addItem("9:00-10:00");
    timeSlotComboBox->addItem("10:00-11:00");
    timeSlotComboBox->addItem("14:00-15:00");
    timeSlotComboBox->addItem("15:00-16:00");
    timeSlotComboBox->addItem("16:00-17:00");
    timeSlotComboBox->addItem("19:00-20:00");
    timeSlotComboBox->addItem("20:00-21:00");

    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, &TimetableWd::onDateChanged);
    connect(timeSlotComboBox, &QComboBox::currentTextChanged, this, &TimetableWd::onTimeSlotChanged);
    connect(pushButton, &QPushButton::clicked, this, &TimetableWd::onPushButtonClicked);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *rightLayout = new QHBoxLayout;

    rightLayout->addWidget(new QLabel("Time Slot:"));
    rightLayout->addWidget(timeSlotComboBox);

    mainLayout->addWidget(calendarWidget);
    mainLayout->addLayout(rightLayout);
    mainLayout->addWidget(dateLabel);
    mainLayout->addWidget(doctorLabel);
    mainLayout->addWidget(pushButton);


    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    centralWidget->resize(500,300);
    //setCentralWidget(centralWidget);
}

TimetableWd::~TimetableWd() {}

void TimetableWd::onDateChanged() {
    QDate selectedDate = calendarWidget->selectedDate();
    QString timeSlot = timeSlotComboBox->currentText();
    dateLabel->setText("Selected Date: " + selectedDate.toString("yyyy-MM-dd") +
                       " Time Slot: " + timeSlot);
}

void TimetableWd::onTimeSlotChanged() {
    // This slot is optional for real-time feedback
    QDate selectedDate = calendarWidget->selectedDate();
    QString timeSlot = timeSlotComboBox->currentText();
    dateLabel->setText("Selected Date: " + selectedDate.toString("yyyy-MM-dd") +
                       " Time Slot: " + timeSlot);
}

void TimetableWd::onPushButtonClicked() {
    QString timeSlot = timeSlotComboBox->currentText();
    QDate selectedDate = calendarWidget->selectedDate();
    // Check if a valid time slot is selected
    if (timeSlot.isEmpty()) {
        QMessageBox::warning(this, "预约失败", "请选择一个时间段进行预约！");
    } else {
        RegisterDataTransmit temp;

        temp.Date=selectedDate.toString("yyyy-MM-dd");
        temp.Hour=timeSlot;
        temp.Room=ttroom;
        temp.Name=ttdoc;
        GlobalData::registerdata.append(temp);
        QString doctorName =ttdoc;//json部分
                   QString doctorRoom =ttroom;
                   QString date = calendarWidget->selectedDate().toString("yyyy-MM-dd");
                   QString hour = timeSlot;
                   QString time=date+"/"+hour;

                   QJsonObject jsonObj;
                   jsonObj["useruid"]=QString::number(UserMgr::GetInstance()->getUid());
                   jsonObj["doctorname"]=doctorName;//预约医生姓名
                   //jsonObj["doctorroom"]=doctorRoom;//预约科室
                   jsonObj["username"]=UserMgr::GetInstance()->getName();
                   jsonObj["usersex"]=UserMgr::GetInstance()->getSex();
                   jsonObj["email"]=UserMgr::GetInstance()->getEmail();
                   jsonObj["time"]=time;//日期



                   QJsonDocument doc(jsonObj);
                   QString jsonString = doc.toJson(QJsonDocument::Indented);
                   emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_order, jsonString);
                   QMessageBox::information(this, "预约成功", ""+selectedDate.toString("yyyy-MM-dd")+"-"+timeSlot);

        //qDebug()<<GlobalData::registerdata.size();
    }
}
void TimetableWd::showdoc(QString room, QString doc){
    ttroom=room;
    ttdoc=doc;
    doctorLabel->setText("预约医生:"+room+doc);
}


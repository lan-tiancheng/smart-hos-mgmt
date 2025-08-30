#include "pmainwindow.h"
#include "ui_pmainwindow.h"
#include "homewindow.h"
#include "GlobalData.h"
//#include "MedicineItem.h"
//#include 在.h文件添加对应文件和变量
#include <QMessageBox>
#include <QCoreApplication>
#include <QVector>
#include <QTextToSpeech>
#include <QVoice>
#include "audio.h"//语音识别

PMainWindow::PMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("智慧医疗");
    my_audio=new Audio;
    my_say=new QTextToSpeech;

    ui->stackedWidget->addWidget(&homeWd);
    ui->stackedWidget->addWidget(&bookWd);
    ui->stackedWidget->addWidget(&ownWd);
    ui->stackedWidget->addWidget(&chatWd);
    ui->stackedWidget->addWidget(&hospitalizationWd);

    btnGroup.addButton(ui->home,0);
    btnGroup.addButton(ui->book,1);
    btnGroup.addButton(ui->personal,2);
    btnGroup.addButton(ui->chattingroom,3);
    btnGroup.addButton(ui->hospitalization,4);

    connect(&btnGroup,static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    btnGroup.button(0)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

    connect(&homeWd,SIGNAL(infoSearchSend(int)),this,SLOT(infoRecv(int)));
    connect(&homeWd,SIGNAL(infoMedicalExpenseSend()),this,SLOT(infoRecv(int)));

}

PMainWindow::~PMainWindow()
{
    delete ui;
}
void PMainWindow::infoRecv(int){
    this->close();
}
void MIsqlite_Init(){
    QSqlDatabase db;
    /*if (QSqlDatabase::contains("my_MIsql_connection"))
    {
        db = QSqlDatabase::database("my_MIsql_connection");
    }
    else{
        db =QSqlDatabase::addDatabase("QSQLITE","my_MIsql_connection");
        db.setDatabaseName("medicalitem.db");
    }*/
    db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("medicalitem.db");
    if(!db.open()){
        qDebug()<<"open error";
    }
    QString createsql=QString("create table if not exists mitable(id integer primary key autoincrement,"
    "miname nametext unique not NULL,"
    "miintro contenttext not NULL)");//zhuyi!
    QSqlQuery query;
    if(!query.exec(createsql)){
        qDebug()<<"table create error";
    }
    else{
        qDebug()<<"table create success";
    }
    QVector<MedicineItem> array(100);
    int i=0;
    int sum=10;
    QString insertMI;
    array[0].name="六味地黄丸";array[0].introduce="治疗肾虚";
    array[1].name="999感冒灵";array[1].introduce="治疗感冒";
    array[2].name="藿香正气水";array[2].introduce="治疗中暑";
    array[3].name="胃舒平";array[3].introduce="治疗消化不良";
    array[4].name="板蓝根";array[4].introduce="治疗感冒";
    array[5].name="救心丸";array[5].introduce="治疗心脏病";
    while(i<sum){
        insertMI = QString("insert into mitable values('%1', '%2', '%3')").arg(i).arg(array[i].name).arg(array[i].introduce);
        if(query.exec(insertMI)){
            qDebug()<<"insert success";
        }
        else {
            qDebug() << "insert error!";
        }
        i++;
    }


}



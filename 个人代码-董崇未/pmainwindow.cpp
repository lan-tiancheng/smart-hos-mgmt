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
    ui->stackedWidget->addWidget(&drawer);
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
    array[0].name="六味地黄丸";array[0].introduce="六味地黄丸，中成药名。为补益剂，具有滋阴补肾之功效。用于肾阴亏损，头晕耳鸣，腰膝酸软，骨蒸潮热，盗汗遗精，消渴。六味合用，三补三泻，其中补药用量重于“泻药”，是以补为主；肝脾肾三阴并补，以补肾阴为主，这是本方的配伍特点。";
    array[1].name="999感冒灵";array[1].introduce="本品为浅棕色至深棕色的颗粒，味甜、微苦。每盒含9包，每包袋装10g。解热镇痛功效，用于因感冒引起的头痛，发热，鼻塞，流涕，咽痛等症状。开水冲服，一次1袋，一日3次。小儿减量或遵医嘱。";
    array[2].name="藿香正气水";array[2].introduce="藿香正气水，中成药名，为祛暑剂，具有解表化湿，理气和中之功效。用于外感风寒、内伤湿滞或夏伤暑湿所致的感冒，症见头痛昏重、胸膈痞闷、脘腹胀痛、呕吐泄泻；肠胃型感冒见上述症候者。";
    array[3].name="胃舒平";array[3].introduce="通用名：复方氢氧化铝。本品有中和胃酸，减少胃液分泌和解痉止疼作用。 用于胃酸过多、胃溃疡及胃痛等。1.服药后一小时内应避免服用其他药物，因氢氧化铝可与其他药物结合而降低吸收，影响疗效。2.本品与肠溶片同服，可使肠溶片加快溶解，不应同用。";
    array[4].name="板蓝根";array[4].introduce="板蓝根颗粒，本品为浅棕黄色至棕褐色的颗粒；味甜、微苦。清热解毒，凉血利咽。用于肺胃热盛所致的咽喉肿痛、口咽干燥；急性扁桃体炎见上述证候者。开水冲服。一次半～1袋（5～10克），一日3～4次。";
    array[5].name="救心丸";array[5].introduce="救心丸，益气强心。用于气虚血瘀所致心痛、胸闷、气促、眩晕、心悸、神疲乏力、自汗、手足发冷、食欲不振、浮肿等症以及冠心病、心绞痛、陈旧性心肌梗塞、心功能不全具有上述证候者。";
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



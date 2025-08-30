#include "medicinesearchwindow.h"
#include "ui_medicinesearchwindow.h"
#include "pmainwindow.h"
//#include "MedicineItem.h"
#include <QLineEdit>
#include <QVector>
#include <QMessageBox>
#include "global.h"
using namespace std;


MedicineSearchWindow::MedicineSearchWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MedicineSearchWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("医药搜索");
    /*QVector<MedicineItem> medicineitem(100);
    MIsqlite_Init();
    int sum=0;
    int i=0;
    //(id integer primary key autoincrement,"
    //"miname nametext unique not NULL,"
    //"miintro contenttext not NULL)"
    QSqlQuery query;

    //ui->lineEdit->setText("999感冒灵");//先后问题,先主文件，然后响应

    qDebug()<<ui->lineEdit->text();
    QString selectmi=QString("select * from mitable where miname='%1';").arg(ui->lineEdit->text());
    query.exec(selectmi);
    while(query.next()){//把数据库找到的内容填进QVector
        medicineitem[i].pictureid=query.value(0).toString().toInt();
        medicineitem[i].name=query.value(1).toString();
        medicineitem[i].introduce=query.value(2).toString();
        i++;
    }
    sum=i;
    i=0;
    while(i<sum){
        medicineitem[i].picturelabel=new QLabel("picture",this);
        medicineitem[i].picturelabel->setPixmap(medicineitem[i].picture);
        medicineitem[i].picturelabel->move(100,70*i+180);
        medicineitem[i].picturelabel->setText(medicineitem[i].name);//设置显示的文本

        medicineitem[i].namelabel=new QLabel(medicineitem[i].name,this);
        medicineitem[i].namelabel->move(200,70*i+180);
        medicineitem[i].namelabel->setText(medicineitem[i].name);//设置显示的文本

        medicineitem[i].introducelabel=new QLabel(medicineitem[i].introduce,this);
        medicineitem[i].introducelabel->move(200,70*i+200);
        medicineitem[i].introducelabel->setText(medicineitem[i].introduce);//设置显示的文本
        i++;
    }*/
}

MedicineSearchWindow::~MedicineSearchWindow()
{
    delete ui;
}

void MedicineSearchWindow::on_backbtn_clicked()
{
    PMainWindow *w=new PMainWindow;
    w->show();
    this->close();
}
void MedicineSearchWindow::sendText(QString str)
{
    ui->lineEdit->setText(str);
    //database conduct

}


void MedicineSearchWindow::on_searchBtn_clicked()
{
    QString strText = ui->lineEdit->text();
    if (!strText.isEmpty()){
        //QVector<MedicineItem> medicineitem(100);
        MIsqlite_Init();
        QSqlQuery query;
        QString selectmi=QString("select * from mitable where miname='%1';").arg(ui->lineEdit->text());
        //QMessageBox::information(this, QStringLiteral("搜索"), QStringLiteral("搜索内容为%1").arg(strText));

        MIsearchSonWd *missWd=new MIsearchSonWd;
        int sum=0;
        int i=0;
        QVector<MedicineItem> medicineitem(100);
        query.exec(selectmi);
        while(query.next()){//把数据库找到的内容填进QVector
            medicineitem[i].pictureid=query.value(0).toString().toInt();
            medicineitem[i].name=query.value(1).toString();
            medicineitem[i].introduce=query.value(2).toString();
            i++;
        }
        qDebug()<<i;//
        sum=i;
        i=0;
        while(i<sum){
            //medicineitem[i].picturelabel=new QLabel("picture",this);
            QLabel *picturelabel=new QLabel(missWd);
            //medicineitem[i].picture
            picturelabel->setPixmap(medicineitem[i].picture);
            picturelabel->move(100,70*i+70);
            picturelabel->setText(medicineitem[i].name);//设置显示的文本
            //medicineitem[i].picturelabel->setText("123123");

            //medicineitem[i].namelabel=new QLabel(medicineitem[i].name,this);
            QLabel *namelabel=new QLabel(missWd);
            namelabel->move(200,70*i+70);
            namelabel->setText(medicineitem[i].name);//设置显示的文本
            //namelabel->setText("2392834239");

            //medicineitem[i].introducelabel=new QLabel(medicineitem[i].introduce,this);
            QLabel *introducelabel=new QLabel(missWd);
            introducelabel->move(200,70*i+20+70);
            introducelabel->setText(medicineitem[i].introduce);//设置显示的文本
            i++;
        }
        update();
        missWd->show();
        //repolish(this);
    }
}


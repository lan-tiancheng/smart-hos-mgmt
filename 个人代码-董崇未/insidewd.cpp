#include "insidewd.h"
#include "ui_insidewd.h"
#include "GlobalData.h"
#include <QLabel>
#include <vector>
#include <QVector>
#include <QPushButton>
#include "timetablewd.h"
#include "usermgr.h"
using namespace std;

int GlobalData::InsideDocnum=0;

InsideWd::InsideWd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsideWd)
{
    ui->setupUi(this);

    //请在此处调用datatrans()

    QVector<QVector<QString>> internalMedicineData = UserMgr::GetInstance()->getInternalMedicineData();

       int num = internalMedicineData.size();
       QString *id = new QString[num];
       QString *name = new QString[num];
       QString *introduce = new QString[num];
       QString *position = new QString[num];

       for (int i = 0; i < num; ++i) {
           id[i] = internalMedicineData[i][1];          // 工号
           name[i] = internalMedicineData[i][2];        // 姓名
           introduce[i] = internalMedicineData[i][5];   // 介绍
           position[i] = internalMedicineData[i][12];    // 职位
       }

       // 调用 datatrans 函数传递数据

       this->datatrans(num, id, name, introduce, position);

       // 清理动态分配的内存
       delete[] id;
       delete[] name;
       delete[] introduce;
       delete[] position;

    int i=0;
    while(i<GlobalData::InsideDocnum){  //condition
        QLabel *temp=new QLabel(this);
        QString pixmapstring=QString(":/res/doc%1.jpeg").arg(i+1+12);
        QPixmap pixmap(pixmapstring);
        temp->setPixmap(pixmap.scaled(QSize(100,100),
                                       Qt::IgnoreAspectRatio,
                                       Qt::SmoothTransformation));
        temp->resize(100,100);
        temp->move(0,100*i);

        insidedoc[i].namelabel=new QLabel(insidedoc[i].name,this);
        insidedoc[i].namelabel->move(100,100*i);
        insidedoc[i].namelabel->setText(insidedoc[i].name);//设置显示的文本

        insidedoc[i].introducelabel=new QLabel(insidedoc[i].introduce,this);
        insidedoc[i].introducelabel->move(100,100*i+60);
        insidedoc[i].introducelabel->setText(insidedoc[i].introduce);//设置显示的文本

        insidedoc[i].positionlabel=new QLabel(insidedoc[i].position,this);
        insidedoc[i].positionlabel->move(200,100*i);
        insidedoc[i].positionlabel->setText(insidedoc[i].position);//设置显示的文本

        str=insidedoc[i].name;

        QPushButton *tempBtn = new QPushButton(this);
        tempBtn->move(300,100*i+30);
        tempBtn->setText(insidedoc[i].id);//到时候读取text就可以知道预约那个医生。
        connect(tempBtn,SIGNAL(clicked()),this,SLOT(showdate()));
        i++;
    }
}

InsideWd::~InsideWd()
{
    delete ui;
}
void InsideWd::showdate(){
    TimetableWd *ttWd=new TimetableWd;
    ttWd->resize(500,300);
    ttWd->showdoc("内科",str);
    ttWd->show();
}
//封装借口，数据传输用
//num是数据库里医生数量,其余请传入对应的数组：工号，姓名，介绍，职位。
void InsideWd::datatrans(int num,QString *id,QString *name,QString *introduce,QString *position){
    GlobalData::InsideDocnum=num;
    while(num--){
        InsideDoc temp;
        temp.id=id[num];
        temp.name=name[num];
        temp.introduce=introduce[num];
        temp.position=position[num];
        insidedoc.append(temp);
    }
}

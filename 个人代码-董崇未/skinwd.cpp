#include "skinwd.h"
#include "ui_skinwd.h"
#include "GlobalData.h"
#include <QLabel>
#include <vector>
#include <QVector>
#include <QPushButton>
#include "timetablewd.h"
#include "usermgr.h"
using namespace std;

int GlobalData::SkinDocnum=0;

SkinWd::SkinWd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SkinWd)
{
    ui->setupUi(this);

    //此处调用datatrans()
    QVector<QVector<QString>> dermatologyData = UserMgr::GetInstance()->getDermatologyData();

    int num = dermatologyData.size();
    QString *id = new QString[num];
    QString *name = new QString[num];
    QString *introduce = new QString[num];
    QString *position = new QString[num];

    for (int i = 0; i < num; ++i) {
        id[i] = dermatologyData[i][1];          // 工号
        name[i] = dermatologyData[i][2];        // 姓名
        introduce[i] = dermatologyData[i][5];   // 介绍
        position[i] = dermatologyData[i][12];    // 职位
    }

    // 调用 datatrans 函数传递数据

    this->datatrans(num, id, name, introduce, position);

    // 清理动态分配的内存
    delete[] id;
    delete[] name;
    delete[] introduce;
    delete[] position;

    int i=0;
    while(i<GlobalData::SkinDocnum){  //condition
        QLabel *temp=new QLabel(this);
        QString pixmapstring=QString(":/res/doc%1.jpeg").arg(i+1+9);
        QPixmap pixmap(pixmapstring);
        temp->setPixmap(pixmap.scaled(QSize(100,100),
                                       Qt::IgnoreAspectRatio,
                                       Qt::SmoothTransformation));
        temp->resize(100,100);
        temp->move(0,100*i);

        skindoc[i].namelabel=new QLabel(skindoc[i].name,this);
        skindoc[i].namelabel->move(100,100*i);
        skindoc[i].namelabel->setText(skindoc[i].name);//设置显示的文本

        skindoc[i].introducelabel=new QLabel(skindoc[i].introduce,this);
        skindoc[i].introducelabel->move(100,100*i+60);
        skindoc[i].introducelabel->setText(skindoc[i].introduce);//设置显示的文本

        skindoc[i].positionlabel=new QLabel(skindoc[i].position,this);
        skindoc[i].positionlabel->move(200,100*i);
        skindoc[i].positionlabel->setText(skindoc[i].position);//设置显示的文本

        str=skindoc[i].name;

        QPushButton *tempBtn = new QPushButton(this);
        tempBtn->move(300,100*i+30);
        tempBtn->setText(skindoc[i].id);//到时候读取text就可以知道预约那个医生。
        connect(tempBtn,SIGNAL(clicked()),this,SLOT(showdate()));
        i++;
    }
}

SkinWd::~SkinWd()
{
    delete ui;
}
void SkinWd::showdate(){
    TimetableWd *ttWd=new TimetableWd;
    ttWd->resize(500,300);
    ttWd->showdoc("皮肤科",str);
    ttWd->show();
}
//封装借口，数据传输用
//num是数据库里医生数量,其余请传入对应的数组：工号，姓名，介绍，职位。
void SkinWd::datatrans(int num,QString *id,QString *name,QString *introduce,QString *position){
    GlobalData::SkinDocnum=num;
    while(num--){
        SkinDoc temp;
        temp.id=id[num];
        temp.name=name[num];
        temp.introduce=introduce[num];
        temp.position=position[num];
        skindoc.append(temp);
    }
}

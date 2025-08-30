#include "womanwd.h"
#include "ui_womanwd.h"
#include "GlobalData.h"
#include <QLabel>
#include <vector>
#include <QVector>
#include <QPushButton>
#include "timetablewd.h"
#include "usermgr.h"
using namespace std;
int GlobalData::WomanDocnum=0;
WomanWd::WomanWd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WomanWd)
{
    ui->setupUi(this);

    //此处调用datatrans()
    QVector<QVector<QString>> gynecologyData = UserMgr::GetInstance()->getGynecologyData();

        int num = gynecologyData.size();
        QString *id = new QString[num];
        QString *name = new QString[num];
        QString *introduce = new QString[num];
        QString *position = new QString[num];

        for (int i = 0; i < num; ++i) {
            id[i] = gynecologyData[i][1];          // 工号
            name[i] = gynecologyData[i][2];        // 姓名
            introduce[i] = gynecologyData[i][5];   // 介绍
            position[i] = gynecologyData[i][12];    // 职位
        }

        // 调用 datatrans 函数传递数据

        this->datatrans(num, id, name, introduce, position);

        // 清理动态分配的内存
        delete[] id;
        delete[] name;
        delete[] introduce;
        delete[] position;

    int i=0;
    while(i<GlobalData::WomanDocnum){  //condition
        womandoc[i].picturelabel=new QLabel("picture",this);
        womandoc[i].picturelabel->setPixmap(womandoc[i].picture);
        womandoc[i].picturelabel->move(0,70*i);
        womandoc[i].picturelabel->setText(womandoc[i].name);//设置显示的文本

        womandoc[i].namelabel=new QLabel(womandoc[i].name,this);
        womandoc[i].namelabel->move(100,70*i);
        womandoc[i].namelabel->setText(womandoc[i].name);//设置显示的文本

        womandoc[i].introducelabel=new QLabel(womandoc[i].introduce,this);
        womandoc[i].introducelabel->move(100,70*i+20);
        womandoc[i].introducelabel->setText(womandoc[i].introduce);//设置显示的文本

        womandoc[i].positionlabel=new QLabel(womandoc[i].position,this);
        womandoc[i].positionlabel->move(200,70*i);
        womandoc[i].positionlabel->setText(womandoc[i].position);//设置显示的文本

        str=womandoc[i].name;

        QPushButton *tempBtn = new QPushButton(this);
        tempBtn->move(300,70*i+10);
        tempBtn->setText(womandoc[i].id);//到时候读取text就可以知道预约那个医生。
        connect(tempBtn,SIGNAL(clicked()),this,SLOT(showdate()));
        i++;
    }
}

WomanWd::~WomanWd()
{
    delete ui;
}
void WomanWd::showdate(){
    TimetableWd *ttWd=new TimetableWd;
    ttWd->resize(500,300);
    ttWd->showdoc("妇科",str);
    ttWd->show();
}
//封装借口，数据传输用
//num是数据库里医生数量,其余请传入对应的数组：工号，姓名，介绍，职位。
void WomanWd::datatrans(int num,QString *id,QString *name,QString *introduce,QString *position){
    GlobalData::WomanDocnum=num;
    while(num--){
        WomanDoc temp;
        temp.id=id[num];
        temp.name=name[num];
        temp.introduce=introduce[num];
        temp.position=position[num];
        womandoc.append(temp);
    }
}

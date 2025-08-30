#include "information.h"
#include "ui_information.h"
//#include"usermgr.h"
#include "change.h"
#include <QPainter>
#include <QPaintEvent>
#include"tcpmgr.h"

information::information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::information)
{
    ui->setupUi(this);
    handleDataUpdated();
    connect(TcpMgr::GetInstance().get(),&TcpMgr::dataUpdated,this,&information::handleDataUpdated);
    // 设置控件背景透明
    setAttribute(Qt::WA_TranslucentBackground);
}

information::~information()
{
    delete ui;
}

void information::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 绘制浅蓝色背景
    painter.fillRect(rect(), QColor(173, 216, 230)); // Light blue color

    // 调用基类的 paintEvent 方法以确保其他绘制操作正常进行
    QWidget::paintEvent(event);
}

void information::on_pushButton_clicked()
{
    //emit goback();
    this->hide();
}

void information::on_pushButtonCommit_2_clicked()
{
    change *changeWindow = new change(this);

    // 连接数据更新信号到槽函数
    connect(changeWindow, &change::dataUpdated, this, &information::handleDataUpdated);

    changeWindow->show();
}

void information::handleDataUpdated()
{
    // 刷新当前界面的数据或状态
    // 此处不要显示提示框
    QString name=UserMgr::GetInstance()->getName();
    ui->name->setText(UserMgr::GetInstance()->getName());
    ui->eamil->setText(UserMgr::GetInstance()->getEmail());
    ui->intr->setText(UserMgr::GetInstance()->getIntr());
    ui->department->setText(UserMgr::GetInstance()->getDepartmentName());
    repolish(this);

}

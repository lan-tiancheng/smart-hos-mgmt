#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDir>
#include <QCoreApplication>

Drawer::Drawer(QWidget *parent, Qt::WindowFlags f) :
    QToolBox(parent, f)
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    setWindowTitle("doctor-patient chat");
    setWindowIcon(QPixmap(":/res/qq.png"));

    toolBtn1 = new QToolButton(this);
    toolBtn1->setText("小龙");
    toolBtn1->setIcon(QPixmap(":/res/1.jpg"));
    toolBtn1->setIconSize(QPixmap(":/res/1.jpg").size());
    toolBtn1->setAutoRaise(true);                               //鼠标离开时，按钮自动恢复成弹起状态
    toolBtn1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    QObject::connect(toolBtn1, SIGNAL(clicked()), this, SLOT(showChatWidget1()));

    toolBtn2 = new QToolButton;
    toolBtn2->setText("小强");
    toolBtn2->setIcon(QPixmap(":/res/2.jpg"));
    toolBtn2->setIconSize(QPixmap(":/res/2.jpg").size());
    toolBtn2->setAutoRaise(true);
    toolBtn2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn2, SIGNAL(clicked()), this, SLOT(showChatWidget2()));

    toolBtn3 = new QToolButton;
    toolBtn3->setText("小简");
    toolBtn3->setIcon(QPixmap(":/res/3.jpg"));
    toolBtn3->setIconSize(QPixmap(":/res/3.jpg").size());
    toolBtn3->setAutoRaise(true);
    toolBtn3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn3, SIGNAL(clicked()), this, SLOT(showChatWidget3()));

    toolBtn4 = new QToolButton;
    toolBtn4->setText("小新");
    toolBtn4->setIcon(QPixmap(":/res/4.jpg"));
    toolBtn4->setIconSize(QPixmap(":/res/4.jpg").size());
    toolBtn4->setAutoRaise(true);
    toolBtn4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn4, SIGNAL(clicked()), this, SLOT(showChatWidget4()));

    toolBtn5 = new QToolButton;
    toolBtn5->setText("小花");
    toolBtn5->setIcon(QPixmap(":/res/5.jpg"));
    toolBtn5->setIconSize(QPixmap(":/res/5.jpg").size());
    toolBtn5->setAutoRaise(true);
    toolBtn5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn5, SIGNAL(clicked()), this, SLOT(showChatWidget5()));

    toolBtn6 = new QToolButton;
    toolBtn6->setText("二狗");
    toolBtn6->setIcon(QPixmap(":/res/6.jpg"));
    toolBtn6->setIconSize(QPixmap(":/res/6.jpg").size());
    toolBtn6->setAutoRaise(true);
    toolBtn6->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn6, SIGNAL(clicked()), this, SLOT(showChatWidget6()));

    toolBtn7 = new QToolButton;
    toolBtn7->setText("小明");
    toolBtn7->setIcon(QPixmap(":/res/7.jpg"));
    toolBtn7->setIconSize(QPixmap(":/res/7.jpg").size());
    toolBtn7->setAutoRaise(true);
    toolBtn7->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn7, SIGNAL(clicked()), this, SLOT(showChatWidget7()));

    toolBtn8 = new QToolButton;
    toolBtn8->setText("大黄");
    toolBtn8->setIcon(QPixmap(":/res/8.jpg"));
    toolBtn8->setIconSize(QPixmap(":/res/8.jpg").size());
    toolBtn8->setAutoRaise(true);
    toolBtn8->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn8, SIGNAL(clicked()), this, SLOT(showChatWidget8()));

    toolBtn9 = new QToolButton;
    toolBtn9->setText("小美");
    toolBtn9->setIcon(QPixmap(":/res/9.jpg"));
    toolBtn9->setIconSize(QPixmap(":/res/9.jpg").size());
    toolBtn9->setAutoRaise(true);
    toolBtn9->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn9, SIGNAL(clicked()), this, SLOT(showChatWidget9()));

    QGroupBox *groupBox = new QGroupBox;
    QVBoxLayout *layout=new QVBoxLayout(groupBox);

    layout->setMargin(20);     //布局中各窗体的显示间距
    layout->setAlignment(Qt::AlignLeft);
    layout->addWidget(toolBtn1);
    layout->addWidget(toolBtn2);
    layout->addWidget(toolBtn3);
    layout->addWidget(toolBtn4);
    layout->addWidget(toolBtn5);
    layout->addWidget(toolBtn6);
    layout->addWidget(toolBtn7);
    layout->addWidget(toolBtn8);
    layout->addWidget(toolBtn9);
    layout->addStretch();   //插入一个占位符
    this->addItem((QWidget*)groupBox, "聊天成员");
}

void Drawer::showChatWidget1()
{
    chatWidget1 = new Widget(0,toolBtn1->text());      //以按钮toolBtn1的文本为用户名创建一个widget实例，对应于一个聊天窗口
    chatWidget1->setWindowTitle(toolBtn1->text());      //设置聊天窗口的标题（为对应用户图片按钮的文本）
    chatWidget1->setWindowIcon(toolBtn1->icon());       //设置聊天窗图片
    chatWidget1->show();
}

void Drawer::showChatWidget2()
{
    chatWidget2 = new Widget(0,toolBtn2->text());
    chatWidget2->setWindowTitle(toolBtn2->text());
    chatWidget2->setWindowIcon(toolBtn2->icon());
    chatWidget2->show();
}

void Drawer::showChatWidget3()
{
    chatWidget3 = new Widget(0,toolBtn3->text());
    chatWidget3->setWindowTitle(toolBtn3->text());
    chatWidget3->setWindowIcon(toolBtn3->icon());
    chatWidget3->show();
}

void Drawer::showChatWidget4()
{
    chatWidget4 = new Widget(0,toolBtn4->text());
    chatWidget4->setWindowTitle(toolBtn4->text());
    chatWidget4->setWindowIcon(toolBtn4->icon());
    chatWidget4->show();
}

void Drawer::showChatWidget5()
{
    chatWidget5 = new Widget(0,toolBtn5->text());
    chatWidget5->setWindowTitle(toolBtn5->text());
    chatWidget5->setWindowIcon(toolBtn5->icon());
    chatWidget5->show();
}

void Drawer::showChatWidget6()
{
    chatWidget6 = new Widget(0,toolBtn6->text());
    chatWidget6->setWindowTitle(toolBtn6->text());
    chatWidget6->setWindowIcon(toolBtn6->icon());
    chatWidget6->show();
}

void Drawer::showChatWidget7()
{
    chatWidget7 = new Widget(0,toolBtn7->text());
    chatWidget7->setWindowTitle(toolBtn7->text());
    chatWidget7->setWindowIcon(toolBtn7->icon());
    chatWidget7->show();
}

void Drawer::showChatWidget8()
{
    chatWidget8 = new Widget(0,toolBtn8->text());
    chatWidget8->setWindowTitle(toolBtn8->text());
    chatWidget8->setWindowIcon(toolBtn8->icon());
    chatWidget8->show();
}

void Drawer::showChatWidget9()
{
    chatWidget9 = new Widget(0,toolBtn9->text());
    chatWidget9->setWindowTitle(toolBtn9->text());
    chatWidget9->setWindowIcon(toolBtn9->icon());
    chatWidget9->show();
}

#include "drawer.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDir>
#include <QCoreApplication>
#include <QScrollBar>

Drawer::Drawer(QWidget *parent) :
    QWidget(parent),
    scrollArea(new QScrollArea(this)),
    containerWidget(new QWidget),
    buttonLayout(new QVBoxLayout(containerWidget))
{
    // 设置窗口标志以显示关闭按钮
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    setWindowTitle("doctor-patient chat");
    setWindowIcon(QPixmap(":/images/images/qq.png"));

    // 初始化工具按钮
    toolBtn1 = new QToolButton(this);
    toolBtn1->setText("小龙");
    toolBtn1->setIcon(QPixmap(":/images/images/1.jpg"));
    toolBtn1->setIconSize(QPixmap(":/images/images/1.jpg").size());
    toolBtn1->setAutoRaise(true);
    toolBtn1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn1, &QToolButton::clicked, this, &Drawer::showChatWidget1);

    toolBtn2 = new QToolButton(this);
    toolBtn2->setText("小强");
    toolBtn2->setIcon(QPixmap(":/images/images/2.jpg"));
    toolBtn2->setIconSize(QPixmap(":/images/images/2.jpg").size());
    toolBtn2->setAutoRaise(true);
    toolBtn2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn2, &QToolButton::clicked, this, &Drawer::showChatWidget2);

    toolBtn3 = new QToolButton(this);
    toolBtn3->setText("小简");
    toolBtn3->setIcon(QPixmap(":/images/images/3.jpg"));
    toolBtn3->setIconSize(QPixmap(":/images/images/3.jpg").size());
    toolBtn3->setAutoRaise(true);
    toolBtn3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn3, &QToolButton::clicked, this, &Drawer::showChatWidget3);

    toolBtn4 = new QToolButton(this);
    toolBtn4->setText("小新");
    toolBtn4->setIcon(QPixmap(":/images/images/4.jpg"));
    toolBtn4->setIconSize(QPixmap(":/images/images/4.jpg").size());
    toolBtn4->setAutoRaise(true);
    toolBtn4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn4, &QToolButton::clicked, this, &Drawer::showChatWidget4);

    toolBtn5 = new QToolButton(this);
    toolBtn5->setText("小花");
    toolBtn5->setIcon(QPixmap(":/images/images/5.jpg"));
    toolBtn5->setIconSize(QPixmap(":/images/images/5.jpg").size());
    toolBtn5->setAutoRaise(true);
    toolBtn5->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn5, &QToolButton::clicked, this, &Drawer::showChatWidget5);

    toolBtn6 = new QToolButton(this);
    toolBtn6->setText("二狗");
    toolBtn6->setIcon(QPixmap(":/images/images/6.jpg"));
    toolBtn6->setIconSize(QPixmap(":/images/images/6.jpg").size());
    toolBtn6->setAutoRaise(true);
    toolBtn6->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn6, &QToolButton::clicked, this, &Drawer::showChatWidget6);

    toolBtn7 = new QToolButton(this);
    toolBtn7->setText("小明");
    toolBtn7->setIcon(QPixmap(":/images/images/7.jpg"));
    toolBtn7->setIconSize(QPixmap(":/images/images/7.jpg").size());
    toolBtn7->setAutoRaise(true);
    toolBtn7->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn7, &QToolButton::clicked, this, &Drawer::showChatWidget7);

    toolBtn8 = new QToolButton(this);
    toolBtn8->setText("大黄");
    toolBtn8->setIcon(QPixmap(":/images/images/8.jpg"));
    toolBtn8->setIconSize(QPixmap(":/images/images/8.jpg").size());
    toolBtn8->setAutoRaise(true);
    toolBtn8->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn8, &QToolButton::clicked, this, &Drawer::showChatWidget8);

    toolBtn9 = new QToolButton(this);
    toolBtn9->setText("小美");
    toolBtn9->setIcon(QPixmap(":/images/images/9.jpg"));
    toolBtn9->setIconSize(QPixmap(":/images/images/9.jpg").size());
    toolBtn9->setAutoRaise(true);
    toolBtn9->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    connect(toolBtn9, &QToolButton::clicked, this, &Drawer::showChatWidget9);

    // 添加按钮到布局
    buttonLayout->setMargin(20);
    buttonLayout->setAlignment(Qt::AlignLeft);
    buttonLayout->addWidget(toolBtn1);
    buttonLayout->addWidget(toolBtn2);
    buttonLayout->addWidget(toolBtn3);
    buttonLayout->addWidget(toolBtn4);
    buttonLayout->addWidget(toolBtn5);
    buttonLayout->addWidget(toolBtn6);
    buttonLayout->addWidget(toolBtn7);
    buttonLayout->addWidget(toolBtn8);
    buttonLayout->addWidget(toolBtn9);
    buttonLayout->addStretch();

    // 配置滚动区域
    scrollArea->setWidget(containerWidget);
    scrollArea->setWidgetResizable(true);

    // 设置主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

// 实现槽函数
void Drawer::showChatWidget1()
{
    chatWidget1 = new Widget(nullptr, toolBtn1->text());
    chatWidget1->setWindowTitle(toolBtn1->text());
    chatWidget1->setWindowIcon(toolBtn1->icon());
    chatWidget1->show();
}

void Drawer::showChatWidget2()
{
    chatWidget2 = new Widget(nullptr, toolBtn2->text());
    chatWidget2->setWindowTitle(toolBtn2->text());
    chatWidget2->setWindowIcon(toolBtn2->icon());
    chatWidget2->show();
}

void Drawer::showChatWidget3()
{
    chatWidget3 = new Widget(nullptr, toolBtn3->text());
    chatWidget3->setWindowTitle(toolBtn3->text());
    chatWidget3->setWindowIcon(toolBtn3->icon());
    chatWidget3->show();
}

void Drawer::showChatWidget4()
{
    chatWidget4 = new Widget(nullptr, toolBtn4->text());
    chatWidget4->setWindowTitle(toolBtn4->text());
    chatWidget4->setWindowIcon(toolBtn4->icon());
    chatWidget4->show();
}

void Drawer::showChatWidget5()
{
    chatWidget5 = new Widget(nullptr, toolBtn5->text());
    chatWidget5->setWindowTitle(toolBtn5->text());
    chatWidget5->setWindowIcon(toolBtn5->icon());
    chatWidget5->show();
}

void Drawer::showChatWidget6()
{
    chatWidget6 = new Widget(nullptr, toolBtn6->text());
    chatWidget6->setWindowTitle(toolBtn6->text());
    chatWidget6->setWindowIcon(toolBtn6->icon());
    chatWidget6->show();
}

void Drawer::showChatWidget7()
{
    chatWidget7 = new Widget(nullptr, toolBtn7->text());
    chatWidget7->setWindowTitle(toolBtn7->text());
    chatWidget7->setWindowIcon(toolBtn7->icon());
    chatWidget7->show();
}

void Drawer::showChatWidget8()
{
    chatWidget8 = new Widget(nullptr, toolBtn8->text());
    chatWidget8->setWindowTitle(toolBtn8->text());
    chatWidget8->setWindowIcon(toolBtn8->icon());
    chatWidget8->show();
}

void Drawer::showChatWidget9()
{
    chatWidget9 = new Widget(nullptr, toolBtn9->text());
    chatWidget9->setWindowTitle(toolBtn9->text());
    chatWidget9->setWindowIcon(toolBtn9->icon());
    chatWidget9->show();
}

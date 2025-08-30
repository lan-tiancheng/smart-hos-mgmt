#include "homewindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QIcon>

HomeWindow::HomeWindow() {
    resize(600, 400);
    QVBoxLayout *layout = new QVBoxLayout;  // 设置Home窗口的布局

    // 创建标题标签
    QLabel *label = new QLabel("首页");
    label->setStyleSheet("font-size: 40px; font-weight: bold;");
    layout->addWidget(label);  // 将标签添加到布局中
    layout->addStretch();  // 将顶部标签推至顶部

    // 创建搜索栏和搜索按钮
    QHBoxLayout *searchLayout = new QHBoxLayout;

    QLineEdit *searchBar = new QLineEdit;
    searchBar->setPlaceholderText("请输入搜索内容...");
    QPushButton *searchButton = new QPushButton("搜索");

    searchLayout->addWidget(searchBar);  // 将搜索栏添加到布局中
    searchLayout->addWidget(searchButton);  // 将搜索按钮添加到布局中

    layout->addLayout(searchLayout);  // 将搜索栏和搜索按钮的布局添加到主布局中

    // 创建按钮和描述标签
    QHBoxLayout *buttonLayout = new QHBoxLayout;

    // 第一个按钮和描述
    QVBoxLayout *button1Layout = new QVBoxLayout;
    QPushButton *button1 = new QPushButton;
    button1->setIcon(QIcon(":/images/pay.png"));  // 设置按钮图标
    button1->setIconSize(QSize(64, 64));  // 设置图标大小

    QLabel *label1 = new QLabel("缴费功能");
    label1->setAlignment(Qt::AlignCenter);  // 将描述居中

    button1Layout->addWidget(button1);
    button1Layout->addWidget(label1);
    button1Layout->setAlignment(Qt::AlignCenter);  // 将整个垂直布局居中

    // 第二个按钮和描述
    QVBoxLayout *button2Layout = new QVBoxLayout;
    QPushButton *button2 = new QPushButton;
    button2->setIcon(QIcon(":/images/quiz.png"));  // 设置按钮图标
    button2->setIconSize(QSize(64, 64));  // 设置图标大小

    QLabel *label2 = new QLabel("心理评估");
    label2->setAlignment(Qt::AlignCenter);  // 将描述居中

    button2Layout->addWidget(button2);
    button2Layout->addWidget(label2);
    button2Layout->setAlignment(Qt::AlignCenter);  // 将整个垂直布局居中

    // 添加按钮布局和间隔
    buttonLayout->addLayout(button1Layout);
    buttonLayout->addSpacing(20);  // 添加按钮间隔
    buttonLayout->addLayout(button2Layout);

    layout->addLayout(buttonLayout);  // 将按钮和描述标签的布局添加到主布局中

    layout->addStretch();  // 保持底部间距
    setLayout(layout);  // 设置窗口的布局
}

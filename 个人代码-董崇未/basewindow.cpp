#include "basewindow.h"
#include "homewindow.h"

#include "ownwindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QResizeEvent>

BaseWindow::BaseWindow() {
    // 初始化堆叠小部件并设置页面
    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(new HomeWindow);


    // 设置布局
    setupLayout();

    // 设置按钮点击事件的连接
    setupConnections();

    // 初始化按钮高度
    updateButtonHeights();

    //color
    applyStyles();
}

void BaseWindow::setupLayout() {
    QVBoxLayout *mainLayout = new QVBoxLayout;  // 主布局

    // 创建底部导航栏布局
    QHBoxLayout *bottomBarLayout = new QHBoxLayout;

    // 创建并添加按钮
    homeButton = new QPushButton("首页");
    dateButton = new QPushButton("预约");
    ownButton = new QPushButton("个人");
    chatButton = new QPushButton("聊天");
    liveButton = new QPushButton("住院");

    // 设置按钮的大小策略
    homeButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    dateButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ownButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    chatButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    liveButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // 将按钮添加到底部布局中
    bottomBarLayout->addWidget(homeButton);
    bottomBarLayout->addWidget(dateButton);
    bottomBarLayout->addWidget(ownButton);
    bottomBarLayout->addWidget(chatButton);
    bottomBarLayout->addWidget(liveButton);

    // 设置底部布局的边距和间隔
    bottomBarLayout->setContentsMargins(0, 0, 0, 0);  // 去除边距
    bottomBarLayout->setSpacing(0);  // 去除间隔

    // 设置布局的伸缩因子
    bottomBarLayout->setStretch(0, 1);
    bottomBarLayout->setStretch(1, 1);
    bottomBarLayout->setStretch(2, 1);
    bottomBarLayout->setStretch(3, 1);
    bottomBarLayout->setStretch(4, 1);

    // 将堆叠小部件和底部导航栏布局添加到主布局中
    mainLayout->addWidget(stackedWidget);
    mainLayout->addLayout(bottomBarLayout);
    setLayout(mainLayout);

    // 设置窗口大小
    resize(600, 400);  // 窗口大小为600x400像素
}

void BaseWindow::setupConnections() {
    // 连接按钮点击事件到相应的页面
    connect(homeButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(0); });
    connect(dateButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(1); });
    connect(ownButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(2); });
    connect(chatButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(3); });
    connect(liveButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(4); });
}

void BaseWindow::updateButtonHeights() {
    int height = this->height();  // 获取当前窗口的高度
    int buttonHeight = height * 0.2;  // 计算按钮高度为窗口高度的20%

    // 设置每个按钮的高度
    homeButton->setFixedHeight(buttonHeight);
    dateButton->setFixedHeight(buttonHeight);
    ownButton->setFixedHeight(buttonHeight);
    chatButton->setFixedHeight(buttonHeight);
    liveButton->setFixedHeight(buttonHeight);
}

void BaseWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);  // 调用基类的 resizeEvent 方法

    // 更新按钮高度
    updateButtonHeights();
}

void BaseWindow::applyStyles() {
    // 设置窗口的背景色
    setStyleSheet("background-color: lightblue;");

    // 设置按钮的样式
    QString buttonStyle = R"(
        QPushButton {
            background-color: darkblue;
            color: white;
            border: none;
            font-size: 16px;  // 设置字体大小
        }
        QPushButton:hover {
            background-color: #003366;  // 悬停时的颜色
        }
    )";
    homeButton->setStyleSheet(buttonStyle);
    dateButton->setStyleSheet(buttonStyle);
    ownButton->setStyleSheet(buttonStyle);
    chatButton->setStyleSheet(buttonStyle);
    liveButton->setStyleSheet(buttonStyle);
}

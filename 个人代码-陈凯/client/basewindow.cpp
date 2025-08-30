#include "basewindow.h"
#include "homewindow.h"
#include "datewindow.h"
#include "ownwindow.h"
#include "chatwindow.h"
#include "livewindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QResizeEvent>

BaseWindow::BaseWindow() {
    // 初始化堆叠小部件并设置页面
    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(new HomeWindow);
    stackedWidget->addWidget(new DateWindow);
    stackedWidget->addWidget(new OwnWindow);
    stackedWidget->addWidget(new ChatWindow);
    stackedWidget->addWidget(new LiveWindow);

    // 创建并添加按钮
    homeButton = new QPushButton;
    dateButton = new QPushButton;
    ownButton = new QPushButton;
    chatButton = new QPushButton;
    liveButton = new QPushButton;

    // 设置图标
    homeButton->setIcon(QIcon(":/images/home.png"));
    dateButton->setIcon(QIcon(":/images/appointment.png"));
    ownButton->setIcon(QIcon(":/images/personal.png"));
    chatButton->setIcon(QIcon(":/images/chat.png"));
    liveButton->setIcon(QIcon(":/images/live.png"));

    // 设置图标大小
    updateButtonIconSizes();

    // 创建标签
    homeLabel = new QLabel;
    dateLabel = new QLabel;
    ownLabel = new QLabel;
    chatLabel = new QLabel;
    liveLabel = new QLabel;

    // 设置标签对齐方式
    homeLabel->setAlignment(Qt::AlignCenter);
    dateLabel->setAlignment(Qt::AlignCenter);
    ownLabel->setAlignment(Qt::AlignCenter);
    chatLabel->setAlignment(Qt::AlignCenter);
    liveLabel->setAlignment(Qt::AlignCenter);

    // 设置布局
    setupLayout();
    setupConnections();

    // 应用样式
    applyStyles();
}


void BaseWindow::setupLayout() {
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // 创建底部导航栏布局
    QHBoxLayout *bottomBarLayout = new QHBoxLayout;

    // 创建并添加按钮
    homeButton = new QPushButton;
    dateButton = new QPushButton;
    ownButton = new QPushButton;
    chatButton = new QPushButton;
    liveButton = new QPushButton;

    // 设置标签对齐方式
    homeLabel->setAlignment(Qt::AlignCenter);
    dateLabel->setAlignment(Qt::AlignCenter);
    ownLabel->setAlignment(Qt::AlignCenter);
    chatLabel->setAlignment(Qt::AlignCenter);
    liveLabel->setAlignment(Qt::AlignCenter);

    // 创建一个垂直布局，用于按钮和标签
    QVBoxLayout *homeLayout = new QVBoxLayout;
    homeLayout->addWidget(homeButton);
    homeLayout->addWidget(homeLabel);
    homeLayout->setAlignment(Qt::AlignCenter);  // 确保按钮和标签居中对齐

    QVBoxLayout *dateLayout = new QVBoxLayout;
    dateLayout->addWidget(dateButton);
    dateLayout->addWidget(dateLabel);
    dateLayout->setAlignment(Qt::AlignCenter);  // 确保按钮和标签居中对齐

    QVBoxLayout *ownLayout = new QVBoxLayout;
    ownLayout->addWidget(ownButton);
    ownLayout->addWidget(ownLabel);
    ownLayout->setAlignment(Qt::AlignCenter);  // 确保按钮和标签居中对齐

    QVBoxLayout *chatLayout = new QVBoxLayout;
    chatLayout->addWidget(chatButton);
    chatLayout->addWidget(chatLabel);
    chatLayout->setAlignment(Qt::AlignCenter);  // 确保按钮和标签居中对齐

    QVBoxLayout *liveLayout = new QVBoxLayout;
    liveLayout->addWidget(liveButton);
    liveLayout->addWidget(liveLabel);
    liveLayout->setAlignment(Qt::AlignCenter);  // 确保按钮和标签居中对齐

    // 添加到底部导航栏布局中
    bottomBarLayout->addLayout(homeLayout);
    bottomBarLayout->addLayout(dateLayout);
    bottomBarLayout->addLayout(ownLayout);
    bottomBarLayout->addLayout(chatLayout);
    bottomBarLayout->addLayout(liveLayout);

    // 设置底部布局的边距和间隔
    bottomBarLayout->setContentsMargins(0, 0, 0, 0);
    bottomBarLayout->setSpacing(0);

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
    resize(600, 400);
}



void BaseWindow::setupConnections() {
    // 连接按钮点击事件到相应的页面
    connect(homeButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(0); });
    connect(dateButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(1); });
    connect(ownButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(2); });
    connect(chatButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(3); });
    connect(liveButton, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(4); });
}

void BaseWindow::updateButtonSizes() {
    int buttonSize = qMin(this->width(), this->height()) * 0.2;  // 计算按钮的边长为窗口宽度或高度的15%

    // 设置每个按钮的大小
    homeButton->setFixedSize(buttonSize, buttonSize);
    dateButton->setFixedSize(buttonSize, buttonSize);
    ownButton->setFixedSize(buttonSize, buttonSize);
    chatButton->setFixedSize(buttonSize, buttonSize);
    liveButton->setFixedSize(buttonSize, buttonSize);
}


void BaseWindow::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);  // 调用基类的 resizeEvent 方法

    // 更新按钮高度
    updateButtonSizes();
    updateButtonIconSizes();
}

void BaseWindow::applyStyles() {
    // 设置窗口的背景色
    setStyleSheet("background-color: lightblue;");

    // 设置按钮的样式
    QString buttonStyle = R"(
        QPushButton {
            background-color: transparent;
            border: none;
            background-repeat: no-repeat;
            background-position: center;
            background-size: cover;  // 确保图片自适应按钮的大小
        }
        QPushButton:hover {
            background-color: rgba(0, 0, 0, 0.1);  // 悬停时的颜色
        }
    )";

    // 为每个按钮设置不同的图片
    homeButton->setIcon(QIcon(":/images/home.png"));
    dateButton->setIcon(QIcon(":/images/appointment.png"));
    ownButton->setIcon(QIcon(":/images/personal.png"));
    chatButton->setIcon(QIcon(":/images/chat.png"));
    liveButton->setIcon(QIcon(":/images/live.png"));

    // 设置标签样式
    QString labelStyle = R"(
        QLabel {
            font-size: 14px;
            color: darkblue;
            margin-top: 5px;  // 调整这个值确保标签和按钮之间的间距合适
        }
    )";
    homeLabel->setStyleSheet(labelStyle);
    dateLabel->setStyleSheet(labelStyle);
    ownLabel->setStyleSheet(labelStyle);
    chatLabel->setStyleSheet(labelStyle);
    liveLabel->setStyleSheet(labelStyle);
}

void BaseWindow::updateButtonIconSizes() {
    QSize buttonSize = homeButton->size();  // 获取按钮的当前大小
    QSize iconSize = QSize(buttonSize.width() * 0.7, buttonSize.height() * 0.7);  // 设置图标的大小
    homeButton->setIconSize(iconSize);
    dateButton->setIconSize(iconSize);
    ownButton->setIconSize(iconSize);
    chatButton->setIconSize(iconSize);
    liveButton->setIconSize(iconSize);
}

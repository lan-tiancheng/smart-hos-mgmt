#include "chatwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

ChatWindow::ChatWindow() {
    setupUI();
}

void ChatWindow::setupUI() {
    resize(800, 600);  // 调整窗口大小

    // 创建主布局
    QHBoxLayout *mainLayout = new QHBoxLayout;

    // 创建聊天对象列表
    chatListWidget = new QListWidget;
    chatListWidget->addItem("聊天对象1");
    chatListWidget->addItem("聊天对象2");
    chatListWidget->addItem("聊天对象3");
    chatListWidget->setFixedWidth(200);  // 设置聊天对象列表的固定宽度
    chatListWidget->setStyleSheet("background: #f0f0f0;");  // 设置背景颜色

    // 创建右侧面板
    rightPanel = new QWidget;
    rightPanelLayout = new QVBoxLayout(rightPanel);
    rightPanel->setLayout(rightPanelLayout);

    // 创建右侧区域布局
    mainLayout->addWidget(chatListWidget);
    mainLayout->addWidget(rightPanel);

    setLayout(mainLayout);  // 设置主布局

    // 连接聊天对象选择信号到槽函数
    connect(chatListWidget, &QListWidget::currentTextChanged, this, &ChatWindow::onChatItemSelected);
}

void ChatWindow::onChatItemSelected() {
    QString selectedChat = chatListWidget->currentItem()->text();
    clearRightPanel();  // 清空右侧面板
    showChatForItem(selectedChat);  // 显示选中聊天对象的聊天记录
}

void ChatWindow::clearRightPanel() {
    QLayoutItem *item;
    while ((item = rightPanelLayout->takeAt(0))) {
        delete item->widget();
        delete item;
    }
}

void ChatWindow::showChatForItem(const QString &chatName) {
    QLabel *label = new QLabel("聊天记录 - " + chatName);
    label->setStyleSheet("font-size: 20px; font-weight: bold;");

    chatDisplay = new QTextEdit;
    chatDisplay->setReadOnly(true);  // 设置聊天记录区域为只读

    messageInput = new QTextEdit;
    messageInput->setPlaceholderText("输入消息...");  // 设置输入框的提示文字

    sendButton = new QPushButton("发送");

    rightPanelLayout->addWidget(label);
    rightPanelLayout->addWidget(chatDisplay);
    rightPanelLayout->addWidget(messageInput);
    rightPanelLayout->addWidget(sendButton);
}

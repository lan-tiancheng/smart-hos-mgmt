#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

class ChatWindow : public QWidget {
    Q_OBJECT

public:
    ChatWindow();

private slots:
    void onChatItemSelected();  // 处理聊天对象选择的槽函数

private:
    QListWidget *chatListWidget;  // 聊天室列表
    QWidget *rightPanel;          // 右侧面板
    QVBoxLayout *rightPanelLayout; // 右侧面板的布局
    QTextEdit *chatDisplay;       // 聊天记录显示区域
    QTextEdit *messageInput;      // 消息输入框
    QPushButton *sendButton;      // 发送按钮

    void setupUI();               // 设置用户界面
    void clearRightPanel();       // 清空右侧面板
    void showChatForItem(const QString &chatName);  // 显示选中聊天对象的聊天记录
};

#endif // CHATWINDOW_H

#ifndef OWNWINDOW_H
#define OWNWINDOW_H

#include <QWidget>

class QPushButton;
class OwnIllness;
class OwnDeal;
class OwnMessage;

class OwnWindow : public QWidget {
    Q_OBJECT

public:
    OwnWindow();

private slots:
    void showOwnIllness();  // 显示 OwnIllness 窗口
    void showOwnDeal();     // 显示 OwnDeal 窗口
    void showOwnMessage();  // 显示 OwnMessage 窗口
private:
    OwnIllness *illnessWindow;
    OwnDeal *dealWindow;
    OwnMessage *messageWindow;
};

#endif // OWNWINDOW_H

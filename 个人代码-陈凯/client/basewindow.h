#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>  // 新增

class BaseWindow : public QWidget {
    Q_OBJECT

public:
    BaseWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void setupLayout();
    void setupConnections();
    void updateButtonSizes();  // 修改为更新按钮尺寸
    void updateButtonIconSizes();
    void applyStyles();

    QStackedWidget *stackedWidget;
    QPushButton *homeButton;
    QPushButton *dateButton;
    QPushButton *ownButton;
    QPushButton *chatButton;
    QPushButton *liveButton;

    QLabel *homeLabel;  // 新增
    QLabel *dateLabel;  // 新增
    QLabel *ownLabel;   // 新增
    QLabel *chatLabel;  // 新增
    QLabel *liveLabel;  // 新增
};

#endif // BASEWINDOW_H

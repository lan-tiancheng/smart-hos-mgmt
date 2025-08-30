#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>

class BaseWindow : public QWidget {
    Q_OBJECT

public:
    BaseWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;  // 重写resizeEvent以处理窗口大小改变

private:
    void setupLayout();
    void setupConnections();
    void updateButtonHeights();  // 更新按钮高度的方法
    void applyStyles();

    QStackedWidget *stackedWidget;
    QPushButton *homeButton;
    QPushButton *dateButton;
    QPushButton *ownButton;
    QPushButton *chatButton;
    QPushButton *liveButton;
};

#endif // BASEWINDOW_H

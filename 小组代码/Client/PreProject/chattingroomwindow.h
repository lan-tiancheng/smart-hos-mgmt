#ifndef CHATTINGROOMWINDOW_H
#define CHATTINGROOMWINDOW_H

#include <QWidget>

namespace Ui {
class ChattingroomWindow;
//已废弃的页面
}

class ChattingroomWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChattingroomWindow(QWidget *parent = nullptr);
    ~ChattingroomWindow();

private:
    Ui::ChattingroomWindow *ui;
};

#endif // CHATTINGROOMWINDOW_H

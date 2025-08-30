#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>
#include <QPaintEvent>
#include"usermgr.h"

namespace Ui {
class information;
}

class information : public QWidget
{
    Q_OBJECT

public:
    explicit information(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    ~information();

signals:
    void goback();

private slots:
    void on_pushButton_clicked();
    void on_pushButtonCommit_2_clicked();
    void handleDataUpdated(); // 处理数据更新的槽函数



private:
    Ui::information *ui;
};

#endif // INFORMATION_H

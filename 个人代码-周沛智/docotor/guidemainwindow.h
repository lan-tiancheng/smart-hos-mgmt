/*****************************************
File name:      mainwindow.h
Author:         luolewin
Version:        v1.0
Description:    校园导航主窗口cpp的头文件，函数声明
Date:           2020.12.17
*****************************************/

#ifndef GUIDEMAINWINDOW_H
#define GUIDEMAINWINDOW_H

#include "mystruct.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class guideMainWindow; }
QT_END_NAMESPACE

class guideMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    guideMainWindow(QWidget *parent = nullptr);
    ~guideMainWindow();

    void path(mgraph c,int m,int n,int k);
    void allpath(mgraph c, int start, int end);
    void shortdistance(mgraph c, int start, int end);
    void floyd(mgraph c);

private:
    Ui::guideMainWindow *ui;

protected:
    void paintEvent(QPaintEvent *event);        // 图片绘制方法
    void mousePressEvent(QMouseEvent *event);   // 鼠标左击事件
    void closeEvent(QCloseEvent *event);        // 主窗口退出事件

private slots:
    void on_pushButton_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();
    void on_pushButton_2_clicked();
};
#endif // GUIDEMAINWINDOW_H

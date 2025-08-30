#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include"pinf.h"
#include"information.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //限制输入文本框
    QString content();
    void setMaxWordNum(const int maxNum);
    void setTitle(const QString& title);
    void setContent(const QString& content);


    //不同ui界面跳转
    pinf *window = NULL;
    information *window1 =NULL;

//public slots:
//    void on_PI_clicked();
//    void on_WA_clicked();
//    void on_return_1_clicked();
//    void on_return_2_clicked();
//private slots:
//    void switchPage();
//protected:
//    void resizeEvent(QResizeEvent* event);


protected slots:
    void showTime();
private slots:
    void slot_handleInput();
//    void on_buttonBox_rejected();
//    void on_buttonBox_accepted();

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    void on_checkBox_clicked();
    void on_PI_clicked();
    void on_INF_clicked();


//    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
//    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    int m_maxWordNum;

//    QList<QMainWindow> m_Widget;
//    QMap<QMainWindow*,QRect> m_WidgetRect;
};
#endif // MAINWINDOW_H

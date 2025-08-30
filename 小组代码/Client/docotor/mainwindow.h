#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "pinf.h"
#include "information.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString content();
    void setMaxWordNum(const int maxNum);
    void setTitle(const QString& title);
    void setContent(const QString& content);
    void paintEvent(QPaintEvent *event) override;

    pinf *window = nullptr;
    information *window1 = nullptr;
signals:
    void sig_patient_mesg_need();
    void sig_make_first_list();


protected slots:
    void showTime();

private slots:
    void slot_handleInput();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_checkBox_clicked();
    void on_PI_clicked();
    void on_INF_clicked();
    void on_checkBox_1_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    int m_maxWordNum;
    QPixmap backgroundPixmap;

    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H

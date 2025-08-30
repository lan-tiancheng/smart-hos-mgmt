#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include"registerdialog.h"
#include"resetdialog.h"
#include"pmainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slotSwitchRrg();
    void slotSwitchLogin();
    void slotSwitchReset();
    void SlotSwitchLogin2();
    void SlotSwitchMain();

private:
    Ui::MainWindow *ui;
    LoginDialog* _login_dlg;
    RegisterDialog* _reg_dlg;
    ResetDialog* _reset_dlg;
    PMainWindow* _main_dlg;

};
#endif // MAINWINDOW_H

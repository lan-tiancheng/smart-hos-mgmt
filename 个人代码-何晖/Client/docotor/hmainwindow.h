#ifndef HMAINWINDOW_H
#define HMAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include"registerdialog.h"
#include"resetdialog.h"
//#include"pmainwindow.h"
#include"mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class hMainWindow; }
QT_END_NAMESPACE

class hMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    hMainWindow(QWidget *parent = nullptr);
    ~hMainWindow();
public slots:
    void slotSwitchRrg();
    void slotSwitchLogin();
    void slotSwitchReset();
    void SlotSwitchLogin2();

    void SlotSwitchMain();

private:
    Ui::hMainWindow *ui;
    LoginDialog* _login_dlg;
    RegisterDialog* _reg_dlg;
    ResetDialog* _reset_dlg;
   // PMainWindow* _chat_dlg;
    MainWindow* _main_dlg;

};
#endif // HMAINWINDOW_H

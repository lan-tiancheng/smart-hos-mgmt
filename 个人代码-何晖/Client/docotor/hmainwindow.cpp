#include "hmainwindow.h"
#include "ui_hmainwindow.h"
#include"resetdialog.h"
#include"tcpmgr.h"

hMainWindow::hMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::hMainWindow)
{
    ui->setupUi(this);
    _login_dlg=new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);
    //创建连接至注册
    connect(_login_dlg,&LoginDialog::switchToReg,this,&hMainWindow::slotSwitchRrg);

    connect(_login_dlg,&LoginDialog::switchReset,this,&hMainWindow::slotSwitchReset);

    //连接创建主界面信号
   connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_swich_chatdlg, this, &hMainWindow::SlotSwitchMain);
   //emit TcpMgr::GetInstance()->sig_swich_chatdlg();


}

hMainWindow::~hMainWindow()
{
    delete ui;

}

void hMainWindow::slotSwitchRrg()
{
    _reg_dlg=new RegisterDialog(this);


    _reg_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(_reg_dlg,&RegisterDialog::sigSwitchLogin,this,&hMainWindow::slotSwitchLogin);
    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}

void hMainWindow::slotSwitchLogin()
{
    _login_dlg = new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);

   _reg_dlg->hide();
    _login_dlg->show();
    //连接登录界面注册信号
    connect(_login_dlg, &LoginDialog::switchToReg, this, &hMainWindow::slotSwitchRrg);
    //连接登录页面forget信号
    connect(_login_dlg, &LoginDialog::switchReset, this, &hMainWindow::slotSwitchReset);



}

void hMainWindow::slotSwitchReset()
{
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    _reset_dlg = new ResetDialog(this);
    _reset_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_reset_dlg);

    _login_dlg->hide();
    _reset_dlg->show();
    //注册返回登录信号和槽函数
    connect(_reset_dlg, &ResetDialog::switchLogin, this, &hMainWindow::SlotSwitchLogin2);

}

void hMainWindow::SlotSwitchLogin2()
{
    //创建一个centralWight，设置为mainwehindow中心部件
    _login_dlg = new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);

    _reset_dlg->hide();
    _login_dlg->show();
    //连接登录页面forget信号
    connect(_login_dlg, &LoginDialog::switchReset, this, &hMainWindow::slotSwitchReset);
    //连接登录页面注册信号
    connect(_login_dlg, &LoginDialog::switchToReg, this, &hMainWindow::slotSwitchRrg);
}

void hMainWindow::SlotSwitchMain()
{
    _main_dlg = new MainWindow();
    _main_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_main_dlg);
    _main_dlg->show();
    _login_dlg->hide();
    this->setMinimumSize(QSize(1000,400));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}



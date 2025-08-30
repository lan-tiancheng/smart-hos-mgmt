#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"resetdialog.h"
#include "tcpmgr.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _login_dlg=new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);
    //创建连接至注册
    connect(_login_dlg,&LoginDialog::switchToReg,this,&MainWindow::slotSwitchRrg);
    connect(_login_dlg,&LoginDialog::switchReset,this,&MainWindow::slotSwitchReset);
    //连接创建主界面信号
       connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_swich_chatdlg, this, &MainWindow::SlotSwitchMain);
       //emit TcpMgr::GetInstance()->sig_swich_chatdlg();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::slotSwitchRrg()
{
    _reg_dlg=new RegisterDialog(this);


    _reg_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    connect(_reg_dlg,&RegisterDialog::sigSwitchLogin,this,&MainWindow::slotSwitchLogin);
    setCentralWidget(_reg_dlg);
    _login_dlg->hide();
    _reg_dlg->show();
}

void MainWindow::slotSwitchLogin()
{
    _login_dlg = new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);

   _reg_dlg->hide();
    _login_dlg->show();
    //连接登录界面注册信号
    connect(_login_dlg, &LoginDialog::switchToReg, this, &MainWindow::slotSwitchRrg);
    //连接登录页面forget信号
    connect(_login_dlg, &LoginDialog::switchReset, this, &MainWindow::slotSwitchReset);

    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_swich_chatdlg, this, &MainWindow::SlotSwitchMain);


    //测试
   // emit TcpMgr::GetInstance()->sig_swich_chatdlg();



}

void MainWindow::slotSwitchReset()
{
    //创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    _reset_dlg = new ResetDialog(this);
    _reset_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_reset_dlg);

    _login_dlg->hide();
    _reset_dlg->show();
    //注册返回登录信号和槽函数
    connect(_reset_dlg, &ResetDialog::switchLogin, this, &MainWindow::SlotSwitchLogin2);

}

void MainWindow::SlotSwitchLogin2()
{
    //创建一个centralWight，设置为mainwehindow中心部件
    _login_dlg = new LoginDialog(this);
    _login_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_login_dlg);

    _reset_dlg->hide();
    _login_dlg->show();
    //连接登录页面forget信号
    connect(_login_dlg, &LoginDialog::switchReset, this, &MainWindow::slotSwitchReset);
    //连接登录页面注册信号
    connect(_login_dlg, &LoginDialog::switchToReg, this, &MainWindow::slotSwitchRrg);
}
void MainWindow::SlotSwitchMain()
{
    _main_dlg = new PMainWindow();
    _main_dlg->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    setCentralWidget(_main_dlg);
    _main_dlg->show();
    _login_dlg->hide();
    this->setMinimumSize(QSize(675,300));
    this->setMaximumSize(QWIDGETSIZE_MAX, 690);
}

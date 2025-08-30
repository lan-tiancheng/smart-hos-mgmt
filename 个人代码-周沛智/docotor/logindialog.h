#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include"global.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_pushButton_2_clicked();
    void slot_forget_pwd();


    void slot_login_mod_finish(ReqId id,QString res,ErrorCode err);

    void on_loginBtn_clicked();
    void slot_tcp_con_finish(bool bsuccess);
    void slot_login_failed(int err);

private:
    void initHttpHandlers();
    void initHead();
    bool checkUserValid();
    bool checkPwdValid();
    bool enableBtn(bool enabled);
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    QMap<TipErr,QString> _tip_errs;
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    void showTip(QString str,bool b_ok);
    Ui::LoginDialog *ui;
    int _uid;
    QString _token;
signals:
    void switchToReg();
    void switchReset();
    void sig_connect_tcp(ServerInfo);
};

#endif // LOGINDIALOG_H

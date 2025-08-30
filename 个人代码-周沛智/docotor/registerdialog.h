#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"
#include <functional>
#include <QMap>
#include <QJsonObject>
#include <QSet>
#include <QTimer>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_get_code_clicked();
    void on_sure_btn_clicked();

    void on_return_btn_clicked();

    void on_cancel_btn_clicked();

    void on_confirmInfo_clicked();

    void on_manRadioButton_clicked();

    void on_womanRadbutton_clicked();

    void on_otherSex_clicked();

public slots:
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCode err);
private:
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPassValid();
    bool checkVarifyValid();
    bool checkConfirmValid();
    bool checkYear();
    bool checkIDcard();
    bool checkPhone();
    void initHttpHandlers();
    void AddTipErr(TipErr te,QString tips);
    void DelTipErr(TipErr te);
    void ChangeTipPage();
    void ChangeTipPageToThree();
    void AddTipErrInfo(TipErr te, QString tips);
    void DelTipErrInfo(TipErr te);
    bool isDateFormatValid(const QString& year, const QString& month, const QString& day);
    bool isValidDate(const QString& year, const QString& month, const QString& day);
    bool isValidPhoneNumber(const QString& phoneNumber);
    bool isValidIDCard(const QString& idCard);
    QString workID;
    QString sex;
    void showTipInPage2(QString str,bool b_ok );
    Ui::RegisterDialog *ui;
    void showTip(QString str,bool b_ok);
    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr, QString> _tip_errs;
    QTimer * _countdown_timer;
    int _countdown;
signals:
    void sigSwitchLogin();
};

#endif // REGISTERDIALOG_H

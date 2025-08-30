#ifndef ADVICE_H
#define ADVICE_H

#include <QDialog>

namespace Ui {
class advice;
}

class advice : public QDialog
{
    Q_OBJECT

public:
    explicit advice(QWidget *parent = nullptr);
    ~advice();

signals:
    void confirmClicked(const QString &adviceText);

private slots:
    void on_buttonConfirm_clicked();
    void on_buttonCancel_clicked();

private:
    Ui::advice *ui;
};

#endif // ADVICE_H

#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT
    
public:
    explicit Register(QWidget *parent = 0);
    ~Register();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Register *ui;
    QSqlQuery query;

    void refreshRegister();

};

#endif // REGISTER_H

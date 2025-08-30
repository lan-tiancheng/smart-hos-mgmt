#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include <QDialog>
#include "DataType.h"
#include <QDebug>
#include <QSqlQuery>
//#include <QtSql/QSqlQuery>
#include <QStandardItemModel>

namespace Ui {
class MedicalRecord;
}

class MedicalRecord : public QDialog
{
    Q_OBJECT
    
public:
    explicit MedicalRecord(QWidget *parent = 0);
    ~MedicalRecord();
    void setUserInfo();
    void loadMedicalData();

    
private:
    Ui::MedicalRecord *ui;
    //user *user_indoor;
    QSqlQuery query;
    QStringList timeList;
    QStandardItemModel *timeItemModel;
private slots:
    void itemClicked(QModelIndex index);
};

#endif // MEDICALRECORD_H

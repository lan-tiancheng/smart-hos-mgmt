#ifndef OUTWD_H
#define OUTWD_H

#include <QWidget>
#include "OutDoc.h"

namespace Ui {
class OutWd;
}

class OutWd : public QWidget
{
    Q_OBJECT

public:
    explicit OutWd(QWidget *parent = nullptr);
    ~OutWd();
public:
    QString str;
    void datatrans(int num,QString *id,QString *name,QString *introduce,QString *position);
    QVector<OutDoc> outdoc;

private slots:
    void showdate();
private:
    Ui::OutWd *ui;
};

#endif // OUTWD_H

#ifndef INSIDEWD_H
#define INSIDEWD_H

#include <QWidget>
#include "InsideDoc.h"

namespace Ui {
class InsideWd;
}

class InsideWd : public QWidget
{
    Q_OBJECT

public:
    explicit InsideWd(QWidget *parent = nullptr);
    ~InsideWd();
public:
    QString str;
    void datatrans(int num,QString *id,QString *name,QString *introduce,QString *position);
    QVector<InsideDoc> insidedoc;

private slots:
    void showdate();
private:
    Ui::InsideWd *ui;
};

#endif // INSIDEWD_H

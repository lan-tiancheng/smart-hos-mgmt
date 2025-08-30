#ifndef CHILDWD_H
#define CHILDWD_H

#include <QWidget>
#include "ChildDoc.h"

namespace Ui {
class ChildWd;
}

class ChildWd : public QWidget
{
    Q_OBJECT

public:
    explicit ChildWd(QWidget *parent = nullptr);
    ~ChildWd();
//private slots:
//    void showdate();
public:
    QString str;
    void datatrans(int num,QString *id,QString *name,QString *introduce,QString *position);
    QVector<ChildDoc> childdoc;
private slots:
    void showdate();
private:
    Ui::ChildWd *ui;
};

#endif // CHILDWD_H

#ifndef SKINWD_H
#define SKINWD_H

#include <QWidget>
#include "SkinDoc.h"

namespace Ui {
class SkinWd;
}

class SkinWd : public QWidget
{
    Q_OBJECT

public:
    explicit SkinWd(QWidget *parent = nullptr);
    ~SkinWd();
public:
    QString str;
    void datatrans(int num,QString *id,QString *name,QString *introduce,QString *position);
    QVector<SkinDoc> skindoc;

private slots:
    void showdate();
private:
    Ui::SkinWd *ui;
};

#endif // SKINWD_H

#ifndef WOMANWD_H
#define WOMANWD_H

#include <QWidget>
#include "WomanDoc.h"

namespace Ui {
class WomanWd;
}

class WomanWd : public QWidget
{
    Q_OBJECT

public:
    explicit WomanWd(QWidget *parent = nullptr);
    ~WomanWd();
private slots:
    void showdate();
public:
    QString str;
    void datatrans(int num,QString *id,QString *name,QString *introduce,QString *position);
    QVector<WomanDoc> womandoc;

private:
    Ui::WomanWd *ui;
};

#endif // WOMANWD_H

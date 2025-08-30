#ifndef MISEARCHSONWD_H
#define MISEARCHSONWD_H

#include <QWidget>

namespace Ui {
class MIsearchSonWd;
}

class MIsearchSonWd : public QWidget
{
    Q_OBJECT

public:
    explicit MIsearchSonWd(QWidget *parent = nullptr);
    ~MIsearchSonWd();

private:
    Ui::MIsearchSonWd *ui;
};

#endif // MISEARCHSONWD_H

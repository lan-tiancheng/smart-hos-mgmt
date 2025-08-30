#ifndef MEDICALEXPENSEWD_H
#define MEDICALEXPENSEWD_H

#include <QWidget>

namespace Ui {
class MedicalExpenseWd;
}

class MedicalExpenseWd : public QWidget
{
    Q_OBJECT

public:
    explicit MedicalExpenseWd(QWidget *parent = nullptr);
    ~MedicalExpenseWd();

private:
    Ui::MedicalExpenseWd *ui;
    virtual void paintEvent(QPaintEvent *);
};

#endif // MEDICALEXPENSEWD_H

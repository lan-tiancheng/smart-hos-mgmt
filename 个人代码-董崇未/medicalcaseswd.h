#ifndef MEDICALCASESWD_H
#define MEDICALCASESWD_H

#include <QWidget>

namespace Ui {
class MedicalcasesWd;
}

class MedicalcasesWd : public QWidget
{
    Q_OBJECT

public:
    explicit MedicalcasesWd(QWidget *parent = nullptr);
    ~MedicalcasesWd();

private:
    Ui::MedicalcasesWd *ui;
};

#endif // MEDICALCASESWD_H

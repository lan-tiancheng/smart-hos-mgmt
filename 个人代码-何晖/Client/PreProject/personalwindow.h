#ifndef PERSONALWINDOW_H
#define PERSONALWINDOW_H

#include <QWidget>
#include "personalinfowindow.h"
#include "medicalcaseswd.h"

namespace Ui {
class PersonalWindow;
}

class PersonalWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalWindow(QWidget *parent = nullptr);
    ~PersonalWindow();

private slots:
    void on_personalinfoBtn_clicked();

    void on_medicalcasesBtn_clicked();

private:
    Ui::PersonalWindow *ui;
};

#endif // PERSONALWINDOW_H

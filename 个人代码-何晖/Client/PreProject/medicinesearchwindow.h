#ifndef MEDICINESEARCHWINDOW_H
#define MEDICINESEARCHWINDOW_H

#include <QWidget>
#include <QVector>
#include "homewindow.h"
#include "MedicineItem.h"
#include "misearchsonwd.h"

namespace Ui {
class MedicineSearchWindow;
}

class MedicineSearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MedicineSearchWindow(QWidget *parent = nullptr);
    ~MedicineSearchWindow();
public:
    void sendText(QString);

private slots:
    void on_backbtn_clicked();

    void on_searchBtn_clicked();

private:
    Ui::MedicineSearchWindow *ui;
    //QVector<MedicineItem> medicineitem;

};

#endif // MEDICINESEARCHWINDOW_H

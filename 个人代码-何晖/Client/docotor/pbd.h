#ifndef PBD_H
#define PBD_H

#include <QWidget>
#include <QString>
//#include"pinf.h"

namespace Ui {
class pbd;
}

class pbd : public QWidget
{
    Q_OBJECT

public:
    explicit pbd(QWidget *parent = nullptr);
    ~pbd();
    QString paintid;

signals:
    void goback();

public slots:
    void populateData(const QString &jsonString);

private slots:
    void on_pushButton_return_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::pbd *ui;
    void paintEvent(QPaintEvent *event);
    //pinf* pin;
};

#endif // PBD_H

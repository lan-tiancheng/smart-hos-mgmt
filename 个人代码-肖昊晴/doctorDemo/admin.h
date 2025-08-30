#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

namespace Ui {
class book;
}

class book : public QWidget
{
    Q_OBJECT

public:
    explicit book(QWidget *parent = nullptr);
    ~book();

signals:
    void goback();

private slots:
    void on_pushButton_clicked();


private:
    Ui::book *ui;
};

#endif // ADMIN_H

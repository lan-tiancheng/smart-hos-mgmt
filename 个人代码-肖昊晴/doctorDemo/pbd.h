#ifndef PBD_H
#define PBD_H

#include <QWidget>

namespace Ui {
class pbd;
}

class pbd : public QWidget
{
    Q_OBJECT

public:
    explicit pbd(QWidget *parent = nullptr);
    ~pbd();

signals:
    void goback();

private slots:
    void on_pushButton_return_clicked();

private:
    Ui::pbd *ui;
};

#endif // PBD_H

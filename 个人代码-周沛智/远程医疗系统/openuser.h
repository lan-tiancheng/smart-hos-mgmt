#ifndef OPENUSER_H
#define OPENUSER_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

namespace Ui {
class OpenUser;
}

class OpenUser : public QDialog
{
    Q_OBJECT
    
public:
    explicit OpenUser(QWidget *parent = 0);
    ~OpenUser();
    void refresh();
    
private:
    Ui::OpenUser *ui;
    QSqlRelationalTableModel *model;
    QSqlRelationalTableModel *model_2;

};

#endif // OPENUSER_H

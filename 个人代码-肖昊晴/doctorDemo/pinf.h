#ifndef PINF_H
#define PINF_H

#include <QWidget>
#include <QTableView>
#include <QTableWidgetItem>
#include"pbd.h"

namespace Ui {
class pinf;
}

class pinf : public QWidget
{
    Q_OBJECT

public:
    explicit pinf(QWidget *parent = nullptr);
    ~pinf();
    pbd *windowp = NULL;

signals:
    void goback();

private slots:
    void on_pushButton_clicked();
    void on_tableViewRecordation_2_doubleClicked(const QModelIndex &index);

private:
    Ui::pinf *ui;
    void setupTableViewStyle(QTableView *tableView);
};

#endif // PINF_H

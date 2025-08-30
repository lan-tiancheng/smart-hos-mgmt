#ifndef OWNDEAL_H
#define OWNDEAL_H

#include <QWidget>

class QPushButton;
class QTableView;
class QStandardItemModel;

class OwnDeal : public QWidget {
    Q_OBJECT

public:
    OwnDeal(QWidget *parent = nullptr);

private slots:
    void showDetails();  // 显示详细信息
    void goBack();

private:
    void initializeTable();

    QPushButton *backButton;
    QTableView *tableView;
    QStandardItemModel *model;
};

#endif // OWNDEAL_H

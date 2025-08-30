#ifndef OWNILLNESS_H
#define OWNILLNESS_H

#include <QWidget>

class QPushButton;
class QTableView;
class QStandardItemModel;

class OwnIllness : public QWidget {
    Q_OBJECT

public:
    OwnIllness(QWidget *parent = nullptr);

private slots:
    void goBack();

private:
    void initializeTable();

    QPushButton *backButton;
    QTableView *tableView;
    QStandardItemModel *model;
};

#endif // OWNILLNESS_H

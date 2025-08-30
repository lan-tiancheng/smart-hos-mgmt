#ifndef OWNILLNESS_H
#define OWNILLNESS_H

#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QCloseEvent>

class OwnIllness : public QWidget {
    Q_OBJECT

public:
    OwnIllness(QWidget *parent = nullptr);

signals:
    void back();

private slots:
    void goBack();

public:
    void initializeTable();

    QPushButton *backButton;
    QTableView *tableView;
    QStandardItemModel *model;
};

#endif // OWNILLNESS_H

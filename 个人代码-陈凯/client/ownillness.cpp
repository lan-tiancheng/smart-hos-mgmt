#include "ownillness.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>

OwnIllness::OwnIllness(QWidget *parent) : QWidget(parent) {
    resize(600, 400);

    QVBoxLayout *layout = new QVBoxLayout;

    // 创建返回按钮
    backButton = new QPushButton("返回");
    layout->addWidget(backButton);

    // 创建表格视图
    tableView = new QTableView;
    initializeTable();
    layout->addWidget(tableView);

    // 连接返回按钮的信号到槽函数
    connect(backButton, &QPushButton::clicked, this, &OwnIllness::goBack);

    setLayout(layout);
}

void OwnIllness::initializeTable() {
    model = new QStandardItemModel(10, 5, this);  // 创建一个10行5列的模型
    tableView->setModel(model);

    model->setHorizontalHeaderLabels({"列1", "列2", "列3", "列4", "列5"});

    // 填充模型数据
    for (int row = 0; row < 10; ++row) {
        for (int column = 0; column < 5; ++column) {
            QStandardItem *item = new QStandardItem(QString("数据 %1,%2").arg(row).arg(column));
            model->setItem(row, column, item);
        }
    }
}

void OwnIllness::goBack() {
    close();  // 关闭当前窗口
}

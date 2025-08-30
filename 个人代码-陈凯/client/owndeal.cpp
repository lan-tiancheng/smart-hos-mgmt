#include "owndeal.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>

OwnDeal::OwnDeal(QWidget *parent) : QWidget(parent) {
    resize(600, 400);

    QVBoxLayout *layout = new QVBoxLayout;

    backButton = new QPushButton("返回");
    layout->addWidget(backButton);
    // 创建表格视图
    tableView = new QTableView;
    initializeTable();
    layout->addWidget(tableView);

    // 连接返回按钮的信号到槽函数
    connect(backButton, &QPushButton::clicked, this, &OwnDeal::goBack);

    setLayout(layout);
}

void OwnDeal::initializeTable() {
    model = new QStandardItemModel(10, 6, this);  // 创建一个10行6列的模型
    tableView->setModel(model);

    model->setHorizontalHeaderLabels({"列1", "列2", "列3", "列4", "列5", "操作"});

    // 填充模型数据
    for (int row = 0; row < 10; ++row) {
        for (int column = 0; column < 5; ++column) {
            QStandardItem *item = new QStandardItem(QString("数据 %1,%2").arg(row).arg(column));
            model->setItem(row, column, item);
        }

        // 添加“查看”按钮到最后一列
        QPushButton *viewButton = new QPushButton("查看");
        connect(viewButton, &QPushButton::clicked, this, &OwnDeal::showDetails);
        model->setItem(row, 5, new QStandardItem());
        tableView->setIndexWidget(model->index(row, 5), viewButton);
    }
}

void OwnDeal::showDetails() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QMessageBox::information(this, "详细信息", "这是详细信息！");
    }
}

void OwnDeal::goBack() {
    close();  // 关闭当前窗口
}


#include "ownillness.h"
#include "GlobalData.h"
#include <QVBoxLayout>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <QDebug>

//QVector<RegisterDataTransmit> GlobalData::registerdata;

OwnIllness::OwnIllness(QWidget *parent) : QWidget(parent) {
    resize(600, 400);
    QVBoxLayout *layout = new QVBoxLayout;

    backButton = new QPushButton("返回");
    layout->addWidget(backButton);

    tableView = new QTableView;
    initializeTable();
    layout->addWidget(tableView);

    connect(backButton, &QPushButton::clicked, this, &OwnIllness::goBack);

    setLayout(layout);
}

void OwnIllness::initializeTable() {
    model = new QStandardItemModel(10, 5, this);
    tableView->setModel(model);

    model->setHorizontalHeaderLabels({"日期", "时间", "科室", "医生","预约状态" });

    int size=GlobalData::registerdata.size();
    qDebug()<<size;
        for (int row = 0; row < size; ++row) {
            for (int column = 0; column < 5; ++column) {
                if(column==0){
                    QStandardItem *item = new QStandardItem(QString("%1").arg(GlobalData::registerdata[row].Date));
                    model->setItem(row, column, item);
                }else if(column==1){
                    QStandardItem *item = new QStandardItem(QString("%1").arg(GlobalData::registerdata[row].Hour));
                    model->setItem(row, column, item);
                }else if(column==2){
                    QStandardItem *item = new QStandardItem(QString("%1").arg(GlobalData::registerdata[row].Room));
                    model->setItem(row, column, item);
                }else if(column==3){
                    QStandardItem *item = new QStandardItem(QString("%1").arg(GlobalData::registerdata[row].Name));
                    model->setItem(row, column, item);
                }else if(column==4){
                    QStandardItem *item = new QStandardItem(QString("成功"));
                    model->setItem(row, column, item);
                }

            }
        }


}

void OwnIllness::goBack() {
    emit back();
}

#include "owndeal.h"
#include "usermgr.h"
#include <QVBoxLayout>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <QMessageBox>

OwnDeal::OwnDeal(QWidget *parent) : QWidget(parent) {
    resize(600, 400);  // 设置与主窗口相同的大小
    QVBoxLayout *layout = new QVBoxLayout;

    backButton = new QPushButton("返回");
    layout->addWidget(backButton);

    tableView = new QTableView;

    //请在此处调用initializeTable();
    QVector<QVector<QString>> guahaoData = UserMgr::GetInstance()->getGuahaoDataByUid(UserMgr::GetInstance()->getUid());

     int num = guahaoData.size();
     QString* doctorNames = new QString[num];
     QString* checkResults = new QString[num];
     QString* prescriptions = new QString[num];

     for (int i = 0; i < num; ++i) {
         doctorNames[i] = guahaoData[i][3];   // doctorname 列
         checkResults[i] = guahaoData[i][10]; // checkresult 列
         prescriptions[i] = guahaoData[i][11]; // chufang 列
     }

     // 调用 initializeTable 方法
     this->initializeTable(num, doctorNames, checkResults, prescriptions);

     // 清理动态分配的内存
     delete[] doctorNames;
     delete[] checkResults;
     delete[] prescriptions;

    layout->addWidget(tableView);

    connect(backButton, &QPushButton::clicked, this, &OwnDeal::goBack);

    setLayout(layout);
}

void OwnDeal::initializeTable(int num,QString *docname,QString *judge,QString *prescription) {
    model = new QStandardItemModel(10, 5, this);
    tableView->setModel(model);

    model->setHorizontalHeaderLabels({"医生", "临床诊断", "处方", "操作"});

    for (int row = 0; row < num; ++row) {
        for (int column = 0; column < 3; ++column) {
            if(column==0){
                QStandardItem *item = new QStandardItem(QString("%1").arg(docname[row]));
                model->setItem(row, column, item);
            }else if(column==1){
                QStandardItem *item = new QStandardItem(QString("%1").arg(judge[row]));
                model->setItem(row, column, item);
            }else if(column==2){
                QStandardItem *item = new QStandardItem(QString("%1").arg(prescription[row]));
                model->setItem(row, column, item);
            }else if(column==3){
                //QStandardItem *item = new QStandardItem(QString("%1").arg(note[row]));
                //model->setItem(row, column, item);
            }

        }
        QPushButton *viewButton = new QPushButton("查看");
        connect(viewButton, &QPushButton::clicked, this, &OwnDeal::showDetails);
        model->setItem(row, 3, new QStandardItem());
        tableView->setIndexWidget(model->index(row, 3), viewButton);
    }
}

void OwnDeal::showDetails() {
    QMessageBox::information(this, "详细信息", "这是详细信息！");
}

void OwnDeal::goBack()
{
    emit back();
}


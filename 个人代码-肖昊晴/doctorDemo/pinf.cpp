#include "pinf.h"
#include "ui_pinf.h"


#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>


void pinf::setupTableViewStyle(QTableView *tableView)
{
    tableView->setShowGrid(true);  // 显示网格线

    // 自定义水平头部样式
    QHeaderView *horizontalHeader = tableView->horizontalHeader();
    horizontalHeader->setStyleSheet(
        "QHeaderView::section { "
        "border: 1px solid black; "         // 头部边框
        "background-color: #f0f0f0; "       // 头部背景色
        "padding: 5px; "                    // 头部内边距
        "}"
    );

    // 自定义垂直头部样式
    QHeaderView *verticalHeader = tableView->verticalHeader();
    verticalHeader->setStyleSheet(
        "QHeaderView::section { "
        "border: 1px solid black; "         // 头部边框
        "background-color: #f0f0f0; "       // 头部背景色
        "padding: 5px; "                    // 头部内边距
        "}"
    );

    // 自定义表格项样式
    tableView->setStyleSheet(
        "QTableView::item { "
        "border-right: 1px solid black; "   // 单元格右边框
        "border-bottom: 1px solid black; "  // 单元格底边框
        "padding: 5px; "                    // 单元格内边距
        "}"
        "QTableView::item:selected { "
        "background-color: lightblue; "    // 选中单元格背景色
        "}"
    );

    // 设置头部高度和宽度
    horizontalHeader->setFixedHeight(30); // 水平头部高度
    verticalHeader->setFixedWidth(70);    // 垂直头部宽度
}

pinf::pinf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pinf)
{
    ui->setupUi(this);


    this->windowp = new pbd;
    connect(windowp,&pbd::goback,this,[=]()
    {
        windowp->close();
        this->show();
    });


    // 初始化并设置“预约记录”标签页的模型
       QStandardItemModel *recordationModel = new QStandardItemModel(0, 7, this);
       recordationModel->setHorizontalHeaderLabels({
           "患者编号", "患者姓名", "患者账号", "患者性别", "患者年龄",
           "患者预约日期", "患者信息资料"
       });
      ui->tableViewRecordation_2->setModel(recordationModel);;
       setupTableViewStyle(ui->tableViewRecordation_2); // 设置预约记录表格样式

       // 初始化并设置“诊断记录”标签页的模型
       QStandardItemModel *userModel = new QStandardItemModel(0, 8, this);
       userModel->setHorizontalHeaderLabels({
           "患者编号", "患者姓名", "患者账号", "患者性别", "患者年龄",
           "患者预约日期", "患者信息资料", "诊断结果"
       });
       ui->tableViewUser_2->setModel(userModel);
       setupTableViewStyle(ui->tableViewUser_2); // 设置诊断记录表格样式

       // 初始化并设置“处方记录”标签页的模型
       QStandardItemModel *goodsModel = new QStandardItemModel(0, 9, this);
       goodsModel->setHorizontalHeaderLabels({
           "患者编号", "患者姓名", "患者账号", "患者性别", "患者年龄",
           "患者预约日期", "患者信息资料", "诊断结果", "处方"
       });
       ui->tableViewGoods_2->setModel(goodsModel);
       setupTableViewStyle(ui->tableViewGoods_2); // 设置处方记录表格样式

       // 初始化并设置“住院记录”标签页的模型
       QStandardItemModel *statisticsModel = new QStandardItemModel(0, 5, this);
       statisticsModel->setHorizontalHeaderLabels({
           "患者编号", "患者姓名", "病房号", "病床号", "住院日期"
       });
       ui->tableViewStatistics_2->setModel(statisticsModel);
       setupTableViewStyle(ui->tableViewStatistics_2); // 设置住院记录表格样式

       // 示例数据填充
       // 请根据需要替换或添加实际数据
       for (int row = 0; row < 10; ++row) {
           recordationModel->setItem(row, 0, new QStandardItem(QString::number(row)));
           recordationModel->setItem(row, 1, new QStandardItem("姓名" + QString::number(row)));
           recordationModel->setItem(row, 2, new QStandardItem("账号" + QString::number(row)));
           recordationModel->setItem(row, 3, new QStandardItem("性别" + QString::number(row)));
           recordationModel->setItem(row, 4, new QStandardItem(QString::number(20 + row)));
           recordationModel->setItem(row, 5, new QStandardItem("日期" + QString::number(row)));
           recordationModel->setItem(row, 6, new QStandardItem("信息" + QString::number(row)));
       }

       for (int row = 0; row < 10; ++row) {
           userModel->setItem(row, 0, new QStandardItem(QString::number(row)));
           userModel->setItem(row, 1, new QStandardItem("姓名" + QString::number(row)));
           userModel->setItem(row, 2, new QStandardItem("账号" + QString::number(row)));
           userModel->setItem(row, 3, new QStandardItem("性别" + QString::number(row)));
           userModel->setItem(row, 4, new QStandardItem(QString::number(20 + row)));
           userModel->setItem(row, 5, new QStandardItem("日期" + QString::number(row)));
           userModel->setItem(row, 6, new QStandardItem("信息" + QString::number(row)));
           userModel->setItem(row, 7, new QStandardItem("结果" + QString::number(row)));
       }

       for (int row = 0; row < 10; ++row) {
           goodsModel->setItem(row, 0, new QStandardItem(QString::number(row)));
           goodsModel->setItem(row, 1, new QStandardItem("姓名" + QString::number(row)));
           goodsModel->setItem(row, 2, new QStandardItem("账号" + QString::number(row)));
           goodsModel->setItem(row, 3, new QStandardItem("性别" + QString::number(row)));
           goodsModel->setItem(row, 4, new QStandardItem(QString::number(20 + row)));
           goodsModel->setItem(row, 5, new QStandardItem("日期" + QString::number(row)));
           goodsModel->setItem(row, 6, new QStandardItem("信息" + QString::number(row)));
           goodsModel->setItem(row, 7, new QStandardItem("结果" + QString::number(row)));
           goodsModel->setItem(row, 8, new QStandardItem("处方" + QString::number(row)));
       }

       for (int row = 0; row < 10; ++row) {
           statisticsModel->setItem(row, 0, new QStandardItem(QString::number(row)));
           statisticsModel->setItem(row, 1, new QStandardItem("姓名" + QString::number(row)));
           statisticsModel->setItem(row, 2, new QStandardItem("病房" + QString::number(row)));
           statisticsModel->setItem(row, 3, new QStandardItem("床号" + QString::number(row)));
           statisticsModel->setItem(row, 4, new QStandardItem("日期" + QString::number(row)));
       }
}


//pinf界面和pbd界面切换相关
void pinf::on_tableViewRecordation_2_doubleClicked(const QModelIndex &index)
{
    if(index.column()==0)
    {
        this->hide();
        windowp->show();
    }
}

pinf::~pinf()
{
    delete ui;
}

//MianWindow界面和pinf界面切换相关
void pinf::on_pushButton_clicked()
{
    emit goback();
}


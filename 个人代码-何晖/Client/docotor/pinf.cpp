#include "pinf.h"
#include "ui_pinf.h"
#include "mainwindow.h"
#include <QHeaderView>
#include <QStandardItemModel>
#include <qjsondocument.h>
#include"mainwindow.h"
#include"tcpmgr.h"
#include <QPushButton>
#include <QMouseEvent>
#include <asm-generic/errno.h>

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

// ButtonDelegate 实现
ButtonDelegate::ButtonDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void ButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 7) { // 假设按钮在第8列
        QStyleOptionButton buttonOpt;
        buttonOpt.rect = option.rect;
        buttonOpt.text = "详情";
        buttonOpt.state = QStyle::State_Enabled;

        QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonOpt, painter);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

bool ButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (index.column() == 7 && event->type() == QEvent::MouseButtonRelease) {
        emit buttonClicked(index);
        return true;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

pinf::pinf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pinf)
{
    ui->setupUi(this);
    ui->tableViewRecordation_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewUser_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewGoods_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewStatistics_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setStyleSheet("background-color: skyblue;");
    this->windowp = new pbd;
    connect(windowp, &pbd::goback, this, [=]() {
        windowp->close();
        this->show();
    });
     connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_make_first_list,this,&pinf::setRecordationData);

    buttonDelegate = new ButtonDelegate(this);
    connect(buttonDelegate, &ButtonDelegate::buttonClicked, this, &pinf::onButtonClicked);

    // 初始化表格模型
    QStandardItemModel *recordationModel = new QStandardItemModel(0, 8, this);
    recordationModel->setHorizontalHeaderLabels({
        "患者编号", "患者姓名", "患者账号", "患者性别", "患者年龄",
        "患者预约日期", "患者信息资料", "操作"
    });
    ui->tableViewRecordation_2->setModel(recordationModel);
    ui->tableViewRecordation_2->setItemDelegateForColumn(7, buttonDelegate);
    setupTableViewStyle(ui->tableViewRecordation_2);

    QStandardItemModel *userModel = new QStandardItemModel(0, 8, this);
    userModel->setHorizontalHeaderLabels({
        "患者编号", "患者姓名", "患者账号", "患者性别", "患者年龄",
        "患者预约日期", "患者信息资料", "诊断结果"
    });
    ui->tableViewUser_2->setModel(userModel);
    setupTableViewStyle(ui->tableViewUser_2);

    QStandardItemModel *goodsModel = new QStandardItemModel(0, 9, this);
    goodsModel->setHorizontalHeaderLabels({
        "患者编号", "患者姓名", "患者账号", "患者性别", "患者年龄",
        "患者预约日期", "患者信息资料", "诊断结果", "处方"
    });
    ui->tableViewGoods_2->setModel(goodsModel);
    setupTableViewStyle(ui->tableViewGoods_2);

    QStandardItemModel *statisticsModel = new QStandardItemModel(0, 5, this);
    statisticsModel->setHorizontalHeaderLabels({
        "患者编号", "患者姓名", "病房号", "病床号", "住院日期"
    });
    ui->tableViewStatistics_2->setModel(statisticsModel);
    setupTableViewStyle(ui->tableViewStatistics_2);

    connect(buttonDelegate, &ButtonDelegate::buttonClicked, this, &pinf::onButtonClicked);
}

void pinf::setRecordationData(const QVector<QVector<QString>> &data)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableViewRecordation_2->model());
    if (model) {
        model->clear();  // 清空现有数据
        model->setHorizontalHeaderLabels({
            "患者编号", "患者姓名", "患者账号", "患者性别", "患者年龄",
            "患者预约日期", "患者信息资料", "详情"
        });

        int rowCount = data.size();
        model->setRowCount(rowCount);  // 设置行数

        patientIds.clear(); // 清空现有的患者编号

        for (int row = 0; row < rowCount; ++row) {
            const QVector<QString> &dataRow = data[row];
            if (dataRow.size() == 8) {
                for (int col = 1; col < dataRow.size(); ++col) {
                    model->setItem(row, col, new QStandardItem(dataRow[col]));
                }
                patientIds.append(dataRow[0]); // 假设患者编号在第0列
                Ids.append(dataRow[1]);

            }
        }
    }
}

void pinf::setUserData(const QVector<QVector<QString>> &data)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableViewUser_2->model());
    if (model) {
        model->clear();  // 清空现有数据
        model->setHorizontalHeaderLabels({
            "患者编号", "患者姓名", "患者账号", "患者性别", "患者年龄",
            "患者预约日期", "患者信息资料", "诊断结果"
        });

        int rowCount = data.size();
        int atrow=0;
        for (int row = 0; row < rowCount; ++row) {
            const QVector<QString> &dataRow = data[row];
            if (dataRow.size() == 9 && !dataRow[8].isEmpty()) {  // 诊断结果不为空
                atrow++;
            }
        }
        model->setRowCount(atrow);  // 设置行数
                                                       int a=0;
        for (int row = 0; row < rowCount; ++row) {
            const QVector<QString> &dataRow = data[row];
            if (dataRow.size() == 9 && !dataRow[8].isEmpty()) {
                // 诊断结果不为空
                for (int col = 1; col < dataRow.size(); ++col) {
                    model->setItem(a, col, new QStandardItem(dataRow[col]));
                }
                a++;
            }
        }
    }
}

void pinf::setGoodsData(const QVector<QVector<QString>> &data)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableViewGoods_2->model());
    if (model) {
        model->clear();  // 清空现有数据
        model->setHorizontalHeaderLabels({
            "患者编号", "患者姓名", "患者账号", "患者性别", "患者年龄",
            "患者预约日期", "患者信息资料", "诊断结果", "处方"
        });

        int rowCount = data.size();
        int arow=0;
        for (int row = 0; row < rowCount; ++row) {
            const QVector<QString> &dataRow = data[row];
            if (dataRow.size() == 10 && !dataRow[9].isEmpty()) {  // 处方不为空
                arow++;
            }
        }
        model->setRowCount(arow);  // 设置行数
int a=0;
        for (int row = 0; row < rowCount; ++row) {
            const QVector<QString> &dataRow = data[row];
            if (dataRow.size() == 10 && !dataRow[9].isEmpty()) {  // 处方不为空
                for (int col = 1; col < dataRow.size(); ++col) {
                    model->setItem(a, col, new QStandardItem(dataRow[col]));
                }












                a++;
            }
        }
    }
}

void pinf::setStatisticsData(const QVector<QVector<QString>> &data)
{
    QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableViewStatistics_2->model());
    if (model) {
        model->clear();  // 清空现有数据
        model->setHorizontalHeaderLabels({
            "患者编号", "患者姓名", "病房号", "病床号", "住院日期"
        });

        int rowCount = data.size();
        model->setRowCount(rowCount);  // 设置行数

        for (int row = 0; row < rowCount; ++row) {
            const QVector<QString> &dataRow = data[row];
            if (dataRow.size() == 5 && !dataRow[2].isEmpty()) {  // 病房号不为空
                for (int col = 0; col < dataRow.size(); ++col) {
                    model->setItem(row, col, new QStandardItem(dataRow[col]));
                }
            }
        }
    }
}

void pinf::onButtonClicked(const QModelIndex &index)
{
    QString patientId = patientIds.at(index.row());
    QString patinridid=Ids.at(index.row());
    UserMgr::GetInstance()->setpaintIdp(patinridid);
    UserMgr::GetInstance()->setguahaoidEdit(patientId);
    if (windowp) {
        QString result;
        int idValue = patientId.toInt();  // 如果 patientId 是 QVariant 并且代表一个整数
        QString idStr = QString::number(idValue);
            QVector<QVector<QString>> data = UserMgr::GetInstance()->getData();


            for (const QVector<QString>& row : data) {
                if (!row.isEmpty() && row[0] == idStr) {
                    // 比较第一个元素（userid）是否等于给定的id

                    QString username = row[2];
                    QString useremail = row[3];
                    QString usersex = row[4];
                    QString userage = row[5];
                    QString userorderdata = row[6];
                    QString userinfo = row[7];

                    // 将提取到的数据拼接成一个结果字符串，可以根据需求调整格式
                    result = "name: " + username + "\n" +
                             "accounts: " + useremail + "\n" +
                             "departments" + usersex + "\n" +
                             "phones" + userage + "\n" +
                             "times" + userorderdata + "\n" +
                             "Info: " + userinfo+"id"+patientId;
                    break;  // 找到匹配的数据后，跳出循环
                }
            }







        emit UserMgr::GetInstance()->sig_to_paint_info_detail(result);
        this->hide();
        windowp->show();
    }
}

pinf::~pinf()
{
    delete ui;
}

void pinf::on_pushButton_clicked()
{
    // emit goback();
    this->hide();
    // MainWindow *mmMainWindow = new MainWindow();
    // mmMainWindow->show();
}

void pinf::on_tableViewRecordation_2_doubleClicked(const QModelIndex &index)
{
    if (index.column() == 0)
    {

        this->hide();
        windowp->show();
    }
}

void pinf::on_tabWidget_tabBarClicked(int index)
{
    if(index == 0) {
        setRecordationData(UserMgr::GetInstance()->getData());
    }
    else if(index == 1) {
       setUserData(UserMgr::GetInstance()->getMdata());
    }
    else if(index == 2) {

        setGoodsData(UserMgr::GetInstance()->getWdata());
    }
    else if(index == 3) {
        setStatisticsData(UserMgr::GetInstance()->gethdata());
    }
}










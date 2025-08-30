#include "livewindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QStandardItemModel>

LiveWindow::LiveWindow() {
    // 设置窗口初始大小
    resize(600, 400);

    // 创建并设置布局
    QVBoxLayout *layout = new QVBoxLayout;  // 设置住院窗口的布局

    // 创建标题标签
    QLabel *label = new QLabel("住院");
    label->setStyleSheet("font-size: 40px; font-weight: bold;");  // 设置标签样式
    layout->addWidget(label);  // 将标签添加到布局中
    layout->addStretch();  // 将顶部标签推至顶部

    // 创建 QTableView 对象
    tableView = new QTableView;

    // 创建 QStandardItemModel 对象
    model = new QStandardItemModel;
    tableView->setModel(model);

    // 设置表头的居中对齐
    QHeaderView *header = tableView->horizontalHeader();
    header->setDefaultAlignment(Qt::AlignCenter);
    header->setSectionResizeMode(QHeaderView::Stretch); // Set columns to stretch and fill the view

    // 设置 QTableView 的行高以展示更多数据
    tableView->verticalHeader()->setDefaultSectionSize(20); // 设置行高

    // 创建分页控件
    QHBoxLayout *pagingLayout = new QHBoxLayout;
    pageSpinBox = new QSpinBox;
    pageSpinBox->setRange(1, 1); // 页码从1开始
    pageSpinBox->setPrefix("页码: ");
    pageSpinBox->setAlignment(Qt::AlignCenter);

    QPushButton *prevButton = new QPushButton("上一页");
    QPushButton *nextButton = new QPushButton("下一页");

    pagingLayout->addWidget(prevButton);
    pagingLayout->addWidget(pageSpinBox);
    pagingLayout->addWidget(nextButton);

    layout->addWidget(tableView);
    layout->addLayout(pagingLayout);

    // 连接信号槽
    connect(prevButton, &QPushButton::clicked, this, &LiveWindow::previousPage);
    connect(nextButton, &QPushButton::clicked, this, &LiveWindow::nextPage);
    connect(pageSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &LiveWindow::updateTableData);

    // 设置窗口的布局
    setLayout(layout);

    // 初始化表格数据
    initializeData();
    updateTableData(1); // 显示第一页
}

void LiveWindow::initializeData() {
    // 设置表头标签
    model->setHorizontalHeaderLabels({"入院日期", "病房号", "病床号", "出院日期", "主治医生"});

    // 添加虚拟数据
    QVector<QStringList> virtualData;
    for (int i = 0; i < 100; ++i) { // 100条虚拟记录
        QStringList row;
        row << QString("入院日期 %1").arg(i)
            << QString("病房号 %1").arg(i)
            << QString("病床号 %1").arg(i)
            << QString("出院日期 %1").arg(i)
            << QString("主治医生 %1").arg(i);
        virtualData.append(row);
    }

    // 保存数据用于分页
    allData = virtualData;

    // 设置总页数
    int totalPages = (allData.size() + 9) / 10; // 每页10条数据
    pageSpinBox->setMaximum(totalPages);
}

void LiveWindow::updateTableData(int page) {
    // 清空当前数据
    model->removeRows(0, model->rowCount());

    // 计算当前页的数据范围
    int startRow = (page - 1) * 10;
    int endRow = qMin(startRow + 10, allData.size());

    // 填充当前页的数据
    for (int i = startRow; i < endRow; ++i) {
        QList<QStandardItem*> rowItems;
        for (const QString &data : allData[i]) {
            QStandardItem *item = new QStandardItem(data);
            rowItems << item;
        }
        model->appendRow(rowItems);
    }
}

void LiveWindow::previousPage() {
    int currentPage = pageSpinBox->value();
    if (currentPage > 1) {
        pageSpinBox->setValue(currentPage - 1);
    }
}

void LiveWindow::nextPage() {
    int currentPage = pageSpinBox->value();
    int totalPages = pageSpinBox->maximum();
    if (currentPage < totalPages) {
        pageSpinBox->setValue(currentPage + 1);
    }
}

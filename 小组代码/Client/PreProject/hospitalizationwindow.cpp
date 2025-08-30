#include "hospitalizationwindow.h"
#include "ui_hospitalizationwindow.h"
#include "usermgr.h"

HospitalizationWindow::HospitalizationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HospitalizationWindow)
{
    ui->setupUi(this);

// //请在此处填写initializeVirtualData();————————————注意！！！————————————————

    int ii=UserMgr::GetInstance()->getId();

    QVector<QVector<QString>> hospitalizationData = UserMgr::GetInstance()->getHospitalizationDataByUid(UserMgr::GetInstance()->getUid());

        int num = hospitalizationData.size();
        QString* indate = new QString[num];
        QString* roomnum = new QString[num];
        QString* bednum = new QString[num];
        QString* yourdoc = new QString[num];

        for (int i = 0; i < num; ++i) {
            indate[i] = hospitalizationData[i][5];    // admission_data 列
            roomnum[i] = hospitalizationData[i][7];   // roomnum 列
            bednum[i] = hospitalizationData[i][4];    // bed_number 列
            yourdoc[i] = hospitalizationData[i][6];   // doctorname 列
        }

        // 调用 initializeVirtualData 方法
 // 假设你有一个 HospitalizationWindow 实例
        this->initializeVirtualData(num, indate, roomnum, bednum, yourdoc);

        // 清理动态分配的内存
        delete[] indate;
        delete[] roomnum;
        delete[] bednum;
        delete[] yourdoc;
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
           tableView->verticalHeader()->setDefaultSectionSize(60); // 设置行高

           // 创建标题文本部件
           QLabel *titleLabel = new QLabel("住院信息");
           titleLabel->setAlignment(Qt::AlignCenter);
           titleLabel->setStyleSheet("font-size: 40px; font-weight: bold;"); // 设置字号和加粗

           // 创建翻页按钮部件
           QWidget *paginationWidget = new QWidget;
           QHBoxLayout *paginationLayout = new QHBoxLayout(paginationWidget);

           // 创建翻页按钮
           prevButton = new QPushButton("上一页");
           nextButton = new QPushButton("下一页");
           paginationLayout->addWidget(prevButton);
           paginationLayout->addWidget(nextButton);

           // 确保按钮均匀分布
           paginationLayout->setStretch(0, 1);
           paginationLayout->setStretch(1, 1);

           // 设置翻页按钮的布局
           paginationWidget->setLayout(paginationLayout);


           // 创建主布局并添加 QTableView、标题、翻页按钮和底部按钮部件
           QVBoxLayout *mainLayout = new QVBoxLayout(this);

           // 添加标题文本
           mainLayout->addWidget(titleLabel);

           // 将 QTableView 添加到布局
           mainLayout->addWidget(tableView);

           // 将翻页按钮部件添加到布局
           mainLayout->addWidget(paginationWidget);

           // 将底部按钮部件添加到布局
           //mainLayout->addWidget(buttonWidget);

           // 设置中央部件的布局
           this->setLayout(mainLayout);

           // 设置主窗口的初始大小
           resize(1000, 800); // 设置窗口大小

           // 设置界面背景颜色
           setStyleSheet("background-color: #ADD8E6;"); // 设置背景颜色为浅蓝色

           // 设置 QTableView 的样式表
           tableView->setStyleSheet(
               "QTableView {"
               "   background-color: white;" // 表格背景颜色为白色
               "}"
               "QHeaderView::section {"
               "   background-color: white;" // 表头背景颜色为深蓝色
               "   color: black;" // 表头文字颜色为白色
               "   padding: 4px;"
               "}"
               "QTableCornerButton::section {"
               "   background-color: white;" // 表格角的背景颜色为深蓝色
               "}"
               "QTableView QTableCornerButton::section {"
               "   background-color: white;" // 表格角的背景颜色为深蓝色
               "}"
               "QTableView::item {"
               "   background-color: white;" // 单元格背景颜色为白色
               "}"
           );

           // 初始化翻页
           currentPage = 0;
           rowsPerPage = 10;
           totalRows = virtualData.size();
           loadPage(currentPage);

           // 连接翻页按钮的信号和槽
           connect(prevButton, &QPushButton::clicked, this, &HospitalizationWindow::previousPage);
           connect(nextButton, &QPushButton::clicked, this, &HospitalizationWindow::nextPage);

           updateNavigationButtons();

}

HospitalizationWindow::~HospitalizationWindow()
{
    delete ui;
}
void HospitalizationWindow::initializeVirtualData(int num,QString *indate,QString *roomnum,QString *bednum,QString *yourdoc) {
    // 创建虚拟数据
    for (int i = 0; i < num; ++i) { // 100条虚拟记录
        QStringList row;
        row << QString("%1").arg(indate[i])
            << QString("%1").arg(roomnum[i])
            << QString("%1").arg(bednum[i])
            << QString("%1").arg(yourdoc[i]);
        virtualData.append(row);
    }
}
void HospitalizationWindow::loadPage(int pageNumber) {
    model->clear();
    model->setHorizontalHeaderLabels({"入院日期", "病房号", "病床号",  "主治医生"});

    int offset = pageNumber * rowsPerPage;
    int end = std::min(offset + rowsPerPage, totalRows);

    for (int i = offset; i < end; ++i) {
        QList<QStandardItem*> rowItems;
        for (const QString &data : virtualData[i]) {
            QStandardItem *item = new QStandardItem(data);
            rowItems << item;
        }
        model->appendRow(rowItems);
    }

    updateNavigationButtons();
}
void HospitalizationWindow::updateNavigationButtons() {
    prevButton->setEnabled(currentPage > 0);
    nextButton->setEnabled((currentPage + 1) * rowsPerPage < totalRows);
}

void HospitalizationWindow::previousPage() {
    if (currentPage > 0) {
        --currentPage;
        loadPage(currentPage);
    }
}

void HospitalizationWindow::nextPage() {
    if ((currentPage + 1) * rowsPerPage < totalRows) {
        ++currentPage;
        loadPage(currentPage);
    }
}


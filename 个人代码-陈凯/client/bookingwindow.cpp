#include "bookingwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QHeaderView>

BookingWindow::BookingWindow(QWidget *parent) : QWidget(parent) {
    resize(600, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    bookingButton = new QPushButton("预约");
    myInfoButton = new QPushButton("我的");

    connect(bookingButton, &QPushButton::clicked, this, &BookingWindow::showDepartmentWidget);
    connect(myInfoButton, &QPushButton::clicked, this, &BookingWindow::showMyInfoWidget);

    buttonLayout->addWidget(bookingButton);
    buttonLayout->addWidget(myInfoButton);

    mainLayout->addLayout(buttonLayout);

    stackedWidget = new QStackedWidget;

    // 科室选择界面
    departmentWidget = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->setSpacing(10);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    QStringList departments = {"儿科", "妇产科", "外科", "内科", "皮肤科"};
    for (int i = 0; i < departments.size(); ++i) {
        QPushButton *button = new QPushButton(departments[i]);
        button->setFixedWidth(width() * 0.20);
        connect(button, &QPushButton::clicked, this, [this] {
            // Handle department selection
            showDepartmentWidget();
        });
        leftLayout->addWidget(button);
        departmentButtons[i] = button;
    }

    departmentWidget->setLayout(leftLayout);
    stackedWidget->addWidget(departmentWidget);

    // 个人信息界面
    myInfoWidget = new QWidget;
    QVBoxLayout *myInfoLayout = new QVBoxLayout;
    myInfoLayout->setContentsMargins(10, 10, 10, 10);

    QTableView *infoTableView = new QTableView;
    QStandardItemModel *infoModel = new QStandardItemModel(10, 1, this);
    infoModel->setHorizontalHeaderLabels({"信息"});

    for (int row = 0; row < 10; ++row) {
        QStandardItem *item = new QStandardItem(QString("信息 %1").arg(row));
        infoModel->setItem(row, 0, item);
    }

    infoTableView->setModel(infoModel);
    myInfoLayout->addWidget(infoTableView);

    myInfoWidget->setLayout(myInfoLayout);
    stackedWidget->addWidget(myInfoWidget);

    mainLayout->addWidget(stackedWidget);

    setLayout(mainLayout);

    // Initialize with Booking view
    showDepartmentWidget();
}

void BookingWindow::showDepartmentWidget() {
    stackedWidget->setCurrentIndex(0);
    bookingButton->setStyleSheet("background-color: gray;");
    myInfoButton->setStyleSheet("background-color: lightgray;");
}

void BookingWindow::showMyInfoWidget() {
    stackedWidget->setCurrentIndex(1);
    bookingButton->setStyleSheet("background-color: lightgray;");
    myInfoButton->setStyleSheet("background-color: gray;");
}

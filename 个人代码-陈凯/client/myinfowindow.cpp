#include "myinfowindow.h"
#include "bookingwindow.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QVBoxLayout>
#include <QPushButton>

MyInfoWindow::MyInfoWindow(QWidget *parent) : QWidget(parent) {
    resize(600, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    infoTableView = new QTableView;
    infoModel = new QStandardItemModel(10, 1, this);  // 10行1列
    infoModel->setHorizontalHeaderLabels({"信息"});

    initializeTable();

    infoTableView->setModel(infoModel);
    mainLayout->addWidget(infoTableView);

    // Add buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *bookingButton = new QPushButton("预约");
    QPushButton *myInfoButton = new QPushButton("我的");

    connect(bookingButton, &QPushButton::clicked, this, &MyInfoWindow::showBookingWindow);
    connect(myInfoButton, &QPushButton::clicked, this, &MyInfoWindow::showMyInfoWindow);

    buttonLayout->addWidget(bookingButton);
    buttonLayout->addWidget(myInfoButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void MyInfoWindow::initializeTable() {
    for (int row = 0; row < 10; ++row) {
        QStandardItem *item = new QStandardItem(QString("信息 %1").arg(row));
        infoModel->setItem(row, 0, item);
    }
}

void MyInfoWindow::showBookingWindow() {
    // Check if the parent is a valid pointer and cast it to a BookingWindow
    QWidget *parentWidget = this->parentWidget();
    if (parentWidget) {
        BookingWindow *bookingWindow = new BookingWindow(parentWidget);
        bookingWindow->show();
        this->close();  // Close the current window
    }
}

void MyInfoWindow::showMyInfoWindow() {
    // This is already the "我的" window, so no action needed here.
}

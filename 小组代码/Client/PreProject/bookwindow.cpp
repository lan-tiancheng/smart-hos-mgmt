#include "bookwindow.h"
#include "ui_bookwindow.h"
#include <QStyle>

BookWindow::BookWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookWindow)
{
    ui->setupUi(this);
    QListWidgetItem *child= new QListWidgetItem("儿科");
    QListWidgetItem *woman= new QListWidgetItem("妇产科");
    QListWidgetItem *out= new QListWidgetItem("外科");
    QListWidgetItem *inside= new QListWidgetItem("内科");
    QListWidgetItem *skin= new QListWidgetItem("皮肤科");
    ui->listWidget->addItem(child);
    ui->listWidget->addItem(woman);
    ui->listWidget->addItem(out);
    ui->listWidget->addItem(inside);
    ui->listWidget->addItem(skin);
    ui->listWidget->setSpacing(10);

    child->setTextAlignment(Qt::AlignCenter);
    child->setForeground(QBrush(Qt::white));  // 文本颜色
    child->setFont(QFont("Arial", 20));  // 文本字体和大小
    woman->setTextAlignment(Qt::AlignCenter);
    woman->setForeground(QBrush(Qt::white));  // 文本颜色
    woman->setFont(QFont("Arial", 20));  // 文本字体和大小
    out->setTextAlignment(Qt::AlignCenter);
    out->setForeground(QBrush(Qt::white));  // 文本颜色
    out->setFont(QFont("Arial", 20));  // 文本字体和大小
    inside->setTextAlignment(Qt::AlignCenter);
    inside->setForeground(QBrush(Qt::white));  // 文本颜色
    inside->setFont(QFont("Arial", 20));  // 文本字体和大小
    skin->setTextAlignment(Qt::AlignCenter);
    skin->setForeground(QBrush(Qt::white));  // 文本颜色
    skin->setFont(QFont("Arial", 20));  // 文本字体和大小
    /*ui->listWidget->setStyleSheet(
                "QListWidget {"
                "background-color: #f0f0f0;"
                "border: 1px solid #d4d4d4;"
                "padding: 1px;"
                                          "}"
                "QListWidgetItem { "
                "min-height: 100px; min-width: 200px; "
                "padding: 4px;"
                "border: 1px solid transparent;"
                "margin: 1px;"
                                          "}"
                                          "QListWidgetItem {"
                                                             "display: table-cell;"
                                                             "vertical-align: middle;"
                                                             "text-align: center;"
                                                             "padding: 10px;"
                                                             "}");*/
    connect(ui->listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onItemClicked(QListWidgetItem*)));

    ui->stackedWidget->addWidget(&childwd);
    ui->stackedWidget->addWidget(&womanwd);
    ui->stackedWidget->addWidget(&outwd);
    ui->stackedWidget->addWidget(&insidewd);
    ui->stackedWidget->addWidget(&skinwd);
}


BookWindow::~BookWindow()
{
    delete ui;
}

void BookWindow::onItemClicked(QListWidgetItem* item){
    if(item->text()=="儿科"){
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(item->text()=="妇产科"){
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(item->text()=="外科"){
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if(item->text()=="内科"){
        ui->stackedWidget->setCurrentIndex(3);
    }
    else if(item->text()=="皮肤科"){
        ui->stackedWidget->setCurrentIndex(4);
    }
}

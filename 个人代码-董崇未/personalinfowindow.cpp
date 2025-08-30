#include "personalinfowindow.h"
#include "ui_personalinfowindow.h"

PersonalInfoWindow::PersonalInfoWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalInfoWindow)
{
    ui->setupUi(this);
    //已经废弃的页面
}

PersonalInfoWindow::~PersonalInfoWindow()
{
    delete ui;
}

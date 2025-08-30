#include "misearchsonwd.h"
#include "ui_misearchsonwd.h"

MIsearchSonWd::MIsearchSonWd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MIsearchSonWd)
{
    ui->setupUi(this);
    this->setFixedSize(1200, 800);
    this->setStyleSheet("background-color:white;");
    this->setWindowTitle("医药搜索");
}

MIsearchSonWd::~MIsearchSonWd()
{
    delete ui;
}

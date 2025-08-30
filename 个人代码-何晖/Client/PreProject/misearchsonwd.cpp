#include "misearchsonwd.h"
#include "ui_misearchsonwd.h"

MIsearchSonWd::MIsearchSonWd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MIsearchSonWd)
{
    ui->setupUi(this);
}

MIsearchSonWd::~MIsearchSonWd()
{
    delete ui;
}

#include "httprequest.h"
#include "ui_httprequest.h"

httprequest::httprequest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::httprequest)
{
    ui->setupUi(this);
}

httprequest::~httprequest()
{
    delete ui;
}

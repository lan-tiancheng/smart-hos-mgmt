#include "pmainwindowhome.h"
#include "ui_pmainwindowhome.h"

PMainWindowHome::PMainWindowHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PMainWindowHome)
{
    ui->setupUi(this);
    //已经废弃的页面
}

PMainWindowHome::~PMainWindowHome()
{
    delete ui;
}

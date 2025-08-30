#include "getsound.h"
#include "ui_getsound.h"

getsound::getsound(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::getsound)
{
    ui->setupUi(this);
}

getsound::~getsound()
{
    delete ui;
}

#include "pbd.h"
#include "ui_pbd.h"

pbd::pbd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pbd)
{
    ui->setupUi(this);
}

pbd::~pbd()
{
    delete ui;
}

void pbd::on_pushButton_return_clicked()
{
    emit goback();
}


#include "information.h"
#include "ui_information.h"

information::information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::information)
{
    ui->setupUi(this);
}

information::~information()
{
    delete ui;
}

void information::on_pushButton_clicked()
{
    emit goback();
}


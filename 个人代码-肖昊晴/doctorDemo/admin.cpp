#include "admin.h"
#include "ui_book.h"

book::book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::book)
{
    ui->setupUi(this);
}

book::~book()
{
    delete ui;
}

void book::on_pushButton_clicked()
{
    emit goback();
}

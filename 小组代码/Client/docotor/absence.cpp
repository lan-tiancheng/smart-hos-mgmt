#include "absence.h"
#include "ui_absence.h"

Absence::Absence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Absence)
{
    ui->setupUi(this);
}

Absence::~Absence()
{
    delete ui;
}

void Absence::on_okButton_clicked()
{
    accept();  // Close the dialog
}

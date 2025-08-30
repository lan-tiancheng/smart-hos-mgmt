#include "medicalcaseswd.h"
#include "ui_medicalcaseswd.h"

MedicalcasesWd::MedicalcasesWd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MedicalcasesWd)
{
    ui->setupUi(this);
    ui->textBrowser->setText("病例");
    ui->textBrowser->append("患者命不久已");
}

MedicalcasesWd::~MedicalcasesWd()
{
    delete ui;
}

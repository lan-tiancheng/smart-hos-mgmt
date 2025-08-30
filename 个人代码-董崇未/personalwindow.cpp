#include "personalwindow.h"
#include "ui_personalwindow.h"

PersonalWindow::PersonalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonalWindow)
{
    ui->setupUi(this);
    //已经废弃的页面
}

PersonalWindow::~PersonalWindow()
{
    delete ui;
}

void PersonalWindow::on_personalinfoBtn_clicked()
{
    PersonalInfoWindow * plifWd=new PersonalInfoWindow;
    plifWd->show();
}


void PersonalWindow::on_medicalcasesBtn_clicked()
{
    MedicalcasesWd *mcWd=new MedicalcasesWd;
    mcWd->show();
}


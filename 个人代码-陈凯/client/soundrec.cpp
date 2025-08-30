#include "soundrec.h"
#include "ui_soundrec.h"

soundrec::soundrec(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::soundrec)
{
    ui->setupUi(this);
}

soundrec::~soundrec()
{
    delete ui;
}

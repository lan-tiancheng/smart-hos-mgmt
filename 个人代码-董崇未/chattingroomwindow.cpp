#include "chattingroomwindow.h"
#include "ui_chattingroomwindow.h"

ChattingroomWindow::ChattingroomWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChattingroomWindow)
{
    ui->setupUi(this);
}

ChattingroomWindow::~ChattingroomWindow()
{
    delete ui;
}

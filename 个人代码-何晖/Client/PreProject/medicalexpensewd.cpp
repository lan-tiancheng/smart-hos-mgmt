#include "medicalexpensewd.h"
#include "ui_medicalexpensewd.h"
#include <QPainter>

MedicalExpenseWd::MedicalExpenseWd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MedicalExpenseWd)
{
    ui->setupUi(this);
    this->setWindowTitle("医疗缴费");
}

MedicalExpenseWd::~MedicalExpenseWd()
{
    delete ui;
}
void MedicalExpenseWd::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap backgroundPixmap(":/res/medicalexpense.jpg"); // 使用资源文件中的背景图片
    painter.drawPixmap(0, 0, width(), height(), backgroundPixmap);
    QWidget::paintEvent(event); // 调用基类的 paintEvent 以确保正常绘制其他内容
}

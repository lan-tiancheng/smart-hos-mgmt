#include "widget.h"
#include "ui_audiowd.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),ui(new Ui::AudioWd)
{
    ui->setupUi(this);

    ui->startPtn->setEnabled(true);     //Start按钮初始化可用
    ui->stopPtn->setEnabled(false);     //Stop按钮初始化不可用
}

Widget::~Widget()
{
    delete ui;
}

//点击Start按钮后触发的槽函数
void Widget::on_startPtn_clicked()
{
    QString filepath = ui->filepath->text();    //获取用户输入地址

    /* 判断用户是否输入地址 */
    if(filepath == "")
    {
        QMessageBox::information(NULL, "information", "Please input the filepath to save!");
        return;
    }

    /* 点击Start后禁用Start，开放Stop按钮 */
    ui->startPtn->setEnabled(false);
    ui->stopPtn->setEnabled(true);

    myAudioCapture.startCapture(filepath);  //开始录音
}

//点击Stop按钮后触发的槽函数
void Widget::on_stopPtn_clicked()
{
    /* 点击Stop后禁用Stop，开放Start按钮 */
    ui->startPtn->setEnabled(true);
    ui->stopPtn->setEnabled(false);

    myAudioCapture.stopCapture();           //结束录音
}

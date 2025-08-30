#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QTextBlock>
#include<QTimer>     // 定时器
#include<QDateTime>  // 获取当前时间
#include<QDebug>
#include<QString>
#include<QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//试调自适应界面---未成功
//    m_Widget = this->findChildren<QMainWindow>(QString(),Qt::FindDirectChildrenOnly);
//    foreach(auto widget, m_Widget)
//        {
//            m_WidgetRect.insertMulti(widget, QRect(widget->x(), widget->y(), widget->width(), widget->height()));
//        }


    this->window = new pinf;
    connect(window,&pinf::goback,this,[=]()
    {
        window->close();
        this->show();
    });

    this->window1 = new information;
    connect(window1,&information::goback,this,[=]()
    {
        window1->close();
        this->show();
    });

    setWindowTitle("医生端");
    QPixmap pixmap;
    pixmap.load(":/images/pictures/患者信息-copy x64.png");
    ui->label->setPixmap(pixmap);

    QPixmap pixmap1;
    pixmap1.load(":/images/pictures/考勤管理  x64.png");
    ui->label_2->setPixmap(pixmap1);

    QPixmap pixmap2;
    pixmap2.load(":/images/pictures/个人信息x64.png");
    ui->label_5->setPixmap(pixmap2);

    QPixmap pixmap3;
    pixmap3.load(":/pictures/jiankangzhishu_x64.png");
    ui->label_20->setPixmap(pixmap3);

    QPixmap pixmap4;
    pixmap4.load(":/pictures/远程医疗x64.png");
    ui->label_21->setPixmap(pixmap4);

    QPixmap pixmap5;
    pixmap5.load(":/pictures/4-聊天室x64.png");
    ui->label_22->setPixmap(pixmap5);

    QPixmap pixmap6;
    pixmap6.load(":/pictures/导航x64.png");
    ui->label_23->setPixmap(pixmap6);


    //实时打卡时钟
    QTimer *  timer;
    timer = new QTimer;
    connect(timer,&QTimer::timeout,this,&MainWindow::showTime);  // 信号连接 每一秒执行一次槽函数
    timer->start(1000);

//主界面和各个界面间转换
//     QObject::connect(ui->PI,&QPushButton::clicked,
//                     [=]()
//    {
//          ui->stackedWidget->setCurrentIndex(0);
//    }
//    );
     QObject::connect(ui->WA,&QPushButton::clicked,
                     [=]()
    {
          ui->stackedWidget->setCurrentIndex(1);
    }
    );
//     QObject::connect(ui->INF,&QPushButton::clicked,
//                     [=]()
//    {
//          ui->stackedWidget->setCurrentIndex(2);
//    }
//    );
//     QObject::connect(ui->return_1,&QPushButton::clicked,
//                     [=]()
//    {
//          ui->stackedWidget->setCurrentIndex(3);
//    }
//    );
     QObject::connect(ui->return_2,&QPushButton::clicked,
                     [=]()
    {
          ui->stackedWidget->setCurrentIndex(3);
    }
    );
//     QObject::connect(ui->return_3,&QPushButton::clicked,
//                     [=]()
//    {
//          ui->stackedWidget->setCurrentIndex(3);
//    }
//    );


     /*考勤页面*/
     QObject::connect(ui->pushButton,&QPushButton::clicked,
                     [=]()
    {
          ui->stackedWidget_2->setCurrentIndex(0);
    }
    );
     QObject::connect(ui->pushButton_2,&QPushButton::clicked,
                     [=]()
    {
          ui->stackedWidget_2->setCurrentIndex(1);
    }
    );
     QObject::connect(ui->pushButton_3,&QPushButton::clicked,
                     [=]()
    {
          ui->stackedWidget_2->setCurrentIndex(2);
    }
    );

     //手机号限制输入
     ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[0-9]{11}")));

     //计数输入框
     connect(ui->textEdit, &QTextEdit::textChanged,
                 this, &MainWindow::slot_handleInput);

     //状态栏
     QStatusBar *statusbar =statusBar();
     statusbar->addWidget(new QLabel("进行医务工作，切勿过度劳累！",this));

     //销假界面表格设置
     ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


     //销假请求的功能如何实现
     //？？？？？
     //？？？？？
     //？？？？？

}

MainWindow::~MainWindow()
{
    delete ui;
}


//打卡时钟
void MainWindow::showTime()
{
    QString string;
    QDateTime Timedata = QDateTime::currentDateTime();   //  获取当前时间
    string = Timedata.toString("yyyy - MM - dd  hh : mm");   //  设置显示格式
    ui->label_time->setText(string);  // 设置标签内容
}




//限制输入文本框相关
QString MainWindow::content()
{
    return ui->textEdit->document()->toPlainText();
}

void MainWindow::setMaxWordNum(const int maxNum)
{
    m_maxWordNum = maxNum;
    ui->labelMaxNum->setNum(m_maxWordNum);
}
void MainWindow::setTitle(const QString &title)
{
    ui->labelTitle->setText(title);
}

void MainWindow::setContent(const QString &content)
{
    ui->textEdit->setText(content);

    QTextDocument* doc = ui->textEdit->document();

    for(QTextBlock it = doc->begin(); it != doc->end(); it = it.next())
    {
        QTextCursor textCursor(it);
        QTextBlockFormat textBlockFormat = it.blockFormat();
        textBlockFormat.setLineHeight(24,QTextBlockFormat::FixedHeight);  //set line height
        textCursor.setBlockFormat(textBlockFormat);
        ui->textEdit->setTextCursor(textCursor);
    }
    // 将光标移回起始点
    ui->textEdit->setTextCursor(QTextCursor(doc->begin()));
}

void MainWindow::slot_handleInput()
{
    setTitle("字数限制");
    setMaxWordNum(60);
    auto textEdit = static_cast<QTextEdit*>(sender());
    int currentNum = textEdit->toPlainText().length();
    // 判断是不是超出了字数限制
    if (currentNum > m_maxWordNum) {
        QString text = textEdit->toPlainText();
        text = text.mid(0, m_maxWordNum);
        int position = textEdit->textCursor().position();

        textEdit->setText(text);
        QTextCursor cursor = textEdit->textCursor();
        if (position > m_maxWordNum) {
            // 如果当前输入位置为末尾的话，就直接跳到最后一个字符。
            position = m_maxWordNum;
        }
        cursor.setPosition(position);
        textEdit->setTextCursor(cursor);
        currentNum = m_maxWordNum;
    }

    ui->labelCurrentNum->setNum(currentNum);
}

/*完成页面切换功能的代码*/
//void MainWindow::switchPage(){
//    QPushButton *button = qobject_cast<QPushButton*>(sender());
//    if(button==ui->PI)
//        ui->stackedWidget->setCurrentIndex(0);
//    else if(button==ui->WA)
//        ui->stackedWidget->setCurrentIndex(1);
//    else if(button==ui->return_1||button==ui->return_2)
//        ui->stackedWidget->setCurrentIndex(2);

//    int i = 0;
//    ui->stackedWidget->widget(i);
//}
//void MainWindow::on_PI_clicked()
//{
//    switchPage();
//}

//void MainWindow::on_WA_clicked()
//{
//    switchPage();
//}

//void MainWindow::on_return_1_clicked()
//{
//    switchPage();
//}

//void MainWindow::on_return_2_clicked()
//{
//    switchPage();
//}





//失败失败失败
//void MainWindow::on_buttonBox_rejected()
//{

//    QMessageBox::question(this, tr("Hmmm..."),
//    tr("你确定取消请假申请吗？"));
//}
//void MainWindow::on_buttonBox_accepted()
//{
//    QMessageBox::information(this, tr("请假"),
//    tr("请假申请提交成功"));
//}



//请假确定和取消按钮
void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::information(this, tr("请假"),
    tr("请假申请提交成功！"));
}
void MainWindow::on_pushButton_5_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this,
    tr("Question"), tr("你确定取消请假申请吗?"),
    QMessageBox::Yes | QMessageBox::No,
    QMessageBox::Yes))
    {
    QMessageBox::information(this, tr("取消请假申请"),
    tr("取消成功!"));
    }
    else
    {
        QMessageBox::information(this, tr("请假申请"),
        tr("即将返回请假申请界面......"));
    }
}





//打卡按钮
void MainWindow::on_checkBox_clicked()
{
    bool status =ui->checkBox->isChecked();
        if(status == true)
        {
            QMessageBox::information(this, tr("考勤打卡"),
            tr("打卡成功！！！"));

        }
        else if(status == false)
        {
            QMessageBox::information(this, tr("考勤打卡"),
            tr("打卡已取消"));
        }
}


void MainWindow::on_PI_clicked()
{
    this->hide();
    window->show();
}


void MainWindow::on_INF_clicked()
{
    this->hide();
    window1->show();
}


//测试点击表格确定的某一列界面跳转
//void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
//{
//    if(item->column()==0)
//    {
//        ui->stackedWidget->setCurrentIndex(3);
//    }
//}
//void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
//{
//    if(index.column()==0)
//    {
//        ui->stackedWidget->setCurrentIndex(3);
//    }
//}


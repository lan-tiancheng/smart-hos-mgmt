#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "absence.h"
#include "pinf.h"
#include "information.h"
#include "tcpmgr.h"
#include "remainwindow.h"
#include "guidemainwindow.h"
#include "inchartx.h"
#include "widget.h"
#include "drawer.h"
#include <QMessageBox>
#include <QTextBlock>
#include <QDebug>
#include <QString>
#include <QTextCursor>
#include <QTextDocument>
#include <QRegExpValidator>
#include <QStatusBar>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QHeaderView>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load background image
    backgroundPixmap.load(":/images/pictures/主界面背景图.jpg");

    // Initialize secondary windows
    window = new pinf;
    connect(window, &pinf::goback, this, [=]()
    {
        window->close();
        this->show();
    });

    window1 = new information;
    connect(window1, &information::goback, this, [=]()
    {
        window1->close();
        this->show();
    });

    setWindowTitle("医生端");

    // Set pixmaps for labels
    QPixmap pixmap;
    pixmap.load(":/images/pictures/患者信息-copy x64.png");
    ui->label->setPixmap(pixmap);
    ui->label->installEventFilter(this);

    QPixmap pixmap1;
    pixmap1.load(":/images/pictures/考勤管理  x64.png");
    ui->label_2->setPixmap(pixmap1);
    ui->label_2->installEventFilter(this);  // Install event filter here

    QPixmap pixmap2;
    pixmap2.load(":/images/pictures/个人信息x64.png");
    ui->label_5->setPixmap(pixmap2);
    ui->label_5->installEventFilter(this);

    QPixmap pixmap3;
    pixmap3.load(":/images/pictures/jiankangzhishu_x64.png");
    ui->label_20->setPixmap(pixmap3);
    ui->label_20->installEventFilter(this);

    QPixmap pixmap4;
    pixmap4.load(":/images/pictures/远程医疗x64.png");
    ui->label_21->setPixmap(pixmap4);
    ui->label_21->installEventFilter(this);

    QPixmap pixmap5;
    pixmap5.load(":/images/pictures/4-聊天室x64.png");
    ui->label_22->setPixmap(pixmap5);
    ui->label_22->installEventFilter(this);

    QPixmap pixmap6;
    pixmap6.load(":/images/pictures/导航x64.png");
    ui->label_23->setPixmap(pixmap6);
    ui->label_23->installEventFilter(this);

    // Connect buttons to their respective actions
    connect(ui->WA, &QPushButton::clicked, [=]()
    {
        ui->stackedWidget->setCurrentIndex(1);
    });

    connect(ui->return_2, &QPushButton::clicked, [=]()
    {
        ui->stackedWidget->setCurrentIndex(3);
    });

    connect(ui->pushButton, &QPushButton::clicked, [=]()
    {
        ui->stackedWidget_2->setCurrentIndex(0);
    });

    connect(ui->pushButton_2, &QPushButton::clicked, [=]()
    {
        ui->stackedWidget_2->setCurrentIndex(1);
    });

    connect(ui->pushButton_3, &QPushButton::clicked, [=]()
    {
        ui->stackedWidget_2->setCurrentIndex(2);
    });

    // Set input validators
    ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[0-9]{11}")));

    // Connect text edit signal to handle input length
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::slot_handleInput);

    // Set up status bar
    QStatusBar *statusbar = statusBar();
    statusbar->addWidget(new QLabel("进行医务工作，切勿过度劳累！", this));

    // Set up table widget
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set up timer for real-time clock
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::showTime);
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), backgroundPixmap);
}

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

    QTextDocument *doc = ui->textEdit->document();
    for (QTextBlock it = doc->begin(); it != doc->end(); it = it.next())
    {
        QTextCursor textCursor(it);
        QTextBlockFormat textBlockFormat = it.blockFormat();
        textBlockFormat.setLineHeight(24, QTextBlockFormat::FixedHeight);
        textCursor.setBlockFormat(textBlockFormat);
        ui->textEdit->setTextCursor(textCursor);
    }
    ui->textEdit->setTextCursor(QTextCursor(doc->begin()));
}

void MainWindow::slot_handleInput()
{
    setTitle("字数限制");
    setMaxWordNum(60);
    auto textEdit = static_cast<QTextEdit *>(sender());
    int currentNum = textEdit->toPlainText().length();
    if (currentNum > m_maxWordNum)
    {
        QString text = textEdit->toPlainText();
        text = text.mid(0, m_maxWordNum);
        int position = textEdit->textCursor().position();

        textEdit->setText(text);
        QTextCursor cursor = textEdit->textCursor();
        if (position > m_maxWordNum)
        {
            position = m_maxWordNum;
        }
        cursor.setPosition(position);
        textEdit->setTextCursor(cursor);
        currentNum = m_maxWordNum;
    }

    ui->labelCurrentNum->setNum(currentNum);
}

void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::information(this, tr("请假"), tr("请假申请提交成功！"));
}

void MainWindow::on_pushButton_5_clicked()
{
    if (QMessageBox::Yes == QMessageBox::question(this, tr("Question"), tr("你确定取消请假申请吗?"),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
    {
        QMessageBox::information(this, tr("取消请假申请"), tr("取消成功!"));
    }
    else
    {
        QMessageBox::information(this, tr("请假申请"), tr("即将返回请假申请界面......"));
    }
}

void MainWindow::on_checkBox_clicked()
{
    bool status = ui->checkBox->isChecked();
    if (status)
    {
        QMessageBox::information(this, tr("考勤打卡"), tr("打卡成功！！！"));
    }
    else
    {
        QMessageBox::information(this, tr("考勤打卡"), tr("打卡已取消"));
    }
}

void MainWindow::on_PI_clicked()
{
//    window=new pinf;


//    window->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
//    //connect(_reg_dlg,&RegisterDialog::sigSwitchLogin,this,&hMainWindow::slotSwitchLogin);
//    setCentralWidget(window);
//    window->show();
//    this->hide();

    //emit sig_patient_mesg_need();
    QJsonObject jsonObj;
    jsonObj["uid"]=UserMgr::GetInstance()->getUid();
    qDebug()<<jsonObj["uid"].toInt();

    QJsonDocument doc(jsonObj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    //发送tcp请求给chat server
    emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_DOCTOR_CALL_PAINTINFO, jsonString);
    pinf *pinfWindow = new pinf(this);
    pinfWindow->show();
    emit sig_make_first_list();
}

void MainWindow::on_INF_clicked()
{
    information *informationWindow = new information(this);
    informationWindow->show();
}

void MainWindow::on_checkBox_1_stateChanged(int arg1)
{
    Absence *absenceWindow = new Absence(this);
    absenceWindow->show();
}

void MainWindow::showTime()
{
    QString string;
    QDateTime Timedata = QDateTime::currentDateTime();
    string = Timedata.toString("yyyy - MM - dd   hh : mm");
    ui->label_time->setText(string);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (obj == ui->label && mouseEvent->button() == Qt::LeftButton)
        {
            on_PI_clicked();  // Navigate to pinf
            return true;
        }
        if (obj == ui->label_5 && mouseEvent->button() == Qt::LeftButton)
        {
            on_INF_clicked();  // Navigate to information
            return true;
        }
        if (obj == ui->label_2 && mouseEvent->button() == Qt::LeftButton)
        {
            //QMessageBox::information(this, tr("考勤管理"), tr("考勤管理图标被点击了！"));
            // 这里可以添加跳转到考勤管理界面的代码
            ui->stackedWidget->setCurrentIndex(1);
            return true;
        }
        if (obj == ui->label_20 && mouseEvent->button() == Qt::LeftButton)
        {
            on_HC_clicked();  // Navigate to pinf
            return true;
        }
        if (obj == ui->label_21 && mouseEvent->button() == Qt::LeftButton)
        {
            on_YS_clicked();  // Navigate to pinf
            return true;
        }
        if (obj == ui->label_22 && mouseEvent->button() == Qt::LeftButton)
        {
            on_CR_clicked();  // Navigate to pinf
            return true;
        }
        if (obj == ui->label_23 && mouseEvent->button() == Qt::LeftButton)
        {
            on_NG_clicked();  // Navigate to pinf
            return true;
        }
    }
    return QMainWindow::eventFilter(obj, event);
}


void MainWindow::on_YS_clicked()
{
    reMainWindow *rereMainWindow = new reMainWindow(this);
    // this->hide();
    rereMainWindow->show();
}

void MainWindow::on_NG_clicked()
{
    guideMainWindow *guideguideMainWindow = new guideMainWindow(this);
    // this->hide();
    guideguideMainWindow->show();
}


void MainWindow::on_HC_clicked()
{
    InChartX *InchartxWindow = new InChartX(this);
    InchartxWindow->show();
}


void MainWindow::on_CR_clicked()
{
    Drawer *drawer = new Drawer(this);
    drawer->resize(250, 500);
    drawer->show();
}


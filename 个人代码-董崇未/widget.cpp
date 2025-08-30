#include "widget.h"
#include "ui_widget.h"
#include "server.h"
#include "client.h"
#include <QFileDialog>
#include <QDateTime>
#include <QString>

Widget::Widget(QWidget *parent,QString usrname) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->init();
    udpSocket = new QUdpSocket(this);               //创建udp套接字
    uName = usrname;
    port = 23232;                                   //端口默认为23232
    udpSocket->bind(port, QUdpSocket::ShareAddress
                    |QUdpSocket::ReuseAddressHint); //将udp套接字绑定到端口和地址上
    connect(udpSocket, SIGNAL(readyRead()), this,
            SLOT(processPendingDatagrams()));
    sndMsg(UsrEnter);

    srv = new server(this);
    connect(srv, SIGNAL(sndFileName(QString)), this, SLOT(getFileName(QString)));
    connect(ui->msgTextEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat))
            ,this, SLOT(curFmtChanged(QTextCharFormat)));
    connect(ui->sendBtn, SIGNAL(pressed()), this, SLOT(on_sendBtn_clicked()));
}

void Widget::init()
{
    ui->usrTblWidget->setSelectionMode(QAbstractItemView::
                                       SingleSelection); //只能单选
    ui->usrTblWidget->setSelectionBehavior(QAbstractItemView::
                                           SelectRows);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sndMsg(MsgType type, QString srvaddr)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    QString address = getIP();
    out << type << getUsr();        //向要发送的数据中写入信息类型type,用户名（使用getUsr()函数获取）
    switch (type)
    {
        case Msg :
        if (ui->msgTextEdit->toPlainText() == "")
        {
            QMessageBox::warning(0, "警告", "发送信息不能为空", QMessageBox::Ok);
            return;
        }
        out << address << getMsg();
        ui->msgBrowser->verticalScrollBar()->setValue(
                    ui->msgBrowser->verticalScrollBar()->maximum());
        case UsrEnter :
            out << address;
            break;
        case UsrLeft :
            break;
        case FileName :
        {
            int row = ui->usrTblWidget->currentRow();
            QString clntaddr = ui->usrTblWidget->item(row, 1)->text();
            out << address << clntaddr << fileName;
            break;
        }
        case Refuse :
        {
            out << srvaddr;
            break;
        }
    }
    udpSocket->writeDatagram(data, data.length(),
                             QHostAddress::Broadcast, port);        //使用writeDatagram函数进行udp广播
}

void Widget::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())                        //判断是否有可供读取的数据
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());          //获取当前可供读取的UDP报文大小
        udpSocket->readDatagram(datagram.data(), datagram.size());  //读取相应数据
        QDataStream in(&datagram, QIODevice::ReadOnly);
        int msgType;
        in >> msgType;
        QString usrName, ipAddr, msg;
        QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        switch(msgType)
        {
        case Msg:
            in >> usrName >> ipAddr >> msg;
            ui->msgBrowser->setTextColor(Qt::blue);
            ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 12));
            ui->msgBrowser->append("[" +usrName+"]"+ time);
            ui->msgBrowser->append(msg);
            break;
        case UsrEnter:
            in >> usrName >>ipAddr;
            usrEnter(usrName, ipAddr);
            break;
        case UsrLeft:
            in >> usrName;
            usrLeft(usrName, time);
            break;
        case FileName:
        {   in >>usrName >>ipAddr;
            QString clntAddr, fileName;
            in >> clntAddr >> fileName;
            hasPendingFile(usrName, ipAddr, clntAddr, fileName);
            break;
        }
        case Refuse:
        {
            in >> usrName;
            QString srvAddr;
            in >> srvAddr;
            QString ipAddr = getIP();
            if(ipAddr == srvAddr)
            {
                srv->refused();
            }
            break;
        }
        }
    }
}

void Widget::usrEnter(QString usrname, QString ipaddr)
{
    bool isEmpty = ui->usrTblWidget->findItems(usrname, Qt::MatchExactly).isEmpty();
    if(isEmpty)
    {
        QTableWidgetItem *usr = new QTableWidgetItem(usrname);
        QTableWidgetItem *ip = new QTableWidgetItem(ipaddr);
        ui->usrTblWidget->insertRow(0);
        ui->usrTblWidget->setItem(0, 0, usr);
        ui->usrTblWidget->setItem(0, 1, ip);
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
        ui->msgBrowser->append(tr("%1 在线！").arg(usrname));
        ui->usrNumLbl->setText(tr("在线人数：%1").arg(ui->usrTblWidget->rowCount()));
        sndMsg(UsrEnter);
    }
}

void Widget::usrLeft(QString usrname, QString time)
{
    int rowNum = ui->usrTblWidget->findItems(usrname, Qt::MatchExactly).first()->row();
    ui->usrTblWidget->removeRow(rowNum);
    ui->msgBrowser->setTextColor(Qt::gray);
    ui->msgBrowser->setCurrentFont(QFont("Times New Roman", 10));
    ui->msgBrowser->append(tr("%1 于 %2 离开！").arg(usrname).arg(time));
    ui->usrNumLbl->setText(tr("在线人数: %1").arg(ui->usrTblWidget->rowCount()));
}

QString Widget::getIP()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress addr, list)
    {
        if (addr.protocol() == QAbstractSocket::IPv4Protocol)
        return addr.toString();
    }
    return 0;
}

QString Widget::getUsr()
{
    return uName;
}

QString Widget::getMsg()
{
    QString msg = ui->msgTextEdit->toHtml();
    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();
    return msg;
}

void Widget::on_sendBtn_clicked()
{
    sndMsg(Msg);
}

void Widget::getFileName(QString name)
{
    fileName = name;
    sndMsg(FileName);
}

void Widget::on_sendTBtn_clicked()
{
    if (ui->usrTblWidget->selectedItems().isEmpty())
    {
        QMessageBox::warning(0, "选择用户", "请先选择目标用户！", QMessageBox::Ok);
        return;
    }
    srv->show();
    srv->initSrv();
}

void Widget::hasPendingFile(QString usrname, QString srvaddr
                            ,QString clntaddr, QString filename)
{
    QString ipAddr =getIP();
    if (ipAddr == clntaddr)
    {
        int btn = QMessageBox::information(this, tr("接收文件"), tr("来自%1(%2)的文件: %3, 是否接收？")
                                           .arg(usrname).arg(srvaddr).arg(filename),
                                           QMessageBox::Yes, QMessageBox::No);
        if (btn == QMessageBox::Yes)
        {
            QString name = QFileDialog::getSaveFileName(0, "保存文件", filename);
            if (!name.isEmpty())
            {
                Client *clnt = new Client(this);
                clnt->setFileName(name);
                clnt->setHostAddr(QHostAddress(srvaddr));
                clnt->show();
            }
        }
        else
        {
            sndMsg(Refuse, srvaddr);
        }
    }
}

void Widget::on_fontCbx_currentFontChanged(const QFont &f)
{
    ui->msgTextEdit->setCurrentFont(f);
    ui->msgTextEdit->setFocus();
}

void Widget::on_sizeCbx_currentIndexChanged(const QString &arg1)
{
    ui->msgTextEdit->setFontPointSize(arg1.toDouble());
    ui->msgTextEdit->setFocus();
}

void Widget::on_boldTBtn_clicked(bool checked)
{
    if (checked)
        ui->msgTextEdit->setFontWeight(QFont::Bold);
    else
        ui->msgTextEdit->setFontWeight(QFont::Normal);
    ui->msgTextEdit->setFocus();
}

void Widget::on_italicTBtn_clicked(bool checked)
{
    ui->msgTextEdit->setFontItalic(checked);
    ui->msgTextEdit->setFocus();
}

void Widget::on_underlineTBtn_clicked(bool checked)
{
    ui->msgTextEdit->setFontUnderline(checked);
    ui->msgTextEdit->setFocus();
}

void Widget::on_colorTBtn_clicked()
{
    color = QColorDialog::getColor(color, this);
    if (color.isValid())
    {
        ui->msgTextEdit->setTextColor(color);
        ui->msgTextEdit->setFocus();
    }
}

void Widget::curFmtChanged(const QTextCharFormat &fmt)
{
    ui->fontCbx->setCurrentFont(fmt.font());
    if (fmt.fontPointSize()<8)
    {
        ui->sizeCbx->setCurrentIndex(4);
    }
    else
    {
        ui->sizeCbx->setCurrentIndex(ui->sizeCbx->findText(QString::number(fmt.fontPointSize())));
    }
    ui->boldTBtn->setChecked(fmt.font().bold());
    ui->italicTBtn->setChecked(fmt.font().italic());
    ui->underlineTBtn->setChecked(fmt.font().underline());
    color = fmt.foreground().color();
}

void Widget::on_saveTBtn_clicked()
{
    if (ui->msgBrowser->document()->isEmpty())
    {
        QMessageBox::warning(0, "警告", "聊天记录为空, 无法保存！", QMessageBox::Ok);
    }
    else{
        QString fname = QFileDialog::getSaveFileName(this, "保存聊天记录", "聊天记录", "文本(*.txt);;所有文件(*.*)");
        if (!fname.isEmpty())
        {
            saveFile(fname);
        }
    }
}

bool Widget::saveFile(const QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "保存文件", tr("无法保存文件 %1:\n %2").arg(filename).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    out << ui->msgBrowser->toPlainText();
    return true;
}

void Widget::on_clearTBtn_clicked()
{
    ui->msgBrowser->clear();
}

void Widget::on_exitBtn_clicked()
{
    close();
}

void Widget::closeEvent(QCloseEvent *e)
{
    sndMsg(UsrLeft);
    QWidget::closeEvent(e);
}

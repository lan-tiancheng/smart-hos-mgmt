#include "server.h"
#include "ui_server.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTcpServer>

server::server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    //setFixedSize(400,207);
    tPort = 5555;
    tSrv = new QTcpServer(this);
    connect(tSrv, SIGNAL(newConnection()), this, SLOT(sndMsg()));
    initSrv();
}

void server::initSrv()
{
    payloadSize = 64*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesTobeWritten = 0;
    ui->progressBar->reset();
    ui->openBtn->setEnabled(true);
    ui->sendBtn->setEnabled(false);
    tSrv->close();
}

server::~server()
{
    delete ui;
}

void server::sndMsg()
{
    ui->sendBtn->setEnabled(false);
    clntConn = tSrv->nextPendingConnection();
    connect(clntConn, SIGNAL(bytesWritten(qint64)), this, SLOT(updClntProgress(qint64)));
    ui->messageLbl->setText(tr("开始传输文件 %1 !").arg(theFileName));
    locFile = new QFile(fileName);
    if (!locFile->open((QFile::ReadOnly)))
    {
        QMessageBox::warning(this, tr("应用程序"), tr("无法读取文件%1:\n%2")
                                   .arg(fileName).arg(locFile->errorString()));
        return;
    }
    totalBytes = locFile->size();
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);       //将发送缓冲区outBlock封装在一个DataStream类型的变量中， 可以通过重载的"<<"操作符填写文件头结构

    sendOut.setVersion(QDataStream::Qt_4_8);
    time.start();
    QString curFile = fileName.right(fileName.size() - fileName.
                                     lastIndexOf('/')-1);       //通过QString的right()函数去掉文件的路径部分,紧将文件部分保存在变量中
    sendOut << qint64(0) << qint64(0) << curFile;               //构造一个临时的文件头，将该值追加到totalBytes字段，从而完成实际需要发送的字节数的记录
    totalBytes += outBlock.size();

    sendOut.device()->seek(0);                                 //将读写操作指向从头开始。
    sendOut << totalBytes << qint64(outBlock.size()
                                -sizeof(qint64)*2);             //填写实际的总长度和文件长度
    bytesTobeWritten = totalBytes - clntConn->write(outBlock);  //将该文件头发出,同时修改待发送字节数。
    outBlock.resize(0);                                         //清空发送缓存区
}

//更新进度条
void server::updClntProgress(qint64 numBytes)
{
    qApp->processEvents();                                      //传输大文件时
    bytesWritten += (int)numBytes;
    if (bytesTobeWritten > 0)
    {
        outBlock = locFile->read(qMin(bytesTobeWritten, payloadSize));
        bytesTobeWritten -= (int)clntConn->write(outBlock);
        outBlock.resize(0);
    }
    else
    {
        locFile->close();
    }
    ui->progressBar->setMaximum(totalBytes);
    ui->progressBar->setValue(bytesWritten);
    float useTime = time.elapsed();
    double speed = bytesWritten / useTime;
    ui->messageLbl->setText(tr("已发送 %1MB (%2MB/s) \n共%3MB 已用时:%4秒\n估计剩余时间：%5秒")
                            .arg(bytesWritten / (1024*1024))
                            .arg(speed*1000 / (1024*1024), 0, 'f', 2)
                            .arg(totalBytes /(1024*1024))
                            .arg(useTime/1000, 0, 'f', 0)
                            .arg(totalBytes/speed/1000 - useTime/1000, 0, 'f', 0));
    if (bytesWritten == totalBytes)
    {
        locFile->close();
        tSrv->close();
        ui->messageLbl->setText(tr("传送文件 %1 成功").arg(theFileName));
    }
}

void server::on_openBtn_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
        ui->messageLbl->setText(tr("要传送的文件为：%1 ").arg(theFileName));
        ui->sendBtn->setEnabled(true);
        ui->openBtn->setEnabled(false);
    }
}

void server::on_sendBtn_clicked()
{
    if (!tSrv->listen(QHostAddress::Any, tPort))
    {
        qDebug() << tSrv->errorString();
        close();
        return;
    }
    ui->messageLbl->setText(tr("等待对方接收..."));
    emit sndFileName(theFileName);
}

void server::on_colseBtn_clicked()
{
    if (tSrv->isListening())
    {
        tSrv->close();
        if (locFile->isOpen())
            locFile->close();
        clntConn->abort();
    }
    close();
}

void server::closeEvent(QCloseEvent *)
{
    on_colseBtn_clicked();
}

void server::refused()
{
    tSrv->close();
    ui->messageLbl->setText("对方拒绝接收！");
}

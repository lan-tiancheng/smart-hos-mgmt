#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include <QTime>
#include <QTcpSocket>

class QFile;
class QTcpServer;
class QTcpClient;
namespace Ui {
class server;
}

class server : public QDialog
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = 0);
    ~server();
    void initSrv();
    void refused();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::server *ui;
    qint16 tPort;
    QTcpServer *tSrv;
    QString fileName;
    QString theFileName;
    QFile *locFile;                  //待发送的文件
    qint64 totalBytes;               //总共需要发送的字节数
    qint64 bytesWritten;             //已发送字节数
    qint64 bytesTobeWritten;         //待发送字节数
    qint64 payloadSize;              //被初始化为一个常量
    QByteArray outBlock;             //缓存一次发送的数据
    QTcpSocket *clntConn;            //客户端连接的套接字
    QTime time;

private slots:
    void sndMsg();                   //发送数据
    void updClntProgress(qint64 numBytes);    //更新进度条

    void on_sendBtn_clicked();

    void on_openBtn_clicked();

    void on_colseBtn_clicked();

signals:
    void sndFileName(QString fileName);
};

#endif // SERVER_H

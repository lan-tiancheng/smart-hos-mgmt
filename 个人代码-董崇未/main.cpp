#include "mainwindow.h"
#include<QFile>
#include "widget.h"
#include "drawer.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QFile qss(":/style/stylesheet.qss");
    if( qss.open(QFile::ReadOnly))
        {
            qDebug("open success");
            QString style = QLatin1String(qss.readAll());
            a.setStyleSheet(style);
            qss.close();
        }else{
             qDebug("Open failed");
         }

    // 获取当前应用程序的路径
    QString app_path = QCoreApplication::applicationDirPath();
    // 拼接文件名
    QString fileName = "config.ini";
    QString config_path = QDir::toNativeSeparators(app_path +QDir::separator() + fileName);

    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://"+gate_host+":"+gate_port;

    MainWindow w;
    w.show();
    return a.exec();

    /*QApplication a(argc, argv);
        // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
        // QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
        Drawer drawer;
        drawer.resize(250, 700);
        drawer.show();
        return a.exec();*/
}

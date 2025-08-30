#include "hmainwindow.h"
#include "pinf.h"
#include "pbd.h"
#include "mainwindow.h"
#include "widget.h"
#include<QFile>
#include"diagnostic.h"

#include <QApplication>
QString  DiagnosticDialog::paintid="ff";
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

    hMainWindow w;
    // 模拟的 JSON 数据
    // QString jsonString = "{\"name\": \"张三\", \"account\": \"123456\", \"time\": \"2024-08-28 10:00\", \"gender\": \"男\", \"age\": \"31\"}";
    // Widget w;
    w.show();
    // w.populateData(jsonString);
    return a.exec();
}

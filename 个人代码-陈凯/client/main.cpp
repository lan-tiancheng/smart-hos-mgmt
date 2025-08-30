#include "homewindow.h"
#include "basewindow.h"
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaseWindow w;
    w.show();
    return a.exec();
}

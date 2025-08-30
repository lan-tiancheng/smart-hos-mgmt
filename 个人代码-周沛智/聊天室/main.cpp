#include "widget.h"
#include "drawer.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    // QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    Drawer drawer;
    drawer.resize(250, 700);
    drawer.show();
    return a.exec();
}

#include "inchartx.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InChartX w;
    w.show();
    return a.exec();
}

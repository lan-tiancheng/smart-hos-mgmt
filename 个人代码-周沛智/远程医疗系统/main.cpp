#include "remainwindow.h"
#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!createConnection())
        return 1;
    reMainWindow w;
    w.show();
    
    return a.exec();
}

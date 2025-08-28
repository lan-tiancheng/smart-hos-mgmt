#include "App.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    App a;
    a.start();
    return app.exec();
}
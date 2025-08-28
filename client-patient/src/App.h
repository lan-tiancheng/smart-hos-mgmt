#pragma once
#include <QObject>

class App : public QObject {
    Q_OBJECT
public:
    void start();
};

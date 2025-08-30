#-------------------------------------------------
#
# Project created by QtCreator 2018-06-17T10:17:49
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyselfQQ
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    drawer.cpp \
    server.cpp \
    client.cpp

HEADERS  += widget.h \
    drawer.h \
    server.h \
    client.h

FORMS    += widget.ui \
    server.ui \
    client.ui

RESOURCES += \
    images.qrc

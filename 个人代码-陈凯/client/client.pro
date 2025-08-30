QT       += core gui
QT       += multimedia
QT      += multimedia texttospeech network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audio.cpp \
    basewindow.cpp \
    bookingwindow.cpp \
    chatwindow.cpp \
    datewindow.cpp \
    http.cpp \
    livewindow.cpp \
    main.cpp \
    homewindow.cpp \
    mainwindow.cpp \
    myinfowindow.cpp \
    owndeal.cpp \
    ownillness.cpp \
    ownmessage.cpp \
    ownwindow.cpp \
    speech.cpp

HEADERS += \
    audio.h \
    basewindow.h \
    bookingwindow.h \
    chatwindow.h \
    datewindow.h \
    homewindow.h \
    http.h \
    livewindow.h \
    mainwindow.h \
    myinfowindow.h \
    owndeal.h \
    ownillness.h \
    ownmessage.h \
    ownwindow.h \
    speech.h

FORMS += \
    audio.ui \
    basewindow.ui \
    bookingwindow.ui \
    chatwindow.ui \
    datewindow.ui \
    homewindow.ui \
    http.ui \
    livewindow.ui \
    mainwindow.ui \
    myinfowindow.ui \
    owndeal.ui \
    ownillness.ui \
    ownmessage.ui \
    ownwindow.ui \
    speech.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=

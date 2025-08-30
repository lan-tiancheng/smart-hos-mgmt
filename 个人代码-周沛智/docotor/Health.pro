#-------------------------------------------------
#
# Project created by QtCreator 2013-06-28T11:12:49
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Health
TEMPLATE = app


SOURCES += main.cpp\
    register.cpp \
    remainwindow.cpp \
    wavescene.cpp \
    circularbuf.cpp \
    tcpthread.cpp \
    tcpserver.cpp \
    openuser.cpp \
    historydata.cpp \
    display.cpp \
    questionnaire.cpp \
    medicalrecord.cpp

HEADERS  += \
    register.h \
    remainwindow.h \
    wavescene.h \
    circularbuf.h \
    DataType.h \
    tcpthread.h \
    tcpserver.h \
    database.h \
    openuser.h \
    historydata.h \
    display.h \
    questionnaire.h \
    medicalrecord.h

FORMS    += \
    register.ui \
    openuser.ui \
    historydata.ui \
    display.ui \
    questionnaire.ui \
    medicalrecord.ui \
    remainwindow.ui

DISTFILES += \
    historyData/p220130703142759/ecgAVF.txt \
    historyData/p220130703142759/ecgAVL.txt \
    historyData/p220130703142759/ecgAVR.txt \
    historyData/p220130703142759/ecgI.txt \
    historyData/p220130703142759/ecgII.txt \
    historyData/p220130703142759/ecgIII.txt \
    historyData/p220130703142759/ecgV1.txt \
    historyData/p220130703142759/ecgV2.txt \
    historyData/p220130703142759/ecgV3.txt \
    historyData/p220130703142759/ecgV4.txt \
    historyData/p220130703142759/ecgV5.txt \
    historyData/p220130703142759/ecgV6.txt \
    historyData/p220130704144114/ecgAVF.txt \
    historyData/p220130704144114/ecgAVL.txt \
    historyData/p220130704144114/ecgAVR.txt \
    historyData/p220130704144114/ecgI.txt \
    historyData/p220130704144114/ecgII.txt \
    historyData/p220130704144114/ecgIII.txt \
    historyData/p220130704144114/ecgV1.txt \
    historyData/p220130704144114/ecgV2.txt \
    historyData/p220130704144114/ecgV3.txt \
    historyData/p220130704144114/ecgV4.txt \
    historyData/p220130704144114/ecgV5.txt \
    historyData/p220130704144114/ecgV6.txt \
    historyData/p220130705160803/ecgAVF.txt \
    historyData/p220130705160803/ecgAVL.txt \
    historyData/p220130705160803/ecgAVR.txt \
    historyData/p220130705160803/ecgI.txt \
    historyData/p220130705160803/ecgII.txt \
    historyData/p220130705160803/ecgIII.txt \
    historyData/p220130705160803/ecgV1.txt \
    historyData/p220130705160803/ecgV2.txt \
    historyData/p220130705160803/ecgV3.txt \
    historyData/p220130705160803/ecgV4.txt \
    historyData/p220130705160803/ecgV5.txt \
    historyData/p220130705160803/ecgV6.txt \
    historyData/p220130705161210/ecgAVF.txt \
    historyData/p220130705161210/ecgAVL.txt \
    historyData/p220130705161210/ecgAVR.txt \
    historyData/p220130705161210/ecgI.txt \
    historyData/p220130705161210/ecgII.txt \
    historyData/p220130705161210/ecgIII.txt \
    historyData/p220130705161210/ecgV1.txt \
    historyData/p220130705161210/ecgV2.txt \
    historyData/p220130705161210/ecgV3.txt \
    historyData/p220130705161210/ecgV4.txt \
    historyData/p220130705161210/ecgV5.txt \
    historyData/p220130705161210/ecgV6.txt \
    historyException/20131101142942/ecgI.txt \
    historyException/p220130703140315/ecgAVF.txt \
    historyException/p220130703140315/ecgAVL.txt \
    historyException/p220130703140315/ecgAVR.txt \
    historyException/p220130703140315/ecgI.txt \
    historyException/p220130703140315/ecgII.txt \
    historyException/p220130703140315/ecgIII.txt \
    historyException/p220130703140315/ecgV1.txt \
    historyException/p220130703140315/ecgV2.txt \
    historyException/p220130703140315/ecgV3.txt \
    historyException/p220130703140315/ecgV4.txt \
    historyException/p220130703140315/ecgV5.txt \
    historyException/p220130703140315/ecgV6.txt \
    historyException/p220130705160846/ecgAVF.txt \
    historyException/p220130705160846/ecgAVL.txt \
    historyException/p220130705160846/ecgAVR.txt \
    historyException/p220130705160846/ecgI.txt \
    historyException/p220130705160846/ecgII.txt \
    historyException/p220130705160846/ecgIII.txt \
    historyException/p220130705160846/ecgV1.txt \
    historyException/p220130705160846/ecgV2.txt \
    historyException/p220130705160846/ecgV3.txt \
    historyException/p220130705160846/ecgV4.txt \
    historyException/p220130705160846/ecgV5.txt \
    historyException/p220130705160846/ecgV6.txt

QT       += core gui \
    network \
    qml\
    multimedia \
    quick multimedia \
    core gui quick qml multimedia network \
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    client.cpp \
    src/asruploader.cpp \
    src/authmanager.cpp \
    src/databasemanager.cpp \
    src/recorderprocess.cpp

HEADERS += \
    client.h \
    src/asruploader.h \
    src/authmanager.h \
    src/databasemanager.h \
    src/recorderprocess.h

FORMS += \
    client.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    client.qrc

DISTFILES += \
    qml/AppointmentScreen.qml \
    qml/DoctorHomeScreen.qml \
    qml/DoctorListScreen.qml \
    qml/DrugSearchScreen.qml \
    qml/HealthInputScreen.qml \
    qml/LoginScreen.qml \
    qml/Main.qml \
    qml/PatientHomeScreen.qml \
    qml/PatientProfileScreen.qml \
    qml/components/VoiceInputButton.qml

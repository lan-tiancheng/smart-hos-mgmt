QT       += core\
    core gui \
    network \
    qml \
    quick\
    sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# Redis++ 头文件路径
INCLUDEPATH += /usr/local/include

# Redis++ 库文件路径
LIBS += -L/usr/local/lib -lredis++ -lhiredis
SOURCES += \
    DatabaseManager.cpp \
    main.cpp \
    models/appointment.cpp \
    models/doctor.cpp \
    models/patient.cpp \
    models/user.cpp \
    server.cpp

HEADERS += \
    DatabaseManager.h \
    models/appointment.h \
    models/doctor.h \
    models/patient.h \
    models/user.h \
    server.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

DISTFILES += \
    app.py \
    asr_service.py \
    domain/_init_.py \
    domain/entities.py \
    infra/auth_service.py \
    infra/sqlite_store.py \
    services/auth_service.py

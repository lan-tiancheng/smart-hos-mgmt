QT       += core gui network sql multimedia texttospeech

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audio.cpp \
    basewindow.cpp \
    bookwindow.cpp \
    chattingroomwindow.cpp \
    chatwindow.cpp \
    childwd.cpp \
    clickedbtn.cpp \
    clickedlabel.cpp \
    clickedoncelabel.cpp \
    client.cpp \
    drawer.cpp \
    global.cpp \
    homewindow.cpp \
    hospitalizationwindow.cpp \
    http.cpp \
    httpmgr.cpp \
    insidewd.cpp \
    loadingdlg.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    medicalcaseswd.cpp \
    medicalexpensewd.cpp \
    medicinesearchwindow.cpp \
    misearchsonwd.cpp \
    outwd.cpp \
    owndeal.cpp \
    ownillness.cpp \
    ownmessage.cpp \
    ownwindow.cpp \
    personalinfowindow.cpp \
    personalwindow.cpp \
    pmainwindow.cpp \
    pmainwindowhome.cpp \
    quizwd.cpp \
    registerdialog.cpp \
    resetdialog.cpp \
    server.cpp \
    showdetails.cpp \
    skinwd.cpp \
    speech.cpp \
    tcpmgr.cpp \
    timerbtn.cpp \
    timetablewd.cpp \
    userdata.cpp \
    usermgr.cpp \
    widget.cpp \
    womanwd.cpp

HEADERS += \
    ChatItemBase.h \
    ChatView.h \
    ChildDoc.h \
    GlobalData.h \
    InsideDoc.h \
    MedicineItem.h \
    OutDoc.h \
    RegisterDataTransmit.h \
    SkinDoc.h \
    WomanDoc.h \
    audio.h \
    basewindow.h \
    bookwindow.h \
    chattingroomwindow.h \
    chatwindow.h \
    childwd.h \
    clickedbtn.h \
    clickedlabel.h \
    clickedoncelabel.h \
    client.h \
    drawer.h \
    global.h \
    homewindow.h \
    hospitalizationwindow.h \
    http.h \
    httpmgr.h \
    insidewd.h \
    invaliditem.h \
    listitembase.h \
    loadingdlg.h \
    logindialog.h \
    mainwindow.h \
    medicalcaseswd.h \
    medicalexpensewd.h \
    medicinesearchwindow.h \
    misearchsonwd.h \
    outwd.h \
    owndeal.h \
    ownillness.h \
    ownmessage.h \
    ownwindow.h \
    personalinfowindow.h \
    personalwindow.h \
    pmainwindow.h \
    pmainwindowhome.h \
    quizwd.h \
    registerdialog.h \
    resetdialog.h \
    searchlist.h \
    server.h \
    showdetails.h \
    singleton.h \
    skinwd.h \
    speech.h \
    tcpmgr.h \
    timerbtn.h \
    timetablewd.h \
    userdata.h \
    usermgr.h \
    widget.h \
    womanwd.h

FORMS += \
    audio.ui \
    basewindow.ui \
    bookwindow.ui \
    chattingroomwindow.ui \
    chatwindow.ui \
    childwd.ui \
    client.ui \
    homewindow.ui \
    hospitalizationwindow.ui \
    http.ui \
    insidewd.ui \
    loadingdlg.ui \
    logindialog.ui \
    mainwindow.ui \
    medicalcaseswd.ui \
    medicalexpensewd.ui \
    medicinesearchwindow.ui \
    misearchsonwd.ui \
    outwd.ui \
    owndeal.ui \
    ownillness.ui \
    ownmessage.ui \
    ownwindow.ui \
    personalinfowindow.ui \
    personalwindow.ui \
    pmainwindow.ui \
    pmainwindowhome.ui \
    quizwd.ui \
    registerdialog.ui \
    resetdialog.ui \
    server.ui \
    showdetails.ui \
    skinwd.ui \
    speech.ui \
    timetablewd.ui \
    widget.ui \
    womanwd.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rcs.qrc

DISTFILES += \
    config.ini \
    res/banlangen.jpg \
    res/ganmaoling999.jpg \
    res/huoxiangzhengqishui.jpg \
    res/jiuxinwan.jpg \
    res/liuweidihuangwanjpg.jpg \
    res/medicalsearchpage.jpg \
    res/weishuping.jpg \
    style/stylesheet.qss

unix:CONFIG(release, debug | release)
{
    # 指定要拷贝的文件目录为工程目录下的 config.ini 文件
    TargetConfig = $${PWD}/config.ini

    # 输出目录
    OutputDir = $${OUT_PWD}/$${DESTDIR}

    # 执行 cp 命令
    QMAKE_POST_LINK += cp -f \"$$TargetConfig\" \"$$OutputDir\"
}



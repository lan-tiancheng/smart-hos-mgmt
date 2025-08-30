QT       += core gui network
QT       += sql
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    absence.cpp \
    advice.cpp \
    change.cpp \
    circularbuf.cpp \
    clickedlabel.cpp \
    client.cpp \
    diagnostic.cpp \
    display.cpp \
    drawer.cpp \
    global.cpp \
    guidemainwindow.cpp \
    historydata.cpp \
    hmainwindow.cpp \
    hospital.cpp \
    httpmgr.cpp \
    inchartx.cpp \
    information.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    medicalrecord.cpp \
    mydialog.cpp \
    openuser.cpp \
    pbd.cpp \
    pinf.cpp \
    questionnaire.cpp \
    register.cpp \
    registerdialog.cpp \
    remainwindow.cpp \
    resetdialog.cpp \
    server.cpp \
    tcpmgr.cpp \
    tcpserver.cpp \
    tcpthread.cpp \
    timerbtn.cpp \
    usermgr.cpp \
    wavescene.cpp \
    widget.cpp

HEADERS += \
    DataType.h \
    absence.h \
    advice.h \
    change.h \
    circularbuf.h \
    clickedlabel.h \
    client.h \
    database.h \
    diagnostic.h \
    display.h \
    drawer.h \
    global.h \
    guidemainwindow.h \
    historydata.h \
    hmainwindow.h \
    hospital.h \
    httpmgr.h \
    inchartx.h \
    information.h \
    logindialog.h \
    mainwindow.h \
    medicalrecord.h \
    mydialog.h \
    mystruct.h \
    openuser.h \
    pbd.h \
    pinf.h \
    questionnaire.h \
    register.h \
    registerdialog.h \
    remainwindow.h \
    resetdialog.h \
    server.h \
    singleton.h \
    tcpmgr.h \
    tcpserver.h \
    tcpthread.h \
    timerbtn.h \
    usermgr.h \
    wavescene.h \
    widget.h

FORMS += \
    absence.ui \
    advice.ui \
    change.ui \
    client.ui \
    diagnostic.ui \
    display.ui \
    guidemainwindow.ui \
    historydata.ui \
    hmainwindow.ui \
    hospital.ui \
    inchartx.ui \
    information.ui \
    logindialog.ui \
    mainwindow.ui \
    medicalrecord.ui \
    mydialog.ui \
    openuser.ui \
    pbd.ui \
    pinf.ui \
    questionnaire.ui \
    register.ui \
    registerdialog.ui \
    remainwindow.ui \
    resetdialog.ui \
    server.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    doctorDemo.qrc \
    doctorDemo.qrc \
    images.qrc \
    rcs.qrc \
    rcs.qrc \
    rcs.qrc

DISTFILES += \
    Health.pro.user.78ab447 \
    PreProject.pro.user \
    PreProject.pro.user.27a7e1c \
    PreProject.pro.user.5814c12 \
    config.ini \
    green.webp \
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
    historyData/p220240827193736/ecgAVF.txt \
    historyData/p220240827193736/ecgAVL.txt \
    historyData/p220240827193736/ecgAVR.txt \
    historyData/p220240827193736/ecgI.txt \
    historyData/p220240827193736/ecgII.txt \
    historyData/p220240827193736/ecgIII.txt \
    historyData/p220240827193736/ecgV1.txt \
    historyData/p220240827193736/ecgV2.txt \
    historyData/p220240827193736/ecgV3.txt \
    historyData/p220240827193736/ecgV4.txt \
    historyData/p220240827193736/ecgV5.txt \
    historyData/p220240827193736/ecgV6.txt \
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
    historyException/p220130705160846/ecgV6.txt \
    pictures/个人信息x64.png \
    pictures/主界面背景图.jpg \
    pictures/患者主界面.jpg \
    pictures/患者信息-copy x64.png \
    pictures/患者信息-copy.png \
    pictures/患者信息.png \
    pictures/患者信息x64.png \
    pictures/患者信息查询.png \
    pictures/患者信息查询x64.png \
    pictures/考勤管理  X48.png \
    pictures/考勤管理  x64.png \
    pictures/考勤管理 (1).png \
    pictures/考勤管理 x32.png \
    pictures/考勤管理 x64.png \
    pictures/考勤管理.png \
    pictures/预约背景图.jpg \
    red.webp \
    res/add_friend.png \
    res/add_friend_hover.png \
    res/add_friend_normal.png \
    res/addtip.png \
    res/arowdown.png \
    res/chat_icon.png \
    res/chat_icon_hover.png \
    res/chat_icon_press.png \
    res/chat_icon_select_hover.png \
    res/chat_icon_select_press.png \
    res/close_search.png \
    res/close_transparent.png \
    res/contact_list.png \
    res/contact_list_hover.png \
    res/contact_list_press.png \
    res/female.png \
    res/filedir.png \
    res/filedir_hover.png \
    res/filedir_press.png \
    res/head_1.jpg \
    res/head_2.jpg \
    res/head_3.jpg \
    res/head_4.jpg \
    res/head_5.jpg \
    res/ice.png \
    res/loading.gif \
    res/male.png \
    res/msg_chat_hover.png \
    res/msg_chat_normal.png \
    res/msg_chat_press.png \
    res/red_point.png \
    res/right_tip.png \
    res/search.png \
    res/smile.png \
    res/smile_hover.png \
    res/smile_press.png \
    res/tipclose.png \
    res/unvisible.png \
    res/unvisible_hover.png \
    res/video_chat_hover.png \
    res/video_chat_normal.png \
    res/video_chat_press.png \
    res/visible.png \
    res/visible_hover.png \
    res/voice_chat_hover.png \
    res/voice_chat_normal.png \
    res/voice_chat_press.png \
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

SUBDIRS += \
    ../../../../health/Health.pro \
    Health.pro



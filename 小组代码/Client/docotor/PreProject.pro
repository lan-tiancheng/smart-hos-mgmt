QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    absence.cpp \
    advice.cpp \
    change.cpp \
    clickedlabel.cpp \
    diagnostic.cpp \
    global.cpp \
    hmainwindow.cpp \
    hospital.cpp \
    httpmgr.cpp \
    information.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    pbd.cpp \
    pinf.cpp \
    registerdialog.cpp \
    resetdialog.cpp \
    tcpmgr.cpp \
    timerbtn.cpp \
    usermgr.cpp

HEADERS += \
    absence.h \
    advice.h \
    change.h \
    clickedlabel.h \
    diagnostic.h \
    global.h \
    hmainwindow.h \
    hospital.h \
    httpmgr.h \
    information.h \
    logindialog.h \
    mainwindow.h \
    pbd.h \
    pinf.h \
    registerdialog.h \
    resetdialog.h \
    singleton.h \
    tcpmgr.h \
    timerbtn.h \
    usermgr.h

FORMS += \
    absence.ui \
    advice.ui \
    change.ui \
    diagnostic.ui \
    hmainwindow.ui \
    hospital.ui \
    information.ui \
    logindialog.ui \
    mainwindow.ui \
    pbd.ui \
    pinf.ui \
    registerdialog.ui \
    resetdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    doctorDemo.qrc \
    rcs.qrc \
    rcs.qrc

DISTFILES += \
    PreProject.pro.user \
    PreProject.pro.user.5814c12 \
    config.ini \
    green.webp \
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



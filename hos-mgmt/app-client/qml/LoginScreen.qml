// LoginScreen.qml — Qt5 兼容版（轻玻璃拟态 · 蓝白粉）
// 逻辑保持不变：authManager.requestLogin / requestRegister；成功后 push 医生/病人主页
// 需要图片（均在 qml/images/ 下）：hero.svg, icon_user.svg, icon_lock.svg

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Item {
    id: root
    anchors.fill: parent

    // ===== 运行参数（保持原有命名） =====
    property string apiBase: "http://127.0.0.1:8080"
    property string wsUrl: ""
    property string token: ""
    property bool   registering: false

    // ===== 资源与全局尺寸 =====
    readonly property url assetsBase: Qt.resolvedUrl("images/")
    function asset(name) { return assetsBase + name }

    // 强制图标尺寸（你可随时改这个数）
    property int iconSizePx: 22
    // 英雄插画最大宽度（可按喜好微调）
    property int heroMaxWidth: 280

    // ===== 主题色 =====
    readonly property color cBlue:  "#5AA9FF"
    readonly property color cPink:  "#FF9AC2"
    readonly property color cText:  "#0F1B2D"
    readonly property color cGlass: "#FFFFFFCC"
    readonly property color cStroke:"#FFFFFF66"

    // ===== 背景：柔和渐变 + 两个柔光圆（加快版）=====
    Rectangle {
        id: bg
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#E6F2FF" }
            GradientStop { position: 0.5; color: "#FDFDFF" }
            GradientStop { position: 1.0; color: "#FFE9F3" }
        }

        // 柔光圆 1（水平往返 + 呼吸透明）——更快：8s 单程
        Rectangle {
            id: glow1
            width: Math.max(220, bg.width * 0.22)
            height: width
            radius: width / 2
            color: cBlue
            opacity: 0.24
            y: bg.height * 0.25
            x: -width * 0.3

            SequentialAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: bg.width - glow1.width * 0.7; duration: 8000;  easing.type: Easing.InOutSine }
                NumberAnimation { to: -glow1.width * 0.3; duration: 8000;  easing.type: Easing.InOutSine }
            }
            SequentialAnimation on opacity {
                loops: Animation.Infinite
                NumberAnimation { from: 0.16; to: 0.30; duration: 4500; easing.type: Easing.InOutSine }
                NumberAnimation { from: 0.30; to: 0.16; duration: 4500; easing.type: Easing.InOutSine }
            }
        }

        // 柔光圆 2（斜向往返）——更快：9s 单程
        Rectangle {
            id: glow2
            width: Math.max(260, bg.width * 0.26)
            height: width
            radius: width / 2
            color: cPink
            opacity: 0.20
            x: bg.width * 0.65
            y: bg.height * 0.60

            ParallelAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: bg.width * 0.15; duration: 9000; easing.type: Easing.InOutQuad }
                NumberAnimation { to: bg.width * 0.65; duration: 9000; easing.type: Easing.InOutQuad }
            }
            ParallelAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { to: bg.height * 0.15; duration: 9000; easing.type: Easing.InOutQuad }
                NumberAnimation { to: bg.height * 0.60; duration: 9000; easing.type: Easing.InOutQuad }
            }
        }
    }

    // ===== 居中玻璃卡 =====
    Item {
        id: panel
        width: Math.min(root.width * 0.92, 920)
        height: Math.min(root.height * 0.88, 600)
        anchors.centerIn: parent

        ShaderEffectSource { id: bgSrc; anchors.fill: parent; sourceItem: bg; hideSource: false; live: true }
        FastBlur { anchors.fill: parent; source: bgSrc; radius: 28 }

        Rectangle {
            id: glass
            anchors.fill: parent
            color: cGlass
            radius: 22
            border.color: cStroke; border.width: 1
        }
        DropShadow {
            anchors.fill: glass; source: glass
            radius: 26; samples: 32; horizontalOffset: 0; verticalOffset: 14
            color: "#33000000"
        }

        // ===== 内容 =====
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 28
            spacing: 18

            // 顶部：标题 + 角色切换
            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                ColumnLayout {
                    Layout.fillWidth: true
                    Label {
                        text: "智慧医疗系统"
                        color: cText
                        font.pixelSize: 30; font.bold: true
                    }
                    Label {
                        text: "Smart Healthcare · 登录 / 注册"
                        color: "#6B7B93"
                        font.pixelSize: 13
                    }
                }

                // 更聪明的 pill switch：底块跟随按钮实际宽度与位置
                Rectangle {
                    id: rolePill
                    radius: 18
                    height: 38
                    width: Math.max(196, btnPatient.implicitWidth + btnDoctor.implicitWidth + 40)
                    color: "#FFFFFFA0"
                    border.color: cStroke
                    property bool doctorMode: false

                    Rectangle {
                        id: selBg
                        radius: 14
                        height: parent.height - 8
                        y: 4
                        width: (rolePill.doctorMode ? btnDoctor.width : btnPatient.width)
                        x: (rolePill.doctorMode ? btnDoctor.x : btnPatient.x)
                        color: cBlue; opacity: 0.25
                        Behavior on x { NumberAnimation { duration: 220; easing.type: Easing.InOutQuad } }
                        Behavior on width { NumberAnimation { duration: 220; easing.type: Easing.InOutQuad } }
                    }

                    Row {
                        id: btnRow
                        anchors.fill: parent
                        anchors.margins: 4
                        spacing: 4

                        Button {
                            id: btnPatient
                            text: "病人"
                            flat: true; checkable: true
                            checked: !rolePill.doctorMode
                            implicitWidth: Math.max(80, contentItem.implicitWidth + 16)
                            background: Item {}
                            onClicked: rolePill.doctorMode = false
                        }
                        Button {
                            id: btnDoctor
                            text: "医生"
                            flat: true; checkable: true
                            checked: rolePill.doctorMode
                            implicitWidth: Math.max(80, contentItem.implicitWidth + 16)
                            background: Item {}
                            onClicked: rolePill.doctorMode = true
                        }
                    }
                }
            }

            // 主体：左插画 / 右表单
            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 18

                // 左：插画（强制缩放）
                Rectangle {
                    Layout.fillHeight: true
                    Layout.preferredWidth: Math.min(panel.width * 0.42, 380)
                    radius: 18
                    color: "#FFFFFF90"
                    border.color: cStroke

                    Image {
                        id: hero
                        anchors.centerIn: parent
                        source: asset("hero.svg")
                        asynchronous: true
                        fillMode: Image.PreserveAspectFit
                        width: Math.min(parent.width * 0.8, heroMaxWidth)
                        height: width * 0.75
                        // 强制光栅化大小，SVG 也会按此尺寸渲染
                        sourceSize.width: width
                        sourceSize.height: height
                        smooth: true
                        visible: status === Image.Ready
                    }
                    // 占位渐变圆（资源缺失时）
                    Rectangle {
                        visible: hero.status !== Image.Ready
                        width: Math.min(parent.width * 0.7, 240)
                        height: width
                        radius: width / 2
                        anchors.centerIn: parent
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#AAD7FF" }
                            GradientStop { position: 1.0; color: "#FFC7DC" }
                        }
                        NumberAnimation on rotation { from: 0; to: 360; duration: 16000; loops: Animation.Infinite }
                    }

                    Column {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        spacing: 6
                        Label { text: "欢迎来到智慧医疗系统"; color: cText; font.pixelSize: 18; font.bold: true; horizontalAlignment: Text.AlignHCenter }
                        Label {
                            width: parent.width * 1
                            wrapMode: Text.WordWrap; color: "#5C6C80"; horizontalAlignment: Text.AlignHCenter
                            text: "请登录或注册以继续"
                        }
                    }
                }

                // 右：表单
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 18
                    color: "#FFFFFFB0"
                    border.color: cStroke

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 12

                        // 顶部切换
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 8
                            Label { text: stack.currentIndex === 0 ? "登录" : "注册"; font.pixelSize: 20; font.bold: true; color: cText }
                            Item { Layout.fillWidth: true }
                            Button {
                                id: switcher
                                text: stack.currentIndex === 0 ? "没有账户？去注册" : "已有账户？去登录"
                                onClicked: {
                                    stack.currentIndex = 1 - stack.currentIndex
                                    loginStatus.text = ""
                                    regStatus.text   = ""
                                    registering = false
                                }
                            }
                        }

                        StackLayout {
                            id: stack
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            // ===== 登录 =====
                            ColumnLayout {
                                spacing: 10
                                Layout.fillWidth: true
                                Layout.fillHeight: true

                                RowLayout {
                                    Layout.fillWidth: true; spacing: 8
                                    Image {
                                        source: asset("icon_user.svg")
                                        width: iconSizePx; height: iconSizePx
                                        sourceSize: Qt.size(iconSizePx, iconSizePx)
                                        fillMode: Image.PreserveAspectFit
                                        smooth: true
                                        visible: status === Image.Ready
                                    }
                                    TextField { id: user; Layout.fillWidth: true; placeholderText: "用户名" }
                                }
                                RowLayout {
                                    Layout.fillWidth: true; spacing: 8
                                    Image {
                                        source: asset("icon_lock.svg")
                                        width: iconSizePx; height: iconSizePx
                                        sourceSize: Qt.size(iconSizePx, iconSizePx)
                                        fillMode: Image.PreserveAspectFit
                                        smooth: true
                                        visible: status === Image.Ready
                                    }
                                    TextField { id: pass; Layout.fillWidth: true; placeholderText: "密码"; echoMode: TextInput.Password }
                                }

                                RowLayout {
                                    Layout.fillWidth: true; spacing: 10
                                    Button {
                                        id: btnLogin
                                        Layout.fillWidth: true
                                        text: busy.running ? "登录中…" : "登录"
                                        enabled: !busy.running
                                        onClicked: {
                                            if (!authManager || typeof authManager.requestLogin !== "function") {
                                                toast.show("未找到登录接口", true); return
                                            }
                                            if (!user.text || !pass.text) {
                                                shake.start(); toast.show("请输入用户名与密码", true); return
                                            }
                                            busy.running = true
                                            const userType = rolePill.doctorMode ? "doctor" : "patient"
                                            authManager.requestLogin(userType, user.text, pass.text)
                                        }
                                    }
                                    BusyIndicator { id: busy; running: false; visible: running }
                                }

                                Label {
                                    id: loginStatus
                                    text: ""
                                    color: "#D62D30"
                                    font.pixelSize: 13
                                    wrapMode: Text.WordWrap
                                    Layout.fillWidth: true
                                }

                                Item { Layout.fillHeight: true }
                            }

                            // ===== 注册 =====
                            ColumnLayout {
                                spacing: 8
                                Layout.fillWidth: true
                                Layout.fillHeight: true

                                TextField { id: regUser;   placeholderText: "用户名"; Layout.fillWidth: true }
                                TextField { id: regPass;   placeholderText: "密码"; echoMode: TextInput.Password; Layout.fillWidth: true }
                                TextField { id: regPhone;  placeholderText: "电话"; Layout.fillWidth: true }
                                TextField { id: regAddr;   placeholderText: "地址"; Layout.fillWidth: true }
                                TextField { id: regAge;    placeholderText: "年龄（数字）"; inputMethodHints: Qt.ImhDigitsOnly; Layout.fillWidth: true }
                                TextField { id: regGender; placeholderText: "性别（男/女 或 male/female）"; Layout.fillWidth: true }

                                Button {
                                    text: registering ? "注册中…" : "注册"
                                    enabled: !registering
                                    Layout.fillWidth: true
                                    onClicked: {
                                        if (!authManager || typeof authManager.requestRegister !== "function") {
                                            toast.show("未找到注册接口", true); return
                                        }
                                        if (!regUser.text || !regPass.text) { toast.show("用户名和密码不能为空", true); return }
                                        const age = parseInt(regAge.text); if (isNaN(age) || age <= 0) { toast.show("年龄必须是大于0的数字", true); return }
                                        registering = true
                                        const userType = rolePill.doctorMode ? "doctor" : "patient"
                                        authManager.requestRegister(userType, regUser.text, regPass.text, regPhone.text, regAddr.text, age, regGender.text)
                                    }
                                }

                                Label {
                                    id: regStatus
                                    text: ""
                                    color: "#D62D30"
                                    font.pixelSize: 13
                                    wrapMode: Text.WordWrap
                                    Layout.fillWidth: true
                                }

                                Item { Layout.fillHeight: true }
                            }
                        }
                    }
                }
            }
        }
    }

    // ===== 顶部 Toast =====
    Rectangle {
        id: toast
        radius: 10
        color: "#CC222222"
        anchors.horizontalCenter: parent.horizontalCenter
        y: shown ? 24 : -height
        width: Math.min(parent.width * 0.8, 420)
        height: msg.implicitHeight + 16
        opacity: shown ? 1 : 0
        visible: opacity > 0
        property bool shown: false
        property bool danger: false
        function show(text, isDanger) { msg.text = text || ""; danger = !!isDanger; shown = true; hideTimer.restart() }
        Timer { id: hideTimer; interval: 2200; repeat: false; onTriggered: toast.shown = false }
        Behavior on y { NumberAnimation { duration: 200; easing.type: Easing.OutCubic } }
        Behavior on opacity { NumberAnimation { duration: 200 } }
        Label { id: msg; anchors.centerIn: parent; color: toast.danger ? "#FFDEE3" : "#FFF"; wrapMode: Text.WordWrap }
    }

    // ===== 登录失败轻抖动 =====
    SequentialAnimation {
        id: shake; running: false
        PropertyAnimation { target: panel; property: "x"; from: 0; to: 10; duration: 60 }
        PropertyAnimation { target: panel; property: "x"; from: 10; to: -10; duration: 100 }
        PropertyAnimation { target: panel; property: "x"; from: -10; to: 0; duration: 60 }
    }

    // ===== 工具函数（保持原逻辑） =====
    function inferWsUrlFromApiBase(base) {
        var b = (base || "http://127.0.0.1:8080").replace(/\/+$/, "")
        return b.replace(/^http(s?):/, "ws$1:") + "/ws/chat"
    }

    // ===== 与后端交互结果（保持信号名） =====
    Connections {
        target: authManager

        function onLoginSuccess(userId, userType) {
            busy.running = false
            loginStatus.color = "#1B8A5A"
            loginStatus.text = "登录成功！UserId: " + userId

            var t = userType
            var isDoctor = (typeof t === "boolean") ? t
                          : ((t + "").toLowerCase() === "doctor" || t === 1 || (t + "") === "1")

            var ws = inferWsUrlFromApiBase(root.apiBase)

            if (isDoctor) {
                var dparams = { doctorId: userId, doctorName: user.text, apiBase: root.apiBase, wsUrl: ws, token: root.token }
                mainStackView.push("DoctorHomeScreen.qml", dparams)
            } else {
                var pparams = { patientId: userId, patientName: user.text, apiBase: root.apiBase, wsUrl: ws, token: root.token }
                mainStackView.push("PatientHomeScreen.qml", pparams)
            }
        }
        function onLoginFailed(reason) {
            busy.running = false
            loginStatus.color = "#D62D30"
            loginStatus.text = reason || "登录失败"
            shake.start(); toast.show(loginStatus.text, true)
        }
        function onRegisterSuccess() {
            registering = false
            regStatus.color = "#1B8A5A"
            regStatus.text = "注册成功！请登录。"
            toast.show("注册成功"); stack.currentIndex = 0
        }
        function onRegisterFailed(reason) {
            registering = false
            regStatus.color = "#D62D30"
            regStatus.text = reason || "注册失败"
            toast.show(regStatus.text, true)
        }
    }
}

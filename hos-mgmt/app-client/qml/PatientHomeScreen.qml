// PatientHomeScreen.qml — Qt5 兼容 · 轻玻璃拟态（蓝白粉）
// 逻辑保持：pushPage / baseParams / 各按钮 onClicked
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Page {
    id: page
    title: "患者主界面"

    // 登录页通过 mainStackView.push 传入
    property string apiBase:  "http://127.0.0.1:8080"
    property string wsUrl:    "ws://127.0.0.1:8080/ws/chat"
    property string token:    ""
    property int    patientId: -1
    property string patientName: "我"

    // 统一的图片相对目录 → 解析成带协议的 URL，防止“协议未知”
    readonly property url imgDir: Qt.resolvedUrl("images/")
    function img(name) { return imgDir + name }

    // 全局尺寸与主题
    property int iconSizePx: 26
    readonly property color cBlue:  "#5AA9FF"
    readonly property color cPink:  "#FF9AC2"
    readonly property color cText:  "#0F1B2D"
    readonly property color cGlass: "#FFFFFFCC"
    readonly property color cStroke:"#FFFFFF66"

    // ============ 背景：柔和渐变 + 两个柔光圆 ============
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#E6F2FF" }
            GradientStop { position: 0.5; color: "#FDFDFF" }
            GradientStop { position: 1.0; color: "#FFE9F3" }
        }

        // 左上蓝光（更快）
        Rectangle {
            id: glowLeft
            width: Math.max(220, parent.width * 0.22)
            height: width
            radius: width/2
            color: cBlue
            opacity: 0.22
            y: parent.height * 0.18
            x: -width * 0.3
            SequentialAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: parent.width - glowLeft.width * 0.7; duration: 8000;  easing.type: Easing.InOutSine }
                NumberAnimation { to: -glowLeft.width * 0.3;  duration: 8000;  easing.type: Easing.InOutSine }
            }
            SequentialAnimation on opacity {
                loops: Animation.Infinite
                NumberAnimation { from: 0.16; to: 0.30; duration: 4500; easing.type: Easing.InOutSine }
                NumberAnimation { from: 0.30; to: 0.16; duration: 4500; easing.type: Easing.InOutSine }
            }
        }
        // 右下粉光（更快）
        Rectangle {
            id: glowRight
            width: Math.max(260, parent.width * 0.26)
            height: width
            radius: width/2
            color: cPink
            opacity: 0.20
            x: parent.width * 0.65
            y: parent.height * 0.62
            ParallelAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: parent.width * 0.15; duration: 9000; easing.type: Easing.InOutQuad }
                NumberAnimation { to: parent.width * 0.65; duration: 9000; easing.type: Easing.InOutQuad }
            }
            ParallelAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { to: parent.height * 0.18; duration: 9000; easing.type: Easing.InOutQuad }
                NumberAnimation { to: parent.height * 0.62; duration: 9000; easing.type: Easing.InOutQuad }
            }
        }
    }

    // ============ 中央玻璃面板 ============
    Item {
        id: panel
        anchors.centerIn: parent
        width: Math.min(page.width * 0.92, 1000)
        height: Math.min(page.height * 0.88, 620)

        // 背景模糊 + 玻璃
        ShaderEffectSource { id: bgSrc; anchors.fill: parent; sourceItem: page.contentItem; hideSource: false; live: true }
        FastBlur { anchors.fill: parent; source: bgSrc; radius: 26 }
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

        // ============ 内容 ============
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 28
            spacing: 18

            // 顶部信息
            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                ColumnLayout {
                    Layout.fillWidth: true
                    Label {
                        text: "患者主界面"
                        color: cText
                        font.pixelSize: 30
                        font.bold: true
                    }
                    Label {
                        text: "欢迎，" + (page.patientName || "我")
                        color: "#5C6C80"
                        font.pixelSize: 13
                    }
                }

                // 右上角返回按钮（行为不改）
                Button {
                    text: "退出登录"
                    onClicked: { mainStackView.pop() }
                }
            }

            // 分隔线
            Rectangle { Layout.fillWidth: true; height: 1; color: "#FFFFFF66" }

            // 欢迎横幅（淡入上浮）
            Rectangle {
                Layout.fillWidth: true
                height: 86
                radius: 16
                color: "#FFFFFFAA"
                border.color: "#FFFFFF66"

                opacity: 0.0; y: 6
                Behavior on opacity { NumberAnimation { duration: 260 } }
                Behavior on y { NumberAnimation { duration: 260; easing.type: Easing.OutCubic } }
                Component.onCompleted: { opacity = 1.0; y = 0 }

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12

                    Rectangle {
                        width: 52; height: 52; radius: 26
                        color: "#FFFFFF"
                        border.color: "#FFFFFF88"
                        Label { anchors.centerIn: parent; text: "🩺"; font.pixelSize: 24 }
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        Label { text: "智慧医疗 · 患者服务中心"; color: cText; font.bold: true }
                        Label { text: "快速进入评估、挂号、对话、药品等功能"; color: "#6B7B93"; font.pixelSize: 12 }
                    }
                }
            }

            // ============ 功能区（按钮栅格） ============
            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 4
                rowSpacing: 18
                columnSpacing: 18

                // 统一样式按钮
                Component {
                    id: glassButton
                    Button {
                        id: control
                        display: AbstractButton.TextUnderIcon
                        icon.width: iconSizePx
                        icon.height: iconSizePx
                        font.pixelSize: 13
                        padding: 14
                        background: Rectangle {
                            radius: 14
                            color: "#FFFFFFB3"
                            border.color: "#FFFFFF80"
                            layer.enabled: true
                            layer.effect: DropShadow {
                                horizontalOffset: 0; verticalOffset: 6
                                radius: 16; samples: 24; color: "#1A000000"
                            }
                        }
                        scale: hovered ? 1.04 : 1.0
                        Behavior on scale { NumberAnimation { duration: 120 } }
                    }
                }

                // ===== 第一排 =====
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "健康评估"
                        item.icon.source = img("health.svg")
                        item.onClicked.connect(function() { pushPage("HealthInputScreen.qml") })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "个人信息"
                        item.icon.source = img("profile.svg")
                        item.onClicked.connect(function() { pushPage("PatientProfileScreen.qml") })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "挂号"
                        item.icon.source = img("register.svg")
                        item.onClicked.connect(function() {
                            if ((page.patientId || 0) <= 0) { console.log("阻止跳转：缺少 patientId"); return }
                            var params = baseParams()
                            params.patientId = page.patientId
                            params.patientName = page.patientName || "我"
                            pushPage("DoctorListScreen.qml", params)
                        })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "查看医生信息"
                        item.icon.source = img("doctor.svg")
                        item.onClicked.connect(function() { pushPage("DoctorInfoScreen.qml") })
                    }
                }

                // ===== 第二排 =====
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "查看病例"
                        item.icon.source = img("case.svg")
                        item.onClicked.connect(function() { pushPage("CaseListScreen.qml") })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "预约就诊"
                        item.icon.source = img("appointment.svg")
                        item.onClicked.connect(function() { pushPage("AppointmentScreen.qml") })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "药品搜索"
                        item.icon.source = img("drug.svg")
                        item.onClicked.connect(function() { pushPage("DrugSearchScreen.qml") })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "住院信息"
                        item.icon.source = img("hospital.svg")
                        item.onClicked.connect(function() { pushPage("HospitalInfoScreen.qml") })
                    }
                }

                // ===== 第三排 =====
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "线上支付"
                        item.icon.source = img("pay.svg")
                        item.onClicked.connect(function() { pushPage("OnlinePayScreen.qml") })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "医疗助手"
                        item.icon.source = img("ai.svg")
                        item.onClicked.connect(function() { pushPage("GLMAiChatScreen.qml") })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "咨询服务"
                        item.icon.source = img("room.svg")
                        item.onClicked.connect(function() {
                            if ((page.patientId || 0) <= 0) { console.log("阻止跳转：缺少 patientId"); return }
                            var params = baseParams()
                            params.patientId = page.patientId
                            params.patientName = page.patientName || "我"
                            pushPage("DoctorListScreen.qml", params)
                        })
                    }
                }
                // 占位（保持整齐）
                Item { Layout.fillWidth: true }
            }
        }
    }

    // ============ 便捷函数（保持原有逻辑） ============
    function pushPage(url, params) {
        if (typeof mainStackView !== "undefined" && mainStackView.push) {
            mainStackView.push(url, params)
        } else if (StackView.view) {
            StackView.view.push(url, params)
        } else {
            console.log("未找到 StackView，无法跳转")
        }
    }
    function baseParams() {
        return { apiBase: page.apiBase, wsUrl: page.wsUrl, token: page.token }
    }
}

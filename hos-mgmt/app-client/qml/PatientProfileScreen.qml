// PatientProfileScreen.qml — Qt5 兼容 · 轻玻璃拟态（蓝白粉）
// 逻辑保持不变：authManager.getPatientInfo(...) / updatePatientInfo(...)
// 固定头像：请在 qml/images 下放置 avatar.png，并在 qrc 中加入：
//   <file>images/avatar.png</file>

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Page {
    id: profilePage
    title: "个人信息"

    // -------- 状态与数据（保持原命名）--------
    property bool   editing: false
    property string username: ""
    property string phone: ""
    property string address: ""
    property string age: ""
    property string gender: ""

    property string infoHint: ""
    property bool   loading: false
    property var    rawInfo: ({})   // 取消用

    // 固定头像（写死）：qrc 路径（确保进了 qrc）
    readonly property string avatarSrc: "images/avatar.jpeg"

    // 主题
    readonly property color cBlue:  "#5AA9FF"
    readonly property color cPink:  "#FF9AC2"
    readonly property color cText:  "#0F1B2D"
    readonly property color cGlass: "#FFFFFFCC"
    readonly property color cStroke:"#FFFFFF66"

    // ========== 背景动效：三枚柔光圆（更快，全局移动，百分比） ==========
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#E6F2FF" }
            GradientStop { position: 0.5; color: "#FDFDFF" }
            GradientStop { position: 1.0; color: "#FFE9F3" }
        }

        // 蓝光（左上→右中→左上，8s 单程）
        Rectangle {
            id: glowA
            width: Math.max(parent.width * 0.22, 220)
            height: width
            radius: width/2
            color: cBlue
            opacity: 0.24
            x: -width * 0.3
            y: parent.height * 0.15
            SequentialAnimation on x { loops: Animation.Infinite
                NumberAnimation { to: parent.width * 0.70; duration: 8000; easing.type: Easing.InOutSine }
                NumberAnimation { to: -glowA.width * 0.3;  duration: 8000; easing.type: Easing.InOutSine }
            }
            SequentialAnimation on opacity { loops: Animation.Infinite
                NumberAnimation { from: 0.16; to: 0.30; duration: 4200; easing.type: Easing.InOutSine }
                NumberAnimation { from: 0.30; to: 0.16; duration: 4200; easing.type: Easing.InOutSine }
            }
        }
        // 粉光（右下斜向来回，9s 单程）
        Rectangle {
            id: glowB
            width: Math.max(parent.width * 0.26, 260)
            height: width
            radius: width/2
            color: cPink
            opacity: 0.20
            x: parent.width * 0.65
            y: parent.height * 0.62
            ParallelAnimation on x { loops: Animation.Infinite
                NumberAnimation { to: parent.width * 0.12; duration: 9000; easing.type: Easing.InOutQuad }
                NumberAnimation { to: parent.width * 0.65; duration: 9000; easing.type: Easing.InOutQuad }
            }
            ParallelAnimation on y { loops: Animation.Infinite
                NumberAnimation { to: parent.height * 0.18; duration: 9000; easing.type: Easing.InOutQuad }
                NumberAnimation { to: parent.height * 0.62; duration: 9000; easing.type: Easing.InOutQuad }
            }
        }
        // 白光（中心小光点，6s 单程更灵动）
        Rectangle {
            id: glowC
            width: Math.max(parent.width * 0.16, 160)
            height: width
            radius: width/2
            color: "#FFFFFF"
            opacity: 0.12
            x: parent.width * 0.15
            y: parent.height * 0.55
            SequentialAnimation on x { loops: Animation.Infinite
                NumberAnimation { to: parent.width * 0.80; duration: 6000; easing.type: Easing.InOutSine }
                NumberAnimation { to: parent.width * 0.15; duration: 6000; easing.type: Easing.InOutSine }
            }
            SequentialAnimation on y { loops: Animation.Infinite
                NumberAnimation { to: parent.height * 0.25; duration: 6000; easing.type: Easing.InOutSine }
                NumberAnimation { to: parent.height * 0.55; duration: 6000; easing.type: Easing.InOutSine }
            }
        }
    }

    // ========== 中央玻璃面板 ==========
    Item {
        id: panel
        anchors.centerIn: parent
        width:  Math.min(profilePage.width  * 0.92, 1000)
        height: Math.min(profilePage.height * 0.88, 640)

        // 背景模糊 + 玻璃
        ShaderEffectSource { id: bgSrc; anchors.fill: parent; sourceItem: profilePage.contentItem; hideSource: false; live: true }
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

        // ====== 内容布局：左档案卡 / 右编辑表单 ======
        RowLayout {
            anchors.fill: parent
            anchors.margins: 26
            spacing: 20

            // ------ 左：档案卡 ------
            Rectangle {
                Layout.preferredWidth: panel.width * 0.34
                Layout.fillHeight: true
                radius: 18
                color: "#FFFFFFB0"
                border.color: cStroke

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 18
                    spacing: 14

                    // 头像（写死 png）
                    Item {
                        Layout.alignment: Qt.AlignHCenter
                        width: parent.width
                        height: Math.max(120, panel.height * 0.18)

                        Rectangle {
                            anchors.centerIn: parent
                            width: Math.min(panel.width * 0.20, 140)
                            height: width
                            radius: width/2
                            color: "#FFFFFF"
                            border.color: "#FFFFFF88"
                            layer.enabled: true
                            layer.effect: DropShadow {
                                horizontalOffset: 0; verticalOffset: 6
                                radius: 18; samples: 24; color: "#21000000"
                            }

                            // 头像图像
                            Image {
                                anchors.centerIn: parent
                                source: profilePage.avatarSrc
                                fillMode: Image.PreserveAspectCrop
                                width: parent.width * 0.92
                                height: width
                                smooth: true
                                clip: true
                            }
                        }
                    }

                    // 基本信息摘要（只读）
                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 6
                        Label { text: "姓名"; color: "#6B7B93"; font.pixelSize: 12 }
                        Label { text: profilePage.username || "未填写"; color: cText; font.bold: true }

                        Rectangle { height: 1; Layout.fillWidth: true; color: "#FFFFFF66"; Layout.topMargin: 8; Layout.bottomMargin: 8 }

                        Label { text: "电话"; color: "#6B7B93"; font.pixelSize: 12 }
                        Label { text: profilePage.phone || "未填写"; color: cText }

                        Label { text: "地址"; color: "#6B7B93"; font.pixelSize: 12; Layout.topMargin: 8 }
                        Label { text: profilePage.address || "未填写"; color: cText; wrapMode: Text.WordWrap }

                        Label { text: "年龄 / 性别"; color: "#6B7B93"; font.pixelSize: 12; Layout.topMargin: 8 }
                        Label { text: (profilePage.age || "—") + " / " + (profilePage.gender || "—"); color: cText }
                    }

                    Item { Layout.fillHeight: true }

                    // 左侧操作（与右侧按钮一致行为）
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        Button {
                            text: profilePage.editing ? "确认" : "修改"
                            Layout.fillWidth: true
                            enabled: !loading && (editing ? isInputValid() : true)
                            onClicked: confirmOrEdit()
                        }
                        Button {
                            text: profilePage.editing ? "取消" : "返回"
                            Layout.preferredWidth: 100
                            enabled: !loading
                            onClicked: cancelOrBack()
                        }
                    }
                }
            }

            // ------ 右：编辑表单 ------
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

                    // 顶部状态提示
                    Label {
                        text: infoHint
                        color: infoHint.indexOf("成功") >= 0 ? "#1B8A5A" : "#D62D30"
                        visible: infoHint !== ""
                        font.pixelSize: 12
                        horizontalAlignment: Text.AlignHCenter
                        Layout.fillWidth: true
                    }

                    // 姓名
                    RowLayout {
                        Layout.fillWidth: true; spacing: 10
                        Label { text: "姓名"; width: 64; horizontalAlignment: Text.AlignRight }
                        Loader {
                            Layout.fillWidth: true
                            active: !editing
                            sourceComponent: Label { text: profilePage.username }
                        }
                        Loader {
                            Layout.fillWidth: true
                            active: editing
                            sourceComponent: TextField {
                                text: profilePage.username
                                placeholderText: "请输入姓名"
                                onTextChanged: profilePage.username = text
                            }
                        }
                    }
                    // 电话
                    RowLayout {
                        Layout.fillWidth: true; spacing: 10
                        Label { text: "电话"; width: 64; horizontalAlignment: Text.AlignRight }
                        Loader {
                            Layout.fillWidth: true
                            active: !editing
                            sourceComponent: Label { text: profilePage.phone }
                        }
                        Loader {
                            Layout.fillWidth: true
                            active: editing
                            sourceComponent: TextField {
                                text: profilePage.phone
                                placeholderText: "请输入手机号"
                                inputMethodHints: Qt.ImhDigitsOnly
                                onTextChanged: profilePage.phone = text
                            }
                        }
                    }
                    // 地址
                    RowLayout {
                        Layout.fillWidth: true; spacing: 10
                        Label { text: "地址"; width: 64; horizontalAlignment: Text.AlignRight }
                        Loader {
                            Layout.fillWidth: true
                            active: !editing
                            sourceComponent: Label { text: profilePage.address; wrapMode: Text.WordWrap }
                        }
                        Loader {
                            Layout.fillWidth: true
                            active: editing
                            sourceComponent: TextField {
                                text: profilePage.address
                                placeholderText: "请输入地址"
                                onTextChanged: profilePage.address = text
                            }
                        }
                    }
                    // 年龄
                    RowLayout {
                        Layout.fillWidth: true; spacing: 10
                        Label { text: "年龄"; width: 64; horizontalAlignment: Text.AlignRight }
                        Loader {
                            Layout.fillWidth: true
                            active: !editing
                            sourceComponent: Label { text: profilePage.age }
                        }
                        Loader {
                            Layout.fillWidth: true
                            active: editing
                            sourceComponent: TextField {
                                text: profilePage.age
                                placeholderText: "请输入年龄"
                                inputMethodHints: Qt.ImhDigitsOnly
                                validator: IntValidator { bottom: 1; top: 120 }
                                onTextChanged: profilePage.age = text
                            }
                        }
                    }
                    // 性别
                    RowLayout {
                        Layout.fillWidth: true; spacing: 10
                        Label { text: "性别"; width: 64; horizontalAlignment: Text.AlignRight }
                        Loader {
                            Layout.fillWidth: true
                            active: !editing
                            sourceComponent: Label { text: profilePage.gender }
                        }
                        Loader {
                            Layout.fillWidth: true
                            active: editing
                            sourceComponent: ComboBox {
                                model: ["男", "女", "其他"]
                                currentIndex: profilePage.gender === "女" ? 1
                                              : (profilePage.gender === "其他" ? 2 : 0)
                                onCurrentIndexChanged: profilePage.gender = model[currentIndex]
                            }
                        }
                    }

                    Item { Layout.fillHeight: true }

                    // 操作（与左侧保持一致）
                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 12
                        Button {
                            text: editing ? "确认" : "修改"
                            enabled: !loading && (editing ? isInputValid() : true)
                            onClicked: confirmOrEdit()
                        }
                        Button {
                            text: editing ? "取消" : "返回"
                            enabled: !loading
                            onClicked: cancelOrBack()
                        }
                    }
                }
            }
        }

        // 保存/加载时遮罩
        Rectangle {
            visible: loading
            anchors.fill: parent
            color: "#AAFFFFFF"
            radius: 22
            BusyIndicator { anchors.centerIn: parent; running: loading }
        }
    }

    // ========== 生命周期：加载个人信息 ==========
    Component.onCompleted: {
        loading = true
        infoHint = "正在加载..."
        authManager.getPatientInfo(function(username, phone, address, age, gender) {
            loading = false
            if (username === undefined) {
                infoHint = "加载失败，请重试"
                return
            }
            infoHint = ""
            profilePage.username = username
            profilePage.phone = phone
            profilePage.address = address
            profilePage.age = age
            profilePage.gender = gender
            rawInfo = { username: username, phone: phone, address: address, age: age, gender: gender }
        })
    }

    // ========== 交互逻辑（保持原有语义） ==========
    function isInputValid() {
        if (!username || !phone || !address || !age || !gender) return false
        if (phone.length < 6 || phone.length > 20) return false
        var n = parseInt(age)
        if (isNaN(n) || n < 1 || n > 120) return false
        return true
    }

    function confirmOrEdit() {
        if (!editing) {
            editing = true; infoHint = ""
            return
        }
        if (!isInputValid()) {
            infoHint = "请填写完整且正确的信息"
            return
        }
        loading = true
        infoHint = "正在保存..."
        authManager.updatePatientInfo(username, phone, address, age, gender, function(success) {
            loading = false
            if (success) {
                editing = false
                rawInfo = { username: username, phone: phone, address: address, age: age, gender: gender }
                infoHint = "保存成功"
                Qt.createQmlObject('import QtQuick.Dialogs 1.2; MessageDialog { text: "保存成功"; visible: true }', profilePage)
            } else {
                infoHint = "保存失败，请重试"
                Qt.createQmlObject('import QtQuick.Dialogs 1.2; MessageDialog { text: "保存失败"; visible: true }', profilePage)
            }
        })
    }

    function cancelOrBack() {
        if (editing) {
            username = rawInfo.username
            phone    = rawInfo.phone
            address  = rawInfo.address
            age      = rawInfo.age
            gender   = rawInfo.gender
            editing  = false
            infoHint = ""
        } else {
            mainStackView.pop()
        }
    }
}

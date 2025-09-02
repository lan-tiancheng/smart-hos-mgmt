// DoctorListScreen.qml — 医生列表（玻璃拟态 · 蓝白粉主题 · Qt5 兼容）
// 逻辑保持不变：HTTP 获取 /api/doctors；点击“发起咨询”进入 PatientChatScreen

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Page {
    id: page
    title: qsTr("医生列表")
    focus: true   // 接收键盘事件（Esc/Back）

    // 从上个页面传入
    property string apiBase: "http://127.0.0.1:8080"
    property string token: ""
    property int patientId: -1
    property string patientName: "我"

    // 搜索与分页（分页占位，后端未实现总数）
    property string keyword: ""
    property int pageIndex: 1
    property int pageSize: 20
    property int total: 0

    function api(path) { return apiBase.replace(/\/+$/, "") + path }
    ListModel { id: doctorModel }

    // 主题色（与登录/聊天页一致）
    readonly property color cBlue:  "#5AA9FF"
    readonly property color cPink:  "#FF9AC2"
    readonly property color cText:  "#0F1B2D"
    readonly property color cGlass: "#FFFFFFCC"
    readonly property color cStroke:"#FFFFFF66"

    function goBack() {
        // 1) 当前 Page 所在的 StackView（最可靠）
        if (page.StackView && page.StackView.view) {
            page.StackView.view.pop(page)
            return
        }
        // 2) 全局主 StackView
        if (typeof mainStackView !== "undefined" && mainStackView && mainStackView.pop) {
            mainStackView.pop()
            return
        }
        // 3) 向上查找最近的 StackView（兜底）
        var p = page.parent
        while (p) {
            if (p.pop && p.push) { p.pop(); return }
            p = p.parent
        }
        console.log("goBack: no StackView found")
    }

    // 支持 Android 返回键或 Esc
    Keys.onReleased: {
        if (event.key === Qt.Key_Back || event.key === Qt.Key_Escape) {
            page.goBack()
            event.accepted = true
        }
    }

    // 顶部返回按钮（标准 ToolBar）
    header: ToolBar {
        contentItem: RowLayout {
            anchors.fill: parent
            spacing: 8
            ToolButton {
                text: qsTr("返回")
                onClicked: page.goBack()
            }
            Label {
                text: page.title
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }
            // 占位，保持标题居中
            Item { width: 48; height: 1 }
        }
    }

    function loadDoctors(resetPage) {
        if (resetPage) pageIndex = 1
        const url = api("/api/doctors?q=" + encodeURIComponent(keyword || ""))
        const xhr = new XMLHttpRequest()
        xhr.open("GET", url)
        if (token) xhr.setRequestHeader("Authorization", "Bearer " + token)
        xhr.timeout = 10000
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status >= 200 && xhr.status < 300) {
                    try {
                        const res = JSON.parse(xhr.responseText || "{}")
                        if (res && res.success) {
                            doctorModel.clear()
                            const arr = Array.isArray(res.doctors) ? res.doctors : []
                            for (let i = 0; i < arr.length; i++) {
                                const d = arr[i] || {}
                                doctorModel.append({
                                    id: d.id || 0,
                                    name: d.username || "",
                                    gender: d.gender || "",
                                    phone: d.phone || "",
                                    address: d.address || "",
                                    age: d.age || 0,
                                    department: d.department || "",
                                    title: d.title || "",
                                    hospital: d.hospital || ""
                                })
                            }
                        } else {
                            console.log("加载医生失败:", xhr.responseText)
                            toast.show(qsTr("加载医生失败"), true)
                        }
                    } catch (e) {
                        console.log("解析失败:", e, xhr.responseText)
                        toast.show(qsTr("数据解析失败"), true)
                    }
                } else {
                    console.log("HTTP 错误:", xhr.status)
                    toast.show(qsTr("网络错误：") + xhr.status, true)
                }
            }
        }
        xhr.ontimeout = function() { console.log("请求超时"); toast.show(qsTr("请求超时"), true) }
        xhr.send()
    }

    // ===== 背景：柔和渐变 + 两个柔光圆 =====
    Rectangle {
        id: bg
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#E6F2FF" }
            GradientStop { position: 0.5; color: "#FDFDFF" }
            GradientStop { position: 1.0; color: "#FFE9F3" }
        }

        // 蓝色柔光圆
        Rectangle {
            id: glow1
            width: Math.max(220, bg.width * 0.22); height: width; radius: width / 2
            color: cBlue; opacity: 0.22
            y: bg.height * 0.22; x: -width * 0.3
            SequentialAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: bg.width - glow1.width * 0.7; duration: 8500; easing.type: Easing.InOutSine }
                NumberAnimation { to: -glow1.width * 0.3; duration: 8500; easing.type: Easing.InOutSine }
            }
        }

        // 粉色柔光圆
        Rectangle {
            id: glow2
            width: Math.max(260, bg.width * 0.26); height: width; radius: width / 2
            color: cPink; opacity: 0.18
            x: bg.width * 0.68; y: bg.height * 0.62
            ParallelAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: bg.width * 0.15; duration: 9500; easing.type: Easing.InOutQuad }
                NumberAnimation { to: bg.width * 0.68; duration: 9500; easing.type: Easing.InOutQuad }
            }
            ParallelAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { to: bg.height * 0.18; duration: 9500; easing.type: Easing.InOutQuad }
                NumberAnimation { to: bg.height * 0.62; duration: 9500; easing.type: Easing.InOutQuad }
            }
        }
    }

    // ===== 居中玻璃卡容器 =====
    Item {
        id: panel
        width: Math.min(page.width * 0.94, 980)
        height: Math.min(page.height * 0.92, 680)
        anchors.centerIn: parent

        // 背景模糊 + 玻璃面板
        ShaderEffectSource { id: bgSrc; anchors.fill: parent; sourceItem: bg; hideSource: false; live: true }
        FastBlur { anchors.fill: parent; source: bgSrc; radius: 28 }
        Rectangle { id: glass; anchors.fill: parent; color: cGlass; radius: 22; border.color: cStroke; border.width: 1 }
        DropShadow { anchors.fill: glass; source: glass; radius: 26; samples: 32; horizontalOffset: 0; verticalOffset: 14; color: "#33000000" }

        // ===== 内容 =====
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 18
            spacing: 12

            // 顶部栏：标题 + 搜索（返回按钮在 ToolBar）
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Label {
                    text: qsTr("医生列表")
                    font.pixelSize: 22; font.bold: true; color: cText
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignVCenter
                }

                Item { Layout.fillWidth: true }

                // 搜索胶囊
                Rectangle {
                    id: searchPill
                    radius: 16
                    color: "#FFFFFFE6"
                    border.color: cStroke
                    height: 36
                    width: Math.min(panel.width * 0.48, 420)

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 6
                        spacing: 6
                        TextField {
                            id: searchField
                            Layout.fillWidth: true
                            placeholderText: qsTr("输入医生姓名/科室/职称/医院/电话/地址")
                            text: page.keyword
                            background: Item {}
                            onTextChanged: page.keyword = text
                            onAccepted: searchButton.clicked()
                        }
                        Button {
                            id: searchButton
                            text: qsTr("搜索")
                            onClicked: loadDoctors(true)
                            contentItem: Label { text: searchButton.text; color: "#fff"; font.bold: true; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                            background: Rectangle { radius: 10; color: cBlue; border.color: "transparent" }
                        }
                    }
                }
            }

            // 列表容器（半透明玻璃）
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 16
                color: "#FFFFFFB8"
                border.color: cStroke

                // 空态
                Label {
                    visible: doctorModel.count === 0
                    anchors.centerIn: parent
                    text: qsTr("暂无医生数据")
                    color: "#7A8AA0"
                }

                // 列表
                ListView {
                    id: listView
                    anchors.fill: parent
                    anchors.margins: 12
                    clip: true
                    spacing: 8
                    model: doctorModel

                    delegate: ItemDelegate {
                        id: row
                        width: listView.width
                        padding: 10
                        hoverEnabled: true

                        background: Rectangle {
                            radius: 12
                            color: control.down ? "#EEF5FF" : "#FFFFFF"
                            border.color: "#E8ECF3"
                            border.width: 1
                        }

                        contentItem: RowLayout {
                            spacing: 12
                            width: parent.width - row.leftPadding - row.rightPadding

                            // 左：头像圆（首字）
                            Rectangle {
                                width: 44; height: 44; radius: 22
                                color: "#E6F0FF"
                                border.color: "#BBD3FF"
                                Layout.alignment: Qt.AlignVCenter
                                Label {
                                    anchors.centerIn: parent
                                    text: (name && name.length > 0) ? name.charAt(0) : qsTr("医")
                                    color: "#3366CC"; font.bold: true
                                }
                            }

                            // 中：信息
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 4

                                // 姓名 + 标签
                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 6
                                    Label {
                                        text: name || qsTr("未命名")
                                        font.pixelSize: 16; font.bold: true; color: cText
                                        elide: Text.ElideRight
                                        Layout.fillWidth: true
                                    }

                                    // 简单标签（科室）
                                    Rectangle {
                                        visible: !!department && department.length > 0
                                        radius: 10; color: "#E9F6FF"; border.color: "#CBE6FF"
                                        height: 20
                                        Label { anchors.centerIn: parent; text: department; color: "#1F7AE0"; font.pixelSize: 11 }
                                    }
                                    // 职称
                                    Rectangle {
                                        visible: !!title && title.length > 0
                                        radius: 10; color: "#E9FFF4"; border.color: "#C6F1DC"
                                        height: 20
                                        Label { anchors.centerIn: parent; text: title; color: "#2D8A5F"; font.pixelSize: 11 }
                                    }
                                    // 年龄
                                    Rectangle {
                                        visible: age > 0
                                        radius: 10; color: "#FFF7E8"; border.color: "#FFE2B8"
                                        height: 20
                                        Label { anchors.centerIn: parent; text: qsTr("年龄 %1").arg(age); color: "#B07A2A"; font.pixelSize: 11 }
                                    }
                                }

                                // 医院
                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 6
                                    Label {
                                        text: hospital || ""
                                        color: "#55657A"
                                        elide: Text.ElideRight
                                        Layout.fillWidth: true
                                    }
                                }

                                // 电话 + 地址
                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 6
                                    Label {
                                        text: phone ? (qsTr("电话：") + phone) : ""
                                        color: "#39485C"
                                        elide: Text.ElideRight
                                        Layout.fillWidth: true
                                    }
                                    Label {
                                        text: address || ""
                                        color: "#6B7B93"
                                        elide: Text.ElideRight
                                        Layout.fillWidth: true
                                    }
                                }
                            }

                            // 右：按钮
                            Button {
                                id: consultBtn
                                text: qsTr("发起咨询")
                                enabled: (id || 0) > 0 && (page.patientId || 0) > 0
                                onClicked: {
                                    if ((page.patientId || 0) <= 0) {
                                        console.log("缺少 patientId，无法发起咨询")
                                        toast.show(qsTr("缺少患者身份，无法发起咨询"), true)
                                        return
                                    }
                                    const params = {
                                        apiBase: page.apiBase,
                                        token: page.token,
                                        patientId: page.patientId,
                                        patientName: page.patientName,
                                        doctorId: id,
                                        doctorName: name
                                    }
                                    if (typeof mainStackView !== "undefined" && mainStackView.push) {
                                        mainStackView.push("qrc:/client/qml/qml/PatientChatScreen.qml", params)
                                    } else if (StackView.view) {
                                        StackView.view.push("qrc:/client/qml/qml/PatientChatScreen.qml", params)
                                    }
                                }
                                contentItem: Label {
                                    text: consultBtn.text
                                    color: "#fff"
                                    font.bold: true
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }
                                background: Rectangle {
                                    radius: 12
                                    color: consultBtn.enabled ? cPink : "#F6BFD4"
                                    border.color: "transparent"
                                }
                            }
                        }
                    }

                    ScrollBar.vertical: ScrollBar {}
                }
            }
        }
    }

    // 顶部 Toast（与登录页风格一致）
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

    Component.onCompleted: loadDoctors(true)
}

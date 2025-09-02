// DoctorConversationListScreen.qml — Qt5 兼容 · 轻玻璃拟态（蓝白粉）
// 逻辑保持：请求 /api/chat/doctor/conversations，点击进入 DoctorChatScreen
// 新增：渐变背景+玻璃卡、顶部返回/刷新、搜索过滤、本地高亮

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.12

Page {
    id: page
    title: qsTr("会话列表（医生端）")
    focus: true

    // 允许外部 push 传入
    property string apiBase: "http://127.0.0.1:8080"
    property string wsUrl: ""
    property string token: ""
    property int doctorId: -1
    property string doctorName: ""

    // 主题与尺寸
    readonly property color cBlue:  "#5AA9FF"
    readonly property color cPink:  "#FF9AC2"
    readonly property color cText:  "#0F1B2D"
    readonly property color cGlass: "#FFFFFFCC"
    readonly property color cStroke:"#FFFFFF66"

    // 搜索关键字（本地过滤）
    property string searchKeyword: ""

    function api(path) { return apiBase.replace(/\/+$/, "") + path }
    function ensureWs() {
        if (!wsUrl || wsUrl.length === 0) {
            const base = apiBase.replace(/\/+$/, "")
            wsUrl = base.replace(/^http(s?):/, "ws$1:") + "/ws/chat"
        }
    }
    function toInt(v) { var n = parseInt(v, 10); return isNaN(n) ? -1 : n }

    function goBack() {
        if (page.StackView && page.StackView.view) { page.StackView.view.pop(page); return }
        if (typeof mainStackView !== "undefined" && mainStackView.pop) { mainStackView.pop(); return }
        var p = page.parent
        while (p) { if (p.pop && p.push) { p.pop(); return } p = p.parent }
        console.log("No StackView to pop.")
    }

    Keys.onReleased: {
        if (event.key === Qt.Key_Back || event.key === Qt.Key_Escape) {
            page.goBack()
            event.accepted = true
        }
    }

    header: ToolBar {
        contentItem: RowLayout {
            anchors.fill: parent
            spacing: 8
            ToolButton { text: qsTr("返回"); onClicked: page.goBack() }
            Label {
                text: page.title
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }
            ToolButton { text: qsTr("刷新"); onClicked: loadConversations() }
        }
    }

    // 可点击的数据模型
    ListModel { id: convModel }

    // 从全局会话兜底（如果未传 doctorId）
    function inferFromSession() {
        var sess = (typeof appSession !== "undefined") ? appSession : ({})
        if (doctorId <= 0) {
            var t = (sess.userType || sess.user_type || "").toString().toLowerCase()
            var uid = toInt(sess.userId || sess.user_id || -1)
            if (t === "doctor" && uid > 0) doctorId = uid
        }
        if (!doctorName || doctorName.length === 0) {
            doctorName = (sess.userName || sess.username || (doctorId > 0 ? ("医生#" + doctorId) : "医生"))
        }
        if (!apiBase || apiBase.length === 0) apiBase = (sess.apiBase || "http://127.0.0.1:8080")
        if (!token || token.length === 0) token = (sess.token || "")
        ensureWs()
    }

    function loadConversations() {
        doctorId = toInt(doctorId)
        if (doctorId <= 0) {
            console.log("DoctorConversationListScreen: doctorId 缺失或当前用户不是医生")
            return
        }
        const url = api("/api/chat/doctor/conversations?doctorId=" + doctorId + "&limit=100&offset=0")
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
                            convModel.clear()
                            const arr = Array.isArray(res.conversations) ? res.conversations : []
                            for (let i = 0; i < arr.length; i++) {
                                const c = arr[i] || {}
                                convModel.append({
                                    conversationId: c.id || c.conversationId || 0,
                                    patientId: c.patient_id || c.patientId || 0,
                                    patientName: c.patient_name || c.patientName || "",
                                    lastMessage: c.last_message || c.lastMessage || "",
                                    lastAt: c.last_at || c.lastAt || ""
                                })
                            }
                        } else {
                            console.log("加载会话失败:", xhr.responseText)
                        }
                    } catch (e) {
                        console.log("解析失败:", e, xhr.responseText)
                    }
                } else {
                    console.log("HTTP 错误:", xhr.status)
                }
            }
        }
        xhr.ontimeout = function() { console.log("请求超时") }
        xhr.send()
    }

    // ============ 背景：柔和渐变 + 两个柔光圆 ============
    Rectangle {
        id: bg
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#E6F2FF" }
            GradientStop { position: 0.5; color: "#FDFDFF" }
            GradientStop { position: 1.0; color: "#FFE9F3" }
        }

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
        width: Math.min(page.width * 0.94, 980)
        height: Math.min(page.height * 0.92, 680)

        // 背景模糊 + 玻璃
        ShaderEffectSource { id: bgSrc; anchors.fill: parent; sourceItem: bg; hideSource: false; live: true }
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
            anchors.margins: 18
            spacing: 12

            // 顶部信息 + 搜索
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                ColumnLayout {
                    Layout.fillWidth: true
                    Label {
                        text: qsTr("会话列表")
                        color: cText
                        font.pixelSize: 22
                        font.bold: true
                    }
                    Label {
                        text: qsTr("医生：%1").arg(doctorName || (doctorId > 0 ? ("#" + doctorId) : qsTr("未登录")))
                        color: "#5C6C80"
                        font.pixelSize: 12
                    }
                }

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
                            placeholderText: qsTr("按患者姓名/最后消息搜索（本地过滤）")
                            text: page.searchKeyword
                            background: Item {}
                            onTextChanged: page.searchKeyword = text
                            onAccepted: refreshBtn.clicked()
                        }
                        Button {
                            id: refreshBtn
                            text: qsTr("刷新")
                            onClicked: loadConversations()
                            contentItem: Label { text: refreshBtn.text; color: "#fff"; font.bold: true; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter }
                            background: Rectangle { radius: 10; color: cBlue; border.color: "transparent" }
                        }
                    }
                }
            }

            // 列表容器
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 16
                color: "#FFFFFFB8"
                border.color: cStroke

                // 空态提示
                Label {
                    visible: convModel.count === 0
                    anchors.centerIn: parent
                    text: qsTr("暂无会话记录")
                    color: "#7A8AA0"
                }

                ListView {
                    id: listView
                    anchors.fill: parent
                    anchors.margins: 12
                    clip: true
                    spacing: 8
                    model: convModel

                    delegate: ItemDelegate {
                        id: row
                        width: listView.width
                        padding: 10
                        hoverEnabled: true

                        // 本地搜索匹配
                        property string kw: (page.searchKeyword || "").toLowerCase()
                        property bool matchName: (patientName || "").toLowerCase().indexOf(kw) >= 0
                        property bool matchMsg: (lastMessage || "").toLowerCase().indexOf(kw) >= 0
                        visible: (kw.length === 0) ? true : (matchName || matchMsg)
                        height: visible ? implicitHeight : 0

                        onClicked: {
                            const params = {
                                apiBase: page.apiBase,
                                token: page.token,
                                wsUrl: page.wsUrl,
                                conversationId: conversationId,
                                doctorId: page.doctorId,
                                doctorName: page.doctorName,
                                patientId: patientId,
                                patientName: patientName
                            }
                            if (typeof mainStackView !== "undefined" && mainStackView.push) {
                                mainStackView.push("qrc:/client/qml/qml/DoctorChatScreen.qml", params)
                            } else if (StackView.view) {
                                StackView.view.push("qrc:/client/qml/qml/DoctorChatScreen.qml", params)
                            } else {
                                console.log("No StackView to navigate.")
                            }
                        }

                        background: Rectangle {
                            radius: 12
                            color: control.down ? "#EEF5FF" : (row.hovered ? "#FAFDFF" : "#FFFFFF")
                            border.color: "#E8ECF3"
                            border.width: 1
                        }

                        contentItem: RowLayout {
                            id: contentCol
                            spacing: 10
                            width: parent.width - row.leftPadding - row.rightPadding

                            Rectangle {
                                width: 44; height: 44; radius: 22
                                color: "#E6F0FF"
                                border.color: "#BBD3FF"
                                Layout.alignment: Qt.AlignVCenter
                                Label {
                                    anchors.centerIn: parent
                                    text: (patientName && patientName.length > 0) ? patientName.charAt(0) : "患"
                                    color: "#3366CC"; font.bold: true
                                }
                            }

                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 4

                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 6
                                    Label {
                                        text: (patientName && patientName.length > 0) ? patientName : (qsTr("患者#") + patientId)
                                        font.pixelSize: 16; font.bold: true
                                        elide: Text.ElideRight
                                        Layout.fillWidth: true
                                        color: cText
                                    }
                                    Label {
                                        text: lastAt || ""
                                        color: "#8A97AA"
                                        font.pixelSize: 12
                                        horizontalAlignment: Text.AlignRight
                                    }
                                }

                                Label {
                                    text: lastMessage && lastMessage.length > 0 ? lastMessage : qsTr("暂无消息")
                                    color: "#39485C"
                                    elide: Text.ElideRight
                                }
                            }

                            Label {
                                text: "›"
                                color: "#AAB7CC"
                                font.pixelSize: 20
                                Layout.alignment: Qt.AlignVCenter
                            }
                        }
                    }

                    ScrollBar.vertical: ScrollBar {}
                }
            }
        }
    }

    Component.onCompleted: {
        console.log("DoctorConversationListScreen init => apiBase:", apiBase, " wsUrl:", wsUrl, " doctorId:", doctorId, " doctorName:", doctorName)
        inferFromSession()
        ensureWs()
        loadConversations()
    }
}

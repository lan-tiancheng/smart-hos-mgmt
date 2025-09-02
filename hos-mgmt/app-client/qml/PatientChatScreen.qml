// PatientChatScreen.qml — Qt5 兼容玻璃拟态风格（蓝白粉主题）
// 仿照医生聊天页面：右侧显示“患者本人”消息（微信风格气泡）
// 关键点：isSelf 兼容 sender_role/senderRole 与 sender_id/senderId，并做类型转换，避免误判
// 逻辑保持：WS 优先发送，HTTP 回退；进入自动 join 会话并加载历史；带返回按钮与状态胶囊

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12
import QtWebSockets 1.1

Page {
    id: page
    title: qsTr("患者聊天")

    // 外部传入
    property string apiBase: "http://127.0.0.1:8080"
    property string wsUrl: ""        // 若为空，会自动从 apiBase 推导
    property string token: ""
    property int conversationId: -1
    property int patientId: -1
    property string patientName: ""
    property int doctorId: -1
    property string doctorName: ""

    // 自身 ID（用于判断消息左右气泡）
    property int selfId: (patientId > 0 ? patientId : -1)

    // 主题色
    readonly property color cBlue:  "#5AA9FF"
    readonly property color cPink:  "#FF9AC2"
    readonly property color cText:  "#0F1B2D"
    readonly property color cGlass: "#FFFFFFCC"
    readonly property color cStroke:"#FFFFFF66"

    // 微信气泡配色
    readonly property color cWeChatGreen: "#95EC69"   // 患者本人（右侧）
    readonly property color cGreenBorder: "#83D95A"
    readonly property color cLeftBubble:  "#FFFFFF"   // 医生（左侧）
    readonly property color cLeftBorder:  "#E8ECF3"

    function goBack() {
        if (typeof mainStackView !== "undefined" && mainStackView.pop) {
            mainStackView.pop()
        } else if (StackView.view) {
            StackView.view.pop()
        } else {
            console.log("No StackView to pop.")
        }
    }

    function makeApi(path) { return apiBase.replace(/\/+$/, "") + path }
    function ensureWs() {
        if (!wsUrl || wsUrl.length === 0) {
            var base = apiBase.replace(/\/+$/, "")
            var wsBase = base.replace(/^http(s?):/, "ws$1:")
            wsUrl = wsBase + "/ws/chat"
            console.log("chat wsUrl inferred:", wsUrl)
        }
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

        // 柔光圆 1
        Rectangle {
            id: glow1
            width: Math.max(220, bg.width * 0.22); height: width; radius: width / 2
            color: cBlue; opacity: 0.22
            y: bg.height * 0.25; x: -width * 0.3
            SequentialAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: bg.width - glow1.width * 0.7; duration: 8000; easing.type: Easing.InOutSine }
                NumberAnimation { to: -glow1.width * 0.3; duration: 8000; easing.type: Easing.InOutSine }
            }
            SequentialAnimation on opacity {
                loops: Animation.Infinite
                NumberAnimation { from: 0.14; to: 0.28; duration: 4500; easing.type: Easing.InOutSine }
                NumberAnimation { from: 0.28; to: 0.14; duration: 4500; easing.type: Easing.InOutSine }
            }
        }

        // 柔光圆 2
        Rectangle {
            id: glow2
            width: Math.max(260, bg.width * 0.26); height: width; radius: width / 2
            color: cPink; opacity: 0.18
            x: bg.width * 0.65; y: bg.height * 0.60
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

    // ===== 居中玻璃聊天卡片 =====
    Item {
        id: panel
        width: Math.min(page.width * 0.94, 980)
        height: Math.min(page.height * 0.92, 640)
        anchors.centerIn: parent

        ShaderEffectSource { id: bgSrc; anchors.fill: parent; sourceItem: bg; hideSource: false; live: true }
        FastBlur { anchors.fill: parent; source: bgSrc; radius: 28 }

        Rectangle { id: glass; anchors.fill: parent; color: cGlass; radius: 22; border.color: cStroke; border.width: 1 }
        DropShadow {
            anchors.fill: glass; source: glass
            radius: 26; samples: 32; horizontalOffset: 0; verticalOffset: 14
            color: "#33000000"
        }

        // ===== 聊天内容 =====
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 18
            spacing: 10

            // 顶部栏：返回 + 对话对象 + 实时状态
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Button {
                    id: backBtn
                    text: qsTr("返回")
                    onClicked: page.goBack()
                    background: Rectangle { radius: 10; color: "#FFFFFFA0"; border.color: cStroke }
                }

                Label {
                    text: doctorName && doctorName.length > 0 ? doctorName : ("医生#" + page.doctorId)
                    font.pixelSize: 20; font.bold: true; color: cText
                    Layout.alignment: Qt.AlignVCenter
                }
                Item { Layout.fillWidth: true }

                // 实时连接状态胶囊
                Rectangle {
                    radius: 12
                    color: (chatSocket.status === WebSocket.Open ? "#D7FAD7" : "#FFE1E1")
                    border.color: (chatSocket.status === WebSocket.Open ? "#6AC76A" : "#E06666")
                    border.width: 1
                    height: 26
                    width: 110
                    Row {
                        anchors.centerIn: parent; spacing: 6
                        Rectangle {
                            width: 8; height: 8; radius: 4
                            color: (chatSocket.status === WebSocket.Open ? "#33B249" : "#E06666")
                        }
                        Label {
                            text: (chatSocket.status === WebSocket.Open ? qsTr("实时已连接") : qsTr("实时未连接"))
                            color: "#333"; font.pixelSize: 12
                        }
                    }
                }
            }

            // 聊天列表玻璃容器
            Rectangle {
                id: chatGlass
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 16
                color: "#FFFFFFB8"
                border.color: cStroke

                // 列表
                ListView {
                    id: listView
                    anchors.fill: parent
                    anchors.margins: 12
                    clip: true
                    spacing: 8
                    model: messageModel

                    delegate: Column {
                        width: listView.width

                        // 是否患者本人（健壮判断）
                        function asRole(v) { return (v || "").toString().toLowerCase() }
                        function asInt(v)  { var n = parseInt(v, 10); return isNaN(n) ? -1 : n }
                        property string roleStr: (senderRole !== undefined ? senderRole : sender_role)
                        property var sidRaw: (senderId !== undefined ? senderId : sender_id)
                        property bool isSelf: asRole(roleStr) === "patient" &&
                                              asInt(sidRaw) === asInt(page.selfId > 0 ? page.selfId : page.patientId)

                        property real bubbleMaxWidth: Math.round(listView.width * 0.70)
                        property int avatarSize: 32
                        property int bubbleHPad: 10
                        property int bubbleVPad: 8

                        // 使用 RowLayout + 左右占位，将本端气泡推到右侧
                        RowLayout {
                            width: parent.width
                            spacing: 8

                            // 左占位：如果是本人发送，则填充把气泡推到右侧
                            Item { Layout.fillWidth: isSelf }

                            // 左侧（医生）头像
                            Rectangle {
                                visible: !isSelf
                                width: avatarSize; height: avatarSize; radius: avatarSize/2
                                color: "#E6F0FF"
                                border.color: "#BBD3FF"
                                Layout.alignment: Qt.AlignVCenter
                                Label {
                                    anchors.centerIn: parent
                                    text: (page.doctorName && page.doctorName.length > 0) ? page.doctorName.charAt(0) : "医"
                                    color: "#3366CC"; font.bold: true
                                }
                            }

                            // 气泡
                            Rectangle {
                                radius: 10
                                color: isSelf ? cWeChatGreen : cLeftBubble
                                border.color: isSelf ? cGreenBorder : cLeftBorder
                                border.width: 1
                                Layout.alignment: Qt.AlignVCenter

                                // 计算内容宽度，确保自动换行且不超过最大宽度
                                property int contentWidth: Math.min(bubbleMaxWidth - bubbleHPad*2,
                                                                    Math.max(20, contentText.implicitWidth))
                                width: contentWidth + bubbleHPad*2
                                height: contentText.implicitHeight + bubbleVPad*2

                                Text {
                                    id: contentText
                                    text: content || ""
                                    wrapMode: Text.WordWrap
                                    width: parent.contentWidth
                                    anchors.fill: parent
                                    anchors.leftMargin: bubbleHPad
                                    anchors.rightMargin: bubbleHPad
                                    anchors.topMargin: bubbleVPad
                                    anchors.bottomMargin: bubbleVPad
                                    color: isSelf ? "#111" : "#222"
                                }
                            }

                            // 右侧（患者本人）头像
                            Rectangle {
                                visible: isSelf
                                width: avatarSize; height: avatarSize; radius: avatarSize/2
                                color: "#E9FFD9"
                                border.color: "#B7F19B"
                                Layout.alignment: Qt.AlignVCenter
                                Label {
                                    anchors.centerIn: parent
                                    text: (page.patientName && page.patientName.length > 0) ? page.patientName.charAt(0) : "我"
                                    color: "#2E7D32"; font.bold: true
                                }
                            }

                            // 右占位：对方消息占位把气泡维持在左边
                            Item { Layout.fillWidth: !isSelf }
                        }

                        // 时间戳（灰色小字）
                        Label {
                            text: createdAt || ""
                            color: "#7A8AA0"
                            font.pixelSize: 10
                            horizontalAlignment: isSelf ? Text.AlignRight : Text.AlignLeft
                            width: parent.width
                            leftPadding: isSelf ? 0 : 12
                            rightPadding: isSelf ? 12 : 0
                        }
                    }

                    ScrollBar.vertical: ScrollBar {}
                }
            }

            // 输入栏（半透明）
            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Rectangle {
                    id: inputWrap
                    Layout.fillWidth: true
                    radius: 12
                    color: "#FFFFFFE6"
                    border.color: cStroke
                    height: Math.max(40, inputField.implicitHeight + 12)

                    TextField {
                        id: inputField
                        anchors.fill: parent
                        anchors.margins: 8
                        placeholderText: qsTr("输入消息…")
                        background: Item {}
                        onAccepted: {
                            sendMessage(text)
                            text = ""
                        }
                    }
                }

                Button {
                    id: sendBtn
                    text: sending ? qsTr("发送中…") : qsTr("发送")
                    enabled: !sending && inputField.text.trim().length > 0
                    onClicked: {
                        sendMessage(inputField.text)
                        inputField.text = ""
                    }
                    contentItem: Label {
                        text: sendBtn.text
                        color: "#fff"
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 12
                        color: sendBtn.enabled ? cBlue : "#A9CFFF"
                        border.color: "transparent"
                    }
                }
            }
        }
    }

    // ===== 数据与通信逻辑（与医生页一致） =====
    ListModel { id: messageModel }

    function ensureConversation(cb) {
        if (conversationId > 0) { if (cb) cb(true); return }
        if ((patientId || 0) <= 0 || (doctorId || 0) <= 0) {
            console.log("PatientChatScreen: 缺少参数，无法创建会话")
            if (cb) cb(false)
            return
        }
        const url = makeApi("/api/chat/conversation")
        const xhr = new XMLHttpRequest()
        xhr.open("POST", url)
        xhr.setRequestHeader("Content-Type", "application/json")
        if (token) xhr.setRequestHeader("Authorization", "Bearer " + token)
        xhr.timeout = 10000
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                try {
                    const res = JSON.parse(xhr.responseText || "{}")
                    if (xhr.status >= 200 && xhr.status < 300 && res && res.success) {
                        conversationId = parseInt(res.conversationId || -1)
                        if (cb) cb(true)
                    } else {
                        console.log("create/get conversation failed:", xhr.status, xhr.responseText)
                        if (cb) cb(false)
                    }
                } catch (e) {
                    console.log("create/get conversation parse error:", e, xhr.responseText)
                    if (cb) cb(false)
                }
            }
        }
        xhr.ontimeout = function() { console.log("create/get conversation timeout") }
        xhr.send(JSON.stringify({ patientId: patientId, doctorId: doctorId }))
    }

    function loadHistory() {
        if (conversationId <= 0) return
        const url = makeApi("/api/chat/messages?conversationId=" + conversationId + "&limit=200")
        const xhr = new XMLHttpRequest()
        xhr.open("GET", url)
        if (token) xhr.setRequestHeader("Authorization", "Bearer " + token)
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                if (xhr.status >= 200 && xhr.status < 300) {
                    try {
                        const res = JSON.parse(xhr.responseText || "{}")
                        if (res && res.success) {
                            messageModel.clear()
                            const arr = Array.isArray(res.messages) ? res.messages : []
                            for (let i = 0; i < arr.length; i++) {
                                const m = arr[i] || {}
                                messageModel.append({
                                    senderId: m.sender_id !== undefined ? m.sender_id : (m.senderId || 0),
                                    senderRole: m.sender_role !== undefined ? m.sender_role : (m.senderRole || ""),
                                    content: m.content || "",
                                    createdAt: m.created_at !== undefined ? m.created_at : (m.createdAt || "")
                                })
                            }
                            Qt.callLater(function(){ listView.positionViewAtEnd() })
                        }
                    } catch (e) {
                        console.log("parse history error:", e, xhr.responseText)
                    }
                } else {
                    console.log("history http error:", xhr.status)
                }
            }
        }
        xhr.send()
    }

    WebSocket {
        id: chatSocket
        active: false
        url: page.wsUrl

        onStatusChanged: {
            if (status === WebSocket.Open) {
                console.log("ws open, join room:", page.conversationId)
                sendTextMessage(JSON.stringify({ type: "join", conversationId: page.conversationId }))
            } else if (status === WebSocket.Error) {
                console.log("ws error:", errorString)
            }
        }

        onTextMessageReceived: function(message) {
            try {
                const data = JSON.parse(message)
                if (data.type === "message" && data.conversationId === page.conversationId) {
                    const m = data.message || {}
                    messageModel.append({
                        senderId: m.sender_id !== undefined ? m.sender_id : (m.senderId || 0),
                        senderRole: m.sender_role !== undefined ? m.sender_role : (m.senderRole || ""),
                        content: m.content || "",
                        createdAt: m.created_at !== undefined ? m.created_at : (m.createdAt || "")
                    })
                    Qt.callLater(function(){ listView.positionViewAtEnd() })
                }
            } catch (e) {
                console.log("ws parse error:", e, message)
            }
        }
        // 注意：QtWebSockets 没有 onErrorChanged，部分版本支持 errorString 属性变化
        onErrorStringChanged: {
            if (errorString && errorString.length) console.log("ws error:", errorString)
        }
    }

    function connectSocket() {
        ensureWs()
        if (conversationId <= 0) return
        chatSocket.url = wsUrl
        chatSocket.active = true
    }

    // 发送
    property bool sending: false

    function sendViaWs(text) {
        if (chatSocket.status !== WebSocket.Open) return false
        chatSocket.sendTextMessage(JSON.stringify({
            type: "send",
            senderId: (selfId > 0 ? selfId : patientId),
            senderRole: "patient",
            content: text.trim()
        }))
        return true
    }

    function sendViaHttp(text, ondone) {
        const url = makeApi("/api/chat/send")
        const xhr = new XMLHttpRequest()
        xhr.open("POST", url)
        xhr.setRequestHeader("Content-Type", "application/json")
        if (token) xhr.setRequestHeader("Authorization", "Bearer " + token)
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                let ok = false, msg = null
                try {
                    const res = JSON.parse(xhr.responseText || "{}")
                    ok = (xhr.status >= 200 && xhr.status < 300 && res && res.success)
                    msg = res && res.message ? res.message : null
                } catch (e) {}
                if (!ok && !msg) {
                    // 失败时本地追加，避免用户以为没发出
                    messageModel.append({
                        senderId: (selfId > 0 ? selfId : patientId),
                        senderRole: "patient",
                        content: text.trim(),
                        createdAt: new Date().toISOString()
                    })
                    Qt.callLater(function(){ listView.positionViewAtEnd() })
                } else if (msg) {
                    messageModel.append({
                        senderId: msg.sender_id !== undefined ? msg.sender_id : (msg.senderId || (selfId > 0 ? selfId : patientId)),
                        senderRole: msg.sender_role !== undefined ? msg.sender_role : (msg.senderRole || "patient"),
                        content: msg.content || text.trim(),
                        createdAt: msg.created_at !== undefined ? msg.created_at : (msg.createdAt || new Date().toISOString())
                    })
                    Qt.callLater(function(){ listView.positionViewAtEnd() })
                }
                if (ondone) ondone(ok)
            }
        }
        xhr.send(JSON.stringify({
            conversationId: conversationId,
            senderId: (selfId > 0 ? selfId : patientId),
            senderRole: "patient",
            content: text.trim()
        }))
    }

    function sendMessage(text) {
        const t = (text || "").trim()
        if (t.length === 0) return
        if (conversationId <= 0) {
            console.log("no conversationId, cannot send")
            return
        }
        if (sending) return
        sending = true

        const usedWs = sendViaWs(t)
        if (usedWs) {
            sending = false
            return
        }
        sendViaHttp(t, function() { sending = false })
    }

    Component.onCompleted: {
        console.log("PatientChatScreen params => apiBase:", apiBase, " wsUrl:", wsUrl, " conversationId:", conversationId, " patientId:", patientId, " doctorId:", doctorId)
        if (selfId <= 0) selfId = patientId
        ensureWs()
        ensureConversation(function(ok) {
            if (ok) {
                loadHistory()
                connectSocket()
            } else {
                console.log("无法创建/获取会话，检查后端日志")
            }
        })
    }
}

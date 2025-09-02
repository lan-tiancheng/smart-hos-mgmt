import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "智能AI问答 · Ultra"

    /* ===== rpx 工具（以 1280×800 为基准） ===== */
    readonly property real _baseW: 1280
    readonly property real _baseH: 800
    readonly property real _scale: Math.min(width/_baseW, height/_baseH)
    function rpx(v) { return v * _scale }
    function wh(p)  { return width * p }

    /* ===== 业务状态 ===== */
    property string userInput: ""
    property string aiReply: ""
    property bool   loading: false

    /* ===== 背景：渐变 + 动感彩条（无模糊） ===== */
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#141A33" }
            GradientStop { position: 1.0; color: "#0E1226" }
        }
    }
    Rectangle {
        id: topGlow
        anchors.horizontalCenter: parent.horizontalCenter
        y: rpx(24)
        width: wh(1.10)
        height: rpx(12)
        radius: rpx(6)
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#006BFFFF" }
            GradientStop { position: 0.5; color: "#6C63FFFF" }
            GradientStop { position: 1.0; color: "#00E1FFFF" }
        }
        opacity: 0.6
        SequentialAnimation on x {
            loops: Animation.Infinite
            NumberAnimation { from: -rpx(40); to: rpx(40); duration: 4200; easing.type: Easing.InOutSine }
            NumberAnimation { from:  rpx(40); to: -rpx(40); duration: 4200; easing.type: Easing.InOutSine }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin:  rpx(24)
        anchors.rightMargin: rpx(24)
        anchors.topMargin:   rpx(48)
        anchors.bottomMargin:rpx(24)
        spacing: rpx(18)

        /* ===== 标题 ===== */
        Label {
            text: "🤖 智能AI助手"
            color: "#FFFFFF"
            font.pixelSize: rpx(34)
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
        }

        /* ===== 聊天显示区 ===== */
        Rectangle {
            id: chatPanel
            color: "#2FFFFFFF"           // 半透明玻璃感（不使用模糊）
            radius: rpx(20)
            border.color: "#66FFFFFF"
            border.width: 1
            Layout.fillWidth: true
            Layout.fillHeight: true

            Flickable {
                id: chatArea
                anchors.fill: parent
                anchors.margins: rpx(12)
                contentHeight: chatCol.implicitHeight
                clip: true

                Column {
                    id: chatCol
                    width: chatArea.width
                    spacing: rpx(14)

                    /* ---- 用户消息（右对齐，单行） ---- */
                    Item {
                        visible: root.userInput.length > 0
                        width: parent.width
                        height: Math.max(userBubble.height, avatarUser.height)

                        Row {
                            anchors.right: parent.right
                            anchors.rightMargin: rpx(4)
                            spacing: rpx(8)

                            // 文本气泡（单行 + 省略）
                            Rectangle {
                                id: userBubble
                                color: "#2560E6"
                                radius: rpx(12)
                                border.color: "#80A8FF"
                                border.width: 1
                                readonly property int _padX: rpx(16)
                                readonly property int _padY: rpx(12)
                                width: Math.min(root.wh(0.70), userText.implicitWidth + _padX*2)
                                height: Math.max(rpx(44), userText.implicitHeight + _padY*2)

                                Text {
                                    id: userText
                                    text: root.userInput
                                    color: "#FFFFFF"
                                    font.pixelSize: rpx(22)           // 放大
                                    font.bold: true
                                    wrapMode: Text.NoWrap             // ✅ 不换行
                                    elide: Text.ElideRight            // ✅ 超出省略
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: userBubble._padX
                                }
                            }

                            // 用户头像（.jpeg）
                            Rectangle {
                                id: avatarUser
                                width: rpx(48); height: rpx(48)
                                radius: rpx(24)
                                clip: true
                                border.color: "#66FFFFFF"; border.width: 1
                                Image {
                                    anchors.fill: parent
                                    source: "images/avatar.jpeg"      // ✅ 用户 .jpeg
                                    fillMode: Image.PreserveAspectCrop
                                }
                            }
                        }
                    }

                    /* ---- AI 消息（左对齐，单行） ---- */
                    Item {
                        visible: root.aiReply.length > 0 || root.loading
                        width: parent.width
                        height: Math.max(aiBubble.height, avatarAI.height)

                        Row {
                            anchors.left: parent.left
                            anchors.leftMargin: rpx(4)
                            spacing: rpx(8)

                            // AI 头像
                            Rectangle {
                                id: avatarAI
                                width: rpx(48); height: rpx(48)
                                radius: rpx(24)
                                clip: true
                                border.color: "#66FFFFFF"; border.width: 1
                                Image {
                                    anchors.fill: parent
                                    source: "images/avatar_02.jpg"
                                    fillMode: Image.PreserveAspectCrop
                                }
                            }

                            // AI 气泡（单行 + 省略）
                            Rectangle {
                                id: aiBubble
                                color: "#FFFFFF"
                                radius: rpx(12)
                                border.color: "#CCCCCC"
                                border.width: 1
                                readonly property int _padX: rpx(16)
                                readonly property int _padY: rpx(12)
                                width: Math.min(root.wh(0.70), aiText.implicitWidth + _padX*2)
                                height: Math.max(rpx(44), aiText.implicitHeight + _padY*2)

                                Text {
                                    id: aiText
                                    text: root.loading ? "AI正在思考..." : (root.aiReply.length > 0 ? root.aiReply : "")
                                    color: "#222222"
                                    font.pixelSize: rpx(22)           // 放大
                                    wrapMode: Text.NoWrap             // ✅ 不换行
                                    elide: Text.ElideRight            // ✅ 超出省略
                                    anchors.verticalCenter: parent.verticalCenter
                                    anchors.left: parent.left
                                    anchors.leftMargin: aiBubble._padX
                                }
                            }
                        }
                    }
                }
            }
        }

        /* ===== 输入区（单行） ===== */
        RowLayout {
            Layout.fillWidth: true
            spacing: rpx(12)

            Rectangle {
                id: inputBox
                color: "#FFFFFFFF"
                radius: rpx(12)
                border.color: "#2560E6"
                border.width: 2
                Layout.fillWidth: true
                Layout.preferredHeight: rpx(60)

                // 单行输入
                TextField {
                    id: inputField
                    anchors.fill: parent
                    anchors.leftMargin: rpx(16)
                    anchors.rightMargin: rpx(16)
                    anchors.verticalCenter: parent.verticalCenter
                    placeholderText: "请输入你的问题（单行）…"
                    font.pixelSize: rpx(22)          // 放大
                    color: "#222222"
                    background: null
                    text: root.userInput
                    onTextChanged: root.userInput = text
                    enabled: !root.loading
                    echoMode: TextInput.Normal
                    inputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase
                }
            }

            /* ===== 发送按钮（文字居中） ===== */
            Button {
                id: sendBtn
                enabled: !root.loading && inputField.text.length > 0
                Layout.preferredWidth: rpx(140)
                Layout.preferredHeight: rpx(60)

                background: Rectangle {
                    id: btnBg
                    radius: rpx(12)
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "#6C63FF" }
                        GradientStop { position: 1.0; color: "#00E1FF" }
                    }
                    opacity: sendBtn.enabled ? 1.0 : 0.4

                    // 扫光条（位移用 rpx 控制）
                    Rectangle {
                        id: shimmer
                        width: rpx(60); height: btnBg.height
                        x: -width
                        rotation: 22
                        radius: rpx(6)
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: "#00FFFFFF" }
                            GradientStop { position: 0.5; color: "#A0FFFFFF" }
                            GradientStop { position: 1.0; color: "#00FFFFFF" }
                        }
                        SequentialAnimation on x {
                            loops: Animation.Infinite
                            running: sendBtn.enabled
                            NumberAnimation { from: -shimmer.width; to: btnBg.width + shimmer.width; duration: 1600 }
                            PauseAnimation   { duration: 900 }
                        }
                        opacity: sendBtn.enabled ? 0.9 : 0.0
                    }
                }

                // ✅ 文字绝对居中
                contentItem: Text {
                    text: root.loading ? "生成中…" : "发送"
                    color: "white"
                    font.pixelSize: rpx(22)
                    font.bold: true
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                onClicked: {
                    root.loading = true
                    root.aiReply = ""
                    var xhr = new XMLHttpRequest()
                    xhr.open("POST", "http://127.0.0.1:8080/glm_chat")
                    xhr.setRequestHeader("Content-Type", "application/json")
                    xhr.onreadystatechange = function() {
                        if (xhr.readyState === XMLHttpRequest.DONE) {
                            root.loading = false
                            if (xhr.status === 200) {
                                var resp = JSON.parse(xhr.responseText)
                                root.aiReply = resp.reply
                            } else {
                                root.aiReply = "请求失败"
                            }
                        }
                    }
                    xhr.send(JSON.stringify({ question: root.userInput }))
                }
            }
        }

        /* ===== 底部返回按钮（文字居中） ===== */
        Button {
            id: backBtn
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: rpx(120)
            Layout.preferredHeight: rpx(44)

            background: Rectangle {
                radius: rpx(12)
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#FF6A88" }
                    GradientStop { position: 1.0; color: "#FF99AC" }
                }
            }

            // ✅ 文字绝对居中
            contentItem: Text {
                text: "返回"
                color: "white"
                font.pixelSize: rpx(20)
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: mainStackView.pop()
        }
    }
}

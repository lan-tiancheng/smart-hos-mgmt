import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "智能AI问答"
    property string userInput: ""
    property string aiReply: ""
    property bool loading: false

    // 添加顶部标题栏（包含返回按钮）
    header: ToolBar {
        height: 60
        background: Rectangle {
            color: "#2560e6"
        }

        RowLayout {
            anchors.fill: parent
            spacing: 10

            // 返回按钮
            ToolButton {
                icon.source: "qrc:/icons/back.svg" // 使用返回图标
                icon.color: "white"
                icon.width: 30
                icon.height: 30
                onClicked: {
                    // 返回逻辑
                    var p = root.parent
                    while (p && typeof p.pop !== "function") p = p.parent
                    if (p) p.pop()
                }
                background: Rectangle {
                    color: "transparent"
                }
            }

            // 页面标题
            Label {
                text: root.title
                font.pixelSize: 20
                color: "white"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
            }

            // 右侧占位（保持对称）
            Item { width: 60 }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 32
        spacing: 24

        Label {
            text: "智能AI助手"
            font.pixelSize: 32
            font.bold: true
            color: "#2560e6"
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
            Layout.fillWidth: true
        }

        Rectangle {
            color: "#fff"
            radius: 12
            border.color: "#2560e6"
            border.width: 1
            Layout.fillWidth: true
            Layout.preferredHeight: 100
            Layout.alignment: Qt.AlignHCenter

            TextArea {
                id: inputArea
                placeholderText: "请输入你的问题..."
                font.pixelSize: 18
                wrapMode: TextArea.Wrap
                anchors.fill: parent
                anchors.margins: 12
                background: Rectangle { color: "transparent" }
                text: root.userInput
                onTextChanged: root.userInput = text
                enabled: !root.loading
            }
        }

        Button {
            text: root.loading ? "正在生成..." : "发送"
            font.pixelSize: 20
            Layout.preferredWidth: 160
            Layout.alignment: Qt.AlignHCenter
            enabled: !root.loading && inputArea.text.length > 0
            background: Rectangle {
                color: root.loading ? "#a4b9f7" : "#2560e6"
                radius: 8
            }
            contentItem: Label {
                text: parent.text
                color: "#fff"
                anchors.centerIn: parent
                font.pixelSize: 20
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
        Button {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            text: "返回"
            font.pixelSize: 16
            onClicked: {
                // 返回逻辑
                var p = root.parent
                while (p && typeof p.pop !== "function") p = p.parent
                if (p) p.pop()
            }
        }
        Rectangle {
            color: "#fff"
            radius: 12
            border.color: "#7fa6fa"
            border.width: 1
            Layout.fillWidth: true
            Layout.preferredHeight: 220
            Layout.alignment: Qt.AlignHCenter

            Flickable {
                contentHeight: replyLabel.paintedHeight
                width: parent.width
                height: parent.height
                clip: true

                Label {
                    id: replyLabel
                    text: root.aiReply.length > 0 ? root.aiReply : (root.loading ? "AI正在思考..." : "等待您的问题")
                    color: "#222"
                    font.pixelSize: 20
                    wrapMode: Text.Wrap
                    width: parent.width - 24
                    anchors.leftMargin: 12
                    anchors.topMargin: 12
                }
            }
        }
    }
}

// MessageListScreen.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "消息"

    StackView.onStatusChanged: {
        if (StackView.status === StackView.Active) {
            authManager.requestConversations()
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        model: ListModel {
            id: conversationModel
        }
        delegate: ItemDelegate {
            width: listView.width
            height: 70
            RowLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 10

                Rectangle {
                    width: 50
                    height: 50
                    radius: 25
                    color: "#1A5D1A"

                    Label {
                        anchors.centerIn: parent
                        text: model.username.substring(0, 1).toUpperCase()
                        color: "white"
                        font.bold: true
                        font.pixelSize: 18
                    }
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 5

                    Text {
                        text: model.username + (model.userType === "doctor" ? " (医生)" : " (患者)")
                        font.bold: true
                        font.pixelSize: 16
                        elide: Text.ElideRight
                    }

                    Text {
                        text: model.lastMessage || "暂无消息"
                        color: "gray"
                        font.pixelSize: 14
                        elide: Text.ElideRight
                    }
                }

                ColumnLayout {
                    spacing: 5

                    Text {
                        text: model.timestamp || ""
                        color: "gray"
                        font.pixelSize: 12
                    }

                    Rectangle {
                        width: 20
                        height: 20
                        radius: 10
                        color: "red"
                        visible: model.unreadCount > 0

                        Label {
                            anchors.centerIn: parent
                            text: model.unreadCount
                            color: "white"
                            font.pixelSize: 10
                            font.bold: true
                        }
                    }
                }
            }
            onClicked: {
                stack.push("ConversationScreen.qml", {
                    otherUserId: model.userId,
                    otherUsername: model.username
                })
            }
        }
    }

    Connections {
        target: authManager
        function onConversationListReceived(conversations) {
            conversationModel.clear()
            for (var i = 0; i < conversations.length; i++) {
                var conv = conversations[i]
                conversationModel.append({
                    userId: conv.userId,
                    username: conv.username,
                    userType: conv.userType,
                    lastMessage: conv.lastMessage,
                    timestamp: conv.timestamp,
                    unreadCount: conv.unreadCount || 0
                })
            }
        }

        function onMessageReceived(fromUserId, fromUsername, message) {
            // 更新对话列表中的最后一条消息
            for (var i = 0; i < conversationModel.count; i++) {
                if (conversationModel.get(i).userId === fromUserId) {
                    conversationModel.setProperty(i, "lastMessage", message)
                    conversationModel.setProperty(i, "timestamp", new Date().toLocaleTimeString(Qt.locale(), "hh:mm"))
                    conversationModel.setProperty(i, "unreadCount", conversationModel.get(i).unreadCount + 1)
                    break
                }
            }
        }
    }
}

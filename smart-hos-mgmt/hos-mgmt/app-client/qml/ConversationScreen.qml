// ConversationScreen.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    property int otherUserId: 0
    property string otherUsername: ""

    title: otherUsername

    StackView.onStatusChanged: {
        if (StackView.status === StackView.Active) {
            authManager.requestMessages(otherUserId)
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // 消息列表
        ListView {
            id: messageList
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: ListModel {
                id: messageModel
            }
            delegate: MessageBubble {
                isMe: model.senderId === authManager.currentUserId
                message: model.message
                timestamp: model.timestamp
            }
            spacing: 10
        }

        // 输入区域
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            spacing: 10
            padding: 10

            TextField {
                id: messageInput
                Layout.fillWidth: true
                placeholderText: "输入消息..."
                onAccepted: sendButton.clicked()
            }

            Button {
                id: sendButton
                text: "发送"
                onClicked: {
                    if (messageInput.text.trim() !== "") {
                        authManager.sendMessage(otherUserId, messageInput.text)
                        messageInput.text = ""
                    }
                }
            }

            Button {
                icon.source: "qrc:/icons/video_call.svg"
                onClicked: authManager.startVideoCall(otherUserId)
                ToolTip.visible: hovered
                ToolTip.text: "视频通话"
            }
        }
    }

    Connections {
        target: authManager
        function onMessagesReceived(conversationId, messages) {
            if (conversationId === root.otherUserId) {
                messageModel.clear()
                for (var i = 0; i < messages.length; i++) {
                    var msg = messages[i]
                    messageModel.append({
                        senderId: msg.senderId,
                        message: msg.message,
                        timestamp: msg.timestamp
                    })
                }
                messageList.positionViewAtEnd()
            }
        }

        function onMessageReceived(fromUserId, fromUsername, message) {
            if (fromUserId === root.otherUserId) {
                messageModel.append({
                    senderId: fromUserId,
                    message: message,
                    timestamp: new Date().toLocaleTimeString(Qt.locale(), "hh:mm")
                })
                messageList.positionViewAtEnd()
            }
        }

        function onMessageSentSuccess(messageId) {
            // 消息发送成功，可以更新UI
            console.log("消息发送成功，ID:", messageId)
        }

        function onMessageSentFailed(reason) {
            // 显示发送失败提示
            console.log("消息发送失败:", reason)
        }

        function onVideoCallRequested(callId, fromUserId, fromUsername) {
            // 显示视频通话请求对话框
            videoCallDialog.callId = callId
            videoCallDialog.fromUserId = fromUserId
            videoCallDialog.fromUsername = fromUsername
            videoCallDialog.open()
        }
    }

    // 视频通话请求对话框
    Dialog {
        id: videoCallDialog
        property int callId: 0
        property int fromUserId: 0
        property string fromUsername: ""

        title: "视频通话请求"
        standardButtons: Dialog.Yes | Dialog.No
        modal: true

        Label {
            text: fromUsername + " 请求视频通话"
            font.pixelSize: 16
        }

        onAccepted: {
            authManager.acceptVideoCall(callId)
        }

        onRejected: {
            authManager.rejectVideoCall(callId)
        }
    }

    // 视频通话界面
    Loader {
        id: videoCallLoader
        anchors.fill: parent
        active: false

        function startCall(callId) {
            active = true
            item.callId = callId
        }

        function endCall() {
            active = false
        }
    }

    Connections {
        target: authManager
        function onVideoCallAccepted(callId) {
            videoCallLoader.setSource("VideoCallScreen.qml")
            videoCallLoader.item.callId = callId
        }

        function onVideoCallRejected(callId) {
            // 显示通话被拒绝的提示
            console.log("视频通话被拒绝，ID:", callId)
        }

        function onVideoCallStarted(callId) {
            videoCallLoader.setSource("VideoCallScreen.qml")
            videoCallLoader.item.callId = callId
        }

        function onVideoCallEnded(callId) {
            videoCallLoader.active = false
        }

        function onVideoCallError(reason) {
            // 显示通话错误提示
            console.log("视频通话错误:", reason)
        }
    }
}

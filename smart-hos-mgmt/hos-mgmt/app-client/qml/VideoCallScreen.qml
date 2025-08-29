// VideoCallScreen.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    property int callId: 0

    title: "视频通话"

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        // 远程视频画面
        Rectangle {
            width: 300
            height: 200
            color: "#333"
            radius: 10

            Label {
                anchors.centerIn: parent
                text: "远程视频"
                color: "white"
            }
        }

        // 本地视频画面
        Rectangle {
            width: 150
            height: 100
            color: "#555"
            radius: 10
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 20

            Label {
                anchors.centerIn: parent
                text: "本地视频"
                color: "white"
                font.pixelSize: 12
            }
        }

        // 通话控制按钮
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            Button {
                icon.source: "qrc:/icons/mic_off.svg"
                ToolTip.visible: hovered
                ToolTip.text: "静音"
                onClicked: {
                    // 切换麦克风状态
                }
            }

            Button {
                icon.source: "qrc:/icons/videocam_off.svg"
                ToolTip.visible: hovered
                ToolTip.text: "关闭摄像头"
                onClicked: {
                    // 切换摄像头状态
                }
            }

            Button {
                icon.source: "qrc:/icons/call_end.svg"
                background: Rectangle { color: "red" }
                onClicked: {
                    // 结束通话
                    authManager.endVideoCall(callId)
                    stack.pop()
                }
            }

            Button {
                icon.source: "qrc:/icons/screen_share.svg"
                ToolTip.visible: hovered
                ToolTip.text: "屏幕共享"
                onClicked: {
                    // 切换屏幕共享
                }
            }

            Button {
                icon.source: "qrc:/icons/volume_up.svg"
                ToolTip.visible: hovered
                ToolTip.text: "音量"
                onClicked: {
                    // 调整音量
                }
            }
        }
    }

    Component.onDestruction: {
        // 离开页面时结束通话
        authManager.endVideoCall(callId)
    }
}

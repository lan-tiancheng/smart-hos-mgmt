// MainScreen.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "智慧医疗系统"

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            spacing: 10

            Label {
                text: "智慧医疗系统"
                font.pixelSize: 20
                font.bold: true
                color: "white"
                Layout.leftMargin: 10
            }

            Item { Layout.fillWidth: true }

            Button {
                text: "消息"
                onClicked: stack.push("MessageListScreen.qml")
            }

            Button {
                text: "健康数据"
                onClicked: stack.push("HealthInputScreen.qml")
            }

            Button {
                text: "退出"
                onClicked: {
                    authManager.logout()
                    stack.replace("LoginScreen.qml")
                }
            }
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 20

        Label {
            text: "欢迎使用智慧医疗系统！"
            font.pixelSize: 24
            font.bold: true
            color: "#1A5D1A"
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            text: "请使用顶部导航栏访问功能"
            font.pixelSize: 16
            color: "#1A5D1A"
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }
    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.mycompany.app 1.0

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: "智慧医疗系统"

    StackLayout {
        id: screenStack
        anchors.fill: parent
        // 登录界面
        LoginScreen {
            Layout.fillWidth: true
            Layout.fillHeight: true

            onLoginSuccess: (userType) => {
                console.log("登录成功, 用户类型:", userType)
                // 登录成功后切换主界面
                screenStack.currentIndex = 1
            }
        }

        // 主界面示例
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#E0F2F1"

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
                    text: "这是主界面示例，你可以在这里添加功能页面。"
                    font.pixelSize: 16
                    color: "#1A5D1A"
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }
    }
}

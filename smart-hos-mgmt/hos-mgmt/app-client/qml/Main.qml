// Main.qml
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

    StackView {
        id: stack
        anchors.fill: parent

        initialItem: LoginScreen {
            onLoginSuccess: (userType) => {
                console.log("登录成功, 用户类型:", userType)
                // 登录成功后切换到主界面
                stack.replace("MainScreen.qml")
            }
        }
    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.mycompany.app 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: "智慧医疗系统"

    // 登录界面
    LoginScreen {
        id: loginScreen
        anchors.fill: parent

        // 接收登录成功信号，可在此进行导航或加载主界面
        onLoginSuccess: function(userType) {
            console.log("登录成功，用户类型：", userType)
            // TODO: 在此切换到主界面（医生/病人）
        }
    }
}

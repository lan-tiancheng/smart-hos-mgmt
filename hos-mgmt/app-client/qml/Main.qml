import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.mycompany.app 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: "智慧医疗系统"

    // 根据认证状态与用户类型切换界面：
    // - 未登录：显示登录/注册界面
    // - 已登录且为病人：显示体检数据提交
    // - 已登录且为医生：显示占位信息（可后续扩展）
    Loader {
        id: router
        anchors.fill: parent
        sourceComponent: !authManager.isAuthenticated
                         ? loginView
                         : (authManager.currentUserType === AuthManager.Patient ? patientView : doctorView)
    }

    Component {
        id: loginView
        LoginScreen { anchors.fill: parent }
    }

    Component {
        id: patientView
        HealthInputScreen { anchors.fill: parent }
    }

    Component {
        id: doctorView
        Rectangle {
            anchors.fill: parent
            color: "#ffffff"
            Column {
                anchors.centerIn: parent
                spacing: 12
                Label { text: "医生用户已登录"; font.pixelSize: 22 }
                Label { text: "医生端主界面功能待接入"; color: "#666666" }
            }
        }
    }
}

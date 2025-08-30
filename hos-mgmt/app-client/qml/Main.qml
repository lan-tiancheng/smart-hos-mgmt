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

    // 打开为 true 时直接进入语音测试页；测完改回 false
    property bool debugVoiceTest: true

    Loader {
        id: router
        anchors.fill: parent
        sourceComponent: debugVoiceTest
                         ? voiceTestView
                         : (!authManager.isAuthenticated
                             ? loginView
                             : (authManager.currentUserType === AuthManager.Patient ? patientView : doctorView))
    }

    Component {
        id: voiceTestView
        VoiceTest { anchors.fill: parent }
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

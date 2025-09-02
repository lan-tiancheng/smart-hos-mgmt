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

    StackView {
        id: mainStackView
        anchors.fill: parent
        initialItem: Qt.resolvedUrl("LoginScreen.qml")
    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    title: "医生主界面"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 36

        Label {
            text: "医生服务中心"
            font.pixelSize: 32
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            spacing: 30
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: "签到管理"
                icon.source: "qrc:/icons/sign.svg"
                onClicked: mainStackView.push("AttendanceManagement.qml")
                Layout.preferredWidth: 150
            }
            Button {
                text: "个人信息"
                icon.source: "qrc:/icons/Docprofile.svg"
                onClicked: mainStackView.push("DoctorInformationEditing.qml")
                Layout.preferredWidth: 150
            }
            Button {
                text: "预约查看"
                icon.source: "qrc:/icons/App.svg"
                onClicked: mainStackView.push("AppointmentCheck.qml")
                Layout.preferredWidth: 150
            }
        }

        GridLayout {
            columns: 1
            rowSpacing: 20
            columnSpacing: 30
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: "医嘱管理"
                icon.source: "qrc:/icons/docadvice.svg"
                onClicked: mainStackView.push("DoctorAdvice.qml")
                Layout.preferredWidth: 140
            }

        }
    }
}

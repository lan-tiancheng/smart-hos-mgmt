import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    title: "患者主界面"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 36

        Label {
            text: "患者服务中心"
            font.pixelSize: 32
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            spacing: 30
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: "健康评估"
                icon.source: "qrc:/icons/health.svg"
                onClicked: mainStackView.push("HealthInputScreen.qml")
                Layout.preferredWidth: 150
            }
            Button {
                text: "个人信息"
                icon.source: "qrc:/icons/profile.svg"
                onClicked: mainStackView.push("PersonalInformationEditing.qml")
                Layout.preferredWidth: 150
            }
        }

        GridLayout {
            columns: 3
            rowSpacing: 20
            columnSpacing: 30
            Layout.alignment: Qt.AlignHCenter

            Button {
                text: "挂号"
                icon.source: "qrc:/icons/register.svg"
                onClicked: mainStackView.push("PatientAppointmentScreen.qml")
                Layout.preferredWidth: 140
            }

            Button {
                text: "查看病例"
                icon.source: "qrc:/icons/case.svg"
                onClicked: mainStackView.push("CaseListScreen.qml")
                Layout.preferredWidth: 140
            }
            Button {
                text: "预约就诊"
                icon.source: "qrc:/icons/appointment.svg"
                onClicked: mainStackView.push("ForwardAppointment.qml")
                Layout.preferredWidth: 140
            }
            Button {
                text: "药品搜索"
                icon.source: "qrc:/icons/drug.svg"
                onClicked: mainStackView.push("DrugSearchScreen.qml")
                Layout.preferredWidth: 140
            }
            Button {
                text: "住院信息"
                icon.source: "qrc:/icons/hospital.svg"
                onClicked: mainStackView.push("HospitalInfoScreen.qml")
                Layout.preferredWidth: 140
            }
            Button {
                text: "线上支付"
                icon.source: "qrc:/icons/pay.svg"
                onClicked: mainStackView.push("OnlinePayScreen.qml")
                Layout.preferredWidth: 140
            }

            Button {
                text: "医疗助手"
                icon.source: "qrc:/icons/ai.svg"
                onClicked: mainStackView.push("GLMAiChatScreen.qml")
                Layout.preferredWidth: 140
            }

            Button {
                text: "语音测试"
                icon.source: "qrc:/icons/test.svg"
                onClicked: mainStackView.push("VoiceTest.qml")
                Layout.preferredWidth: 140
            }
        }
    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "医嘱管理"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Label {
            text: "为患者开具医嘱"
            font.pixelSize: 20
            Layout.alignment: Qt.AlignHCenter
        }

        TextField {
            id: patientName
            placeholderText: "患者姓名"
            Layout.fillWidth: true
        }

        TextArea {
            id: adviceContent
            placeholderText: "请输入医嘱内容"
            Layout.fillWidth: true
            Layout.preferredHeight: 120
            wrapMode: TextArea.Wrap
        }

        Button {
            text: "提交医嘱"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                if (patientName.text.trim() !== "" && adviceContent.text.trim() !== "") {
                    adviceModel.append({
                        "patient": patientName.text,
                        "advice": adviceContent.text,
                        "time": new Date().toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm:ss")
                    })
                    patientName.text = ""
                    adviceContent.text = ""
                }
            }
        }
        Button {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            text: "返回"
            font.pixelSize: 16
            onClicked: {
                // 返回逻辑
                var p = root.parent
                while (p && typeof p.pop !== "function") p = p.parent
                if (p) p.pop()
            }
        }
        Label {
            text: "医嘱记录"
            font.pixelSize: 18
            Layout.alignment: Qt.AlignLeft
            Layout.topMargin: 15
        }

        ListView {
            id: adviceList
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: ListModel { id: adviceModel }

            delegate: Rectangle {
                width: adviceList.width
                height: 80
                color: index % 2 === 0 ? "#f9f9f9" : "#ffffff"
                border.color: "#cccccc"
                border.width: 1

                Column {
                    anchors.fill: parent
                    anchors.margins: 8
                    spacing: 4

                    Text {
                        text: "患者: " + patient
                        font.bold: true
                    }

                    Text {
                        text: "医嘱: " + advice
                        wrapMode: Text.Wrap
                    }

                    Text {
                        text: "时间: " + time
                        color: "#666666"
                        font.pixelSize: 12
                    }
                }
            }
        }
    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: attendancePage
    title: "考勤管理"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Label {
            text: "医生考勤管理"
            font.pixelSize: 22
            Layout.alignment: Qt.AlignHCenter
        }

        // ---------------- 打卡 ----------------
        RowLayout {
            spacing: 10
            Button {
                text: "签到"
                onClicked: {
                    attendanceModel.append({
                        "type": "签到",
                        "time": new Date().toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm:ss"),
                        "reason": ""
                    })
                }
            }
            Button {
                text: "签退"
                onClicked: {
                    attendanceModel.append({
                        "type": "签退",
                        "time": new Date().toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm:ss"),
                        "reason": ""
                    })
                }
            }
        }

        // ---------------- 请假 ----------------
        Label { text: "请假申请"; font.pixelSize: 18; Layout.topMargin: 10 }

        TextField {
            id: leaveReason
            placeholderText: "请假理由"
            Layout.fillWidth: true
        }
        RowLayout {
            spacing: 10
            Button {
                text: "提交请假"
                onClicked: {
                    if (leaveReason.text.trim() !== "") {
                        attendanceModel.append({
                            "type": "请假",
                            "time": new Date().toLocaleString(Qt.locale(), "yyyy-MM-dd hh:mm:ss"),
                            "reason": leaveReason.text
                        })
                        leaveReason.text = ""
                    }
                }
            }
            Button {
                text: "清空"
                onClicked: leaveReason.text = ""
            }
        }

        // ---------------- 销假 ----------------
        Label { text: "销假"; font.pixelSize: 18; Layout.topMargin: 10 }
        RowLayout {
            spacing: 10
            Button {
                text: "撤销最后一条请假"
                onClicked: {
                    for (var i = attendanceModel.count - 1; i >= 0; i--) {
                        if (attendanceModel.get(i).type === "请假") {
                            attendanceModel.remove(i)
                            break
                        }
                    }
                }
            }
        }

        // ---------------- 考勤记录 ----------------
        Label { text: "考勤记录"; font.pixelSize: 18; Layout.topMargin: 10 }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: ListModel { id: attendanceModel }

            delegate: Rectangle {
                width: parent.width
                height: 70
                color: index % 2 === 0 ? "#f9f9f9" : "#ffffff"
                border.color: "#cccccc"
                border.width: 1

                Column {
                    anchors.fill: parent
                    anchors.margins: 8
                    spacing: 4

                    Text { text: "类型: " + type; font.bold: true }
                    Text { text: "时间: " + time }
                    Text { text: reason !== "" ? "理由: " + reason : "" }
                }
            }
        }
    }
}

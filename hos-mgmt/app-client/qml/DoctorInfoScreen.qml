import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    title: "医生信息"

    // 可由外部传入医生数组（[{ name, workId/work_id, department, ... }...]）
    property var doctors: []

    // 内部可见的列表（用于筛选展示）
    property var filteredDoctors: []

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            Label {
                text: page.title
                font.bold: true
                font.pixelSize: 18
                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                Layout.leftMargin: 12
            }
            Item { Layout.fillWidth: true }
            ToolButton {
                text: "返回"
                onClicked: mainStackView ? mainStackView.pop() : (StackView.view ? StackView.view.pop() : null)
                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                Layout.rightMargin: 8
            }
        }
    }

    Component.onCompleted: {
        if (!doctors || doctors.length === 0) {
            // 简单示例数据，便于先跑通界面。上线时请替换为真实数据源。
            doctors = [
                {
                    name: "张三",
                    work_id: "D1001",
                    department: "内科",
                    personal_profile: "从业10年，擅长呼吸道疾病。",
                    photo_url: "",
                    working_hours: { start: "09:00", end: "17:00" },
                    consultation_fee: "50",
                    daily_limit: 30
                },
                {
                    name: "李四",
                    work_id: "D1002",
                    department: "外科",
                    personal_profile: "擅长普外手术与微创治疗。",
                    photo_url: "",
                    working_hours: { start: "08:30", end: "16:30" },
                    consultation_fee: "80",
                    daily_limit: 20
                }
            ]
        }
        filteredDoctors = doctors
    }

    function applyFilter(text) {
        var key = (text || "").toLowerCase()
        if (!key) {
            filteredDoctors = doctors
            return
        }
        filteredDoctors = doctors.filter(function (d) {
            var name = (d.name || "").toLowerCase()
            var dept = (d.department || d.dept || "").toLowerCase()
            var workId = (d.workId || d.work_id || "").toLowerCase()
            return name.indexOf(key) !== -1 || dept.indexOf(key) !== -1 || workId.indexOf(key) !== -1
        })
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        TextField {
            id: searchField
            placeholderText: "搜索医生姓名 / 科室 / 工号"
            onTextChanged: applyFilter(text)
            Layout.fillWidth: true
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: filteredDoctors
            delegate: Frame {
                width: ListView.view.width
                padding: 10
                background: Rectangle { color: "#FAFAFA"; radius: 6; border.color: "#E6E6E6" }

                RowLayout {
                    spacing: 12
                    width: parent.width

                    Rectangle {
                        width: 56; height: 56; radius: 6
                        color: "#EEE"; border.color: "#DDD"; clip: true
                        Image { anchors.fill: parent; fillMode: Image.PreserveAspectCrop; source: (modelData.photoUrl || modelData.photo_url || "") }
                        Label {
                            visible: !(modelData.photoUrl || modelData.photo_url)
                            anchors.centerIn: parent
                            text: "无\n照"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#777"
                            font.pixelSize: 10
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 4
                        Label { text: (modelData.name || "—"); font.pixelSize: 16; color: "#222" }
                        Label {
                            text: "工号：" + (modelData.workId || modelData.work_id || "—") + "    科室：" + (modelData.department || modelData.dept || "—")
                            color: "#555"
                        }
                        Label {
                            text: "出诊：" +
                                  ((modelData.working_hours && modelData.working_hours.start) ? (modelData.working_hours.start + " - " + modelData.working_hours.end)
                                                                                             : ((modelData.workStart || modelData.work_start || "--:--") + " - " + (modelData.workEnd || modelData.work_end || "--:--")))
                            color: "#777"
                            font.pixelSize: 12
                        }
                    }

                    Button {
                        text: "查看"
                        onClicked: {
                            var payload = { doctor: modelData }
                            if (mainStackView) mainStackView.push("DoctorDetailScreen.qml", payload)
                            else if (StackView.view) StackView.view.push("DoctorDetailScreen.qml", payload)
                        }
                    }
                }
            }
            section.property: "department"
            section.delegate: Rectangle {
                width: ListView.view.width
                height: 28
                color: "#F0F0F0"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    text: section
                    color: "#666"
                }
            }
        }
    }
}

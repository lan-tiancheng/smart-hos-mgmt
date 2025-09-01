import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    title: "预约就诊"

    property var hospitalList: [ {id: 1, name:"市医院"}, {id:2, name:"区医院"} ]
    property var departmentList: [ {id: 1, name:"内科"}, {id:2, name:"外科"} ]
    property var clinicList: [ {id: 1, name:"普通门诊"}, {id:2, name:"专家门诊"} ]
    property var doctorResults: []

    property int selectedHospital: -1
    property int selectedDepartment: -1
    property int selectedClinic: -1
    property string selectedDate: ""
    property var dateList: []

    // 生成未来30天日期
    Component.onCompleted: {
        var today = new Date()
        for (var i = 0; i < 30; ++i) {
            var d = new Date(today.getTime() + i * 86400000)
            dateList.push(Qt.formatDate(d, "yyyy-MM-dd"))
        }
        selectedDate = dateList.length > 0 ? dateList[0] : ""
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 24
        color: "#f8faff"

        ColumnLayout {
            anchors.fill: parent
            spacing: 18

            Label {
                text: "请选择预约信息"
                font.pixelSize: 22
                Layout.alignment: Qt.AlignHCenter
            }

            // 日期选择（ComboBox）
            RowLayout {
                spacing: 10
                Label { text: "日期:" }
                ComboBox {
                    id: dateCombo
                    model: dateList
                    Layout.preferredWidth: 150
                    onCurrentIndexChanged: selectedDate = dateList[currentIndex]
                }
            }

            // 医院选择
            RowLayout {
                spacing: 10
                Label { text: "医院:" }
                ComboBox {
                    id: hospitalBox
                    model: hospitalList
                    textRole: "name"
                    Layout.preferredWidth: 180
                    onCurrentIndexChanged: selectedHospital = currentIndex
                }
            }

            // 科室选择
            RowLayout {
                spacing: 10
                Label { text: "科室:" }
                ComboBox {
                    id: departmentBox
                    model: departmentList
                    textRole: "name"
                    Layout.preferredWidth: 180
                    onCurrentIndexChanged: selectedDepartment = currentIndex
                }
            }

            // 门诊选择
            RowLayout {
                spacing: 10
                Label { text: "门诊:" }
                ComboBox {
                    id: clinicBox
                    model: clinicList
                    textRole: "name"
                    Layout.preferredWidth: 180
                    onCurrentIndexChanged: selectedClinic = currentIndex
                }
            }

            Button {
                text: "搜索支持预约的医生"
                Layout.preferredWidth: 200
                enabled: selectedHospital >= 0 && selectedDepartment >= 0 && selectedClinic >= 0 && selectedDate !== ""
                onClicked: {
                    // 请替换为你的接口
                    client.searchDoctors({
                        date: selectedDate,
                        hospitalId: hospitalList[selectedHospital].id,
                        departmentId: departmentList[selectedDepartment].id,
                        clinicId: clinicList[selectedClinic].id
                    }, function(results) {
                        doctorResults = results
                    })
                }
            }

            // 医生列表
            ListView {
                id: doctorListView
                model: doctorResults
                Layout.fillWidth: true
                Layout.fillHeight: true
                delegate: Rectangle {
                    width: doctorListView.width
                    height: 140
                    color: "#f5f7fa"
                    border.color: "#e0e0e0"
                    radius: 8
                    anchors.margins: 10
                    RowLayout {
                        anchors.fill: parent
                        spacing: 15
                        ColumnLayout {
                            spacing: 5
                            Label { text: "医生: " + model.name }
                            Label { text: "科室: " + model.department }
                            Label { text: "职称: " + model.title }
                            Label { text: "门诊时间: " + model.workTime }
                        }
                        Button {
                            text: "预约"
                            enabled: model.canReserve
                            onClicked: {
                                // 跳转预约详情
                                mainStackView.push("RegisterAppointmentScreen.qml", {
                                    doctorId: model.id,
                                    date: selectedDate,
                                    hospitalId: hospitalList[selectedHospital].id,
                                    departmentId: departmentList[selectedDepartment].id,
                                    clinicId: clinicList[selectedClinic].id
                                })
                            }
                        }
                    }
                }
            }
        }
    }
}

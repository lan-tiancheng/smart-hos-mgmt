import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.4

Page {
    title: "预约就诊"
    header: ToolBar {
            RowLayout {
                anchors.fill: parent

                ToolButton {
                    text: "返回"
                    onClicked: {
                        if (mainStackView) mainStackView.pop()
                        else console.log("mainStackView 未定义，无法返回")
                    }
                }

                Label {
                    text: page.title
                    font.pixelSize: 18
                    font.bold: true
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                    Layout.fillWidth: true
                }

                Item { width: 48 } // 占位，使标题居中
            }
        }
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
        // 确保 ComboBox 有默认选中项（否则 selectedDate 可能为空）
        if (dateList.length > 0) {
            selectedDate = dateList[0]
            // dateCombo 已存在于 component 中，设置 currentIndex = 0
            // （onCompleted 在组件完全创建后运行，所以 dateCombo 可用）
            dateCombo.currentIndex = 0
        }
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

            // 日期选择
            RowLayout {
                            spacing: 5
                            Label { text: "日期:" }
                            Calendar {
                                id: calendar
                                onClicked: selectedDate = Qt.formatDateTime(calendar.selectedDate, "yyyy-MM-dd")
                                width: 50
                                height: 50
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
                Layout.preferredWidth: 220
                enabled: selectedHospital >= 0 && selectedDepartment >= 0 && selectedClinic >= 0 && selectedDate !== ""
                onClicked: {
                    // 模拟生成一些医生 —— 注意字段保留与之前一致
                    // 使用 selectedDate 保证“按日期生成”
                    console.log("搜索条件:", selectedDate, hospitalList[selectedHospital], departmentList[selectedDepartment], clinicList[selectedClinic])
                    doctorResults = [
                        { id: 101, name: "张三", department: departmentList[selectedDepartment].name, title: "主任医师", workTime: selectedDate + " 09:00-12:00", canReserve: true },
                        { id: 102, name: "李四", department: departmentList[selectedDepartment].name, title: "副主任医师", workTime: selectedDate + " 14:00-17:00", canReserve: true },
                        { id: 103, name: "王五", department: departmentList[selectedDepartment].name, title: "主治医师", workTime: selectedDate + " 09:00-11:30", canReserve: true }
                    ]
                    console.log("生成医生数量:", doctorResults.length)
                }
            }

            // 医生列表
            ListView {
                id: doctorListView
                model: doctorResults
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                delegate: Rectangle {
                    width: doctorListView.width
                    height: 120
                    color: "#ffffff"
                    border.color: "#dcdcdc"
                    radius: 8
                    anchors.margins: 10

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 15

                        ColumnLayout {
                            spacing: 6
                            // 使用 modelData.xxx 来访问 JS 数组元素
                            Label { text: "医生: " + (modelData && modelData.name ? modelData.name : "未知"); font.pixelSize: 16 }
                            Label { text: "科室: " + (modelData && modelData.department ? modelData.department : "—") }
                            Label { text: "职称: " + (modelData && modelData.title ? modelData.title : "—") }
                            Label { text: "门诊时间: " + (modelData && modelData.workTime ? modelData.workTime : "—") }
                        }

                        Button {
                            // 使用 modelData.canReserve
                            text: (modelData && modelData.canReserve) ? " 可预约" : "不可预约"
                            enabled: modelData && modelData.canReserve
                            onClicked: {
                                // 若你有 RegisterAppointmentScreen.qml，就跳转并传参
                                if (mainStackView) {
                                    mainStackView.push(Qt.resolvedUrl("RegisterAppointmentScreen.qml"), {
                                        doctorId: modelData.id,
                                        date: selectedDate,
                                        hospitalId: hospitalList[selectedHospital].id,
                                        departmentId: departmentList[selectedDepartment].id,
                                        clinicId: clinicList[selectedClinic].id
                                    })
                                } else {
                                    console.log("要跳转到预约详情，但 mainStackView 不存在，医生ID:", modelData.id)
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

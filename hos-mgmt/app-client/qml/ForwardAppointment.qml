import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Page {
    id: appointmentPage
    title: "预约就诊"

    property var hospitals: ["市中心医院", "社区医院", "儿童医院"]
    property var departments: ["内科", "外科", "儿科", "骨科"]

    // 示例医生数据
    property var doctors: [
        { id:"D001", hospital:"市中心医院", department:"内科", name:"张医生",
          profile:"主任医师，擅长心血管疾病", workTime:"周一至周五 上午 8:00-12:00", fee:30, maxPatients:20, booked:12 },
        { id:"D002", hospital:"市中心医院", department:"外科", name:"李医生",
          profile:"副主任医师，擅长胃肠外科手术", workTime:"周二、周四 下午 14:00-18:00", fee:50, maxPatients:15, booked:8 },
        { id:"D003", hospital:"儿童医院", department:"儿科", name:"王医生",
          profile:"儿科专家，专注儿童哮喘", workTime:"周三、周五 上午 9:00-12:00", fee:25, maxPatients:25, booked:20 }
    ]

    // 选择项
    property string selectedHospital: hospitals[0]
    property string selectedDepartment: departments[0]
    property string selectedDate: getCurrentDate() // 初始化为当前日期
    property string searchKeyword: ""

    // 获取当前格式化的日期
    function getCurrentDate() {
        var today = new Date();
        var yyyy = today.getFullYear();
        var mm = String(today.getMonth() + 1).padStart(2, '0');
        var dd = String(today.getDate()).padStart(2, '0');
        return yyyy + '-' + mm + '-' + dd;
    }

    // 日期选择弹窗
    Dialog {
        id: dateDialog
        title: "选择预约日期"
        standardButtons: Dialog.Ok | Dialog.Cancel

        property int selectedYear: new Date().getFullYear()
        property int selectedMonth: new Date().getMonth() + 1
        property int selectedDay: new Date().getDate()

        contentItem: Rectangle {
            implicitWidth: 300
            implicitHeight: 400

            GridLayout {
                anchors.fill: parent
                columns: 2

                Label { text: "年:" }
                SpinBox {
                    id: yearBox
                    from: 2020
                    to: 2030
                    value: new Date().getFullYear()
                    onValueChanged: dateDialog.selectedYear = value
                }

                Label { text: "月:" }
                SpinBox {
                    id: monthBox
                    from: 1
                    to: 12
                    value: new Date().getMonth() + 1
                    onValueChanged: dateDialog.selectedMonth = value
                }

                Label { text: "日:" }
                SpinBox {
                    id: dayBox
                    from: 1
                    to: 31
                    value: new Date().getDate()
                    onValueChanged: dateDialog.selectedDay = value
                }

                // 显示选择的日期
                Label { text: "选择的日期:" }
                Label {
                    text: dateDialog.selectedYear + "-" +
                          String(dateDialog.selectedMonth).padStart(2, '0') + "-" +
                          String(dateDialog.selectedDay).padStart(2, '0')
                    font.bold: true
                }
            }
        }

        onAccepted: {
            selectedDate = dateDialog.selectedYear + "-" +
                           String(dateDialog.selectedMonth).padStart(2, '0') + "-" +
                           String(dateDialog.selectedDay).padStart(2, '0');
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 12

        Label { text: "预约就诊"; font.pixelSize: 24; Layout.alignment: Qt.AlignHCenter }

        // 预约日期 - 使用自定义对话框
        RowLayout {
            spacing: 10
            Label { text: "预约日期:" }

            // 日期显示和选择按钮
            Button {
                text: selectedDate
                onClicked: dateDialog.open()
                Layout.preferredWidth: 150
                Layout.preferredHeight: 40
                contentItem: Text {
                    text: parent.text
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
            }
        }

        // 医院选择
        RowLayout { spacing: 10
            Label { text: "医院:" }
            ComboBox {
                id: hospitalCombo
                model: hospitals
                currentIndex:0
                onCurrentIndexChanged: selectedHospital = hospitals[currentIndex]
            }
        }

        // 科室选择
        RowLayout { spacing: 10
            Label { text: "科室:" }
            ComboBox {
                id: departmentCombo
                model: departments
                currentIndex:0
                onCurrentIndexChanged: selectedDepartment = departments[currentIndex]
            }
        }

        // 搜索医生
        RowLayout { spacing: 10
            Label { text: "搜索医生:" }
            TextField {
                id: searchField
                placeholderText: "输入医生姓名"
                Layout.fillWidth: true
                onTextChanged: searchKeyword = text
            }
            Button {
                text: "搜索"
                onClicked: doctorList.model = doctors.filter(function(d){
                    return d.hospital === selectedHospital &&
                           d.department === selectedDepartment &&
                           d.name.indexOf(searchKeyword) !== -1
                })
            }
        }

        // 医生列表
        ListView {
            id: doctorList
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10
            model: doctors.filter(function(d){
                return d.hospital === selectedHospital &&
                       d.department === selectedDepartment
            })

            delegate: Frame {
                width: parent.width
                background: Rectangle { color: "white"; radius: 8; border.color: "#cccccc" }

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 6

                    Label { text: "医生编号: " + model.id }
                    Label { text: "姓名: " + model.name }
                    Label { text: "医院: " + model.hospital }
                    Label { text: "科室: " + model.department }
                    Label { text: "个人资料: " + model.profile; wrapMode: Text.WordWrap }
                    Label { text: "上班时间: " + model.workTime }
                    Label { text: "挂号费用: " + model.fee + " 元" }
                    Label { text: "单日患者上限: " + model.maxPatients }
                    Label { text: "已预约人数: " + model.booked }
                    Label { text: "剩余预约数: " + (model.maxPatients - model.booked) }

                    RowLayout { Layout.alignment: Qt.AlignRight
                        Button {
                            text: "挂号"
                            enabled: model.booked < model.maxPatients
                            onClicked: {
                                var message = "挂号成功！\\n医生: " + model.name +
                                              "\\n医院: " + model.hospital +
                                              "\\n费用: " + model.fee + "元";

                                messageDialog.text = message;
                                messageDialog.open();
                            }
                        }
                    }
                }
            }
        }

        // 返回按钮
        Button {
            text: "返回"
            Layout.alignment: Qt.AlignLeft
            onClicked: {
                var p = appointmentPage.parent
                while (p && typeof p.pop !== "function") p = p.parent
                if (p) p.pop()
            }
        }
    }

    // 消息对话框
    MessageDialog {
        id: messageDialog
        title: "挂号结果"
        onAccepted: close()
    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

// 主应用程序
ApplicationWindow {
    id: app
    width: 800
    height: 600
    visible: true
    title: "医疗预约系统"

    // 模拟数据
    property var appointments: [
        { id: 1, name: "张三", time: "2023-09-15 10:30", age: 45, gender: "男", phone: "13800138000", history: "高血压病史5年，近期血压控制良好" },
        { id: 2, name: "李四", time: "2023-09-15 11:00", age: 32, gender: "女", phone: "13900139000", history: "糖尿病2型，胰岛素治疗" },
        { id: 3, name: "王五", time: "2023-09-15 14:00", age: 68, gender: "男", phone: "13700137000", history: "冠心病，支架术后恢复良好" },
        { id: 4, name: "赵六", time: "2023-09-16 09:00", age: 28, gender: "女", phone: "13600136000", history: "健康体检，无特殊病史" }
    ]

    // 主堆栈视图
    StackView {
        id: mainStack
        initialItem: appointmentListPage
        anchors.fill: parent
    }

    // 预约列表页面
    Component {
        id: appointmentListPage

        Page {
            title: "今日预约"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15

                Label {
                    text: "今日预约患者 (" + appointments.length + ")"
                    font.pixelSize: 24
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                // 患者列表
                ListView {
                    id: listView
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    spacing: 10
                    clip: true

                    model: appointments

                    delegate: Rectangle {
                        width: listView.width
                        height: 80
                        radius: 8
                        color: "#f0f8ff"
                        border.color: "#d3d3d3"

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 10
                            spacing: 15

                            // 患者头像占位
                            Rectangle {
                                width: 60
                                height: 60
                                radius: 30
                                color: "#e0e0e0"
                                Layout.alignment: Qt.AlignVCenter

                                Label {
                                    text: modelData.name.charAt(0)
                                    font.pixelSize: 24
                                    anchors.centerIn: parent
                                }
                            }

                            // 患者信息
                            ColumnLayout {
                                spacing: 5

                                Label {
                                    text: modelData.name + " (" + modelData.age + "岁, " + modelData.gender + ")"
                                    font.pixelSize: 18
                                    font.bold: true
                                }

                                Label {
                                    text: "预约时间: " + modelData.time
                                    font.pixelSize: 16
                                    color: "#666"
                                }
                            }

                            // 操作按钮
                            RowLayout {
                                Layout.alignment: Qt.AlignRight
                                spacing: 10

                                Button {
                                    text: "病例详情"
                                    onClicked: {
                                        mainStack.push(patientDetailPage, {patient: modelData})
                                    }
                                }

                                Button {
                                    text: "开始就诊"
                                    onClicked: {
                                        mainStack.push(medicalAdvicePage, {patient: modelData})
                                    }
                                }
                            }
                        }
                    }
                }

                // 返回按钮
                Button {
                    text: "返回"
                    Layout.alignment: Qt.AlignRight
                    onClicked: Qt.quit()
                }
            }
        }
    }

    // 患者详情页面
    Component {
        id: patientDetailPage

        Page {
            id: detailPage
            property var patient: null

            title: "患者详情"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15

                Label {
                    text: "患者详情"
                    font.pixelSize: 24
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                // 患者基本信息
                GroupBox {
                    title: "基本信息"
                    Layout.fillWidth: true

                    GridLayout {
                        width: parent.width
                        columns: 2
                        columnSpacing: 20
                        rowSpacing: 10

                        Label { text: "姓名:"; font.bold: true }
                        Label { text: detailPage.patient.name }

                        Label { text: "年龄:"; font.bold: true }
                        Label { text: detailPage.patient.age + "岁" }

                        Label { text: "性别:"; font.bold: true }
                        Label { text: detailPage.patient.gender }

                        Label { text: "联系电话:"; font.bold: true }
                        Label { text: detailPage.patient.phone }

                        Label { text: "预约时间:"; font.bold: true }
                        Label { text: detailPage.patient.time }
                    }
                }

                // 病例详情
                GroupBox {
                    title: "病例详情"
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ScrollView {
                        anchors.fill: parent

                        TextArea {
                            text: detailPage.patient.history
                            wrapMode: TextArea.Wrap
                            readOnly: true
                            font.pixelSize: 16
                        }
                    }
                }

                // 操作按钮
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Button {
                        text: "返回"
                        Layout.fillWidth: true
                        onClicked: mainStack.pop()
                    }

                    Button {
                        text: "编辑医嘱"
                        Layout.fillWidth: true
                        onClicked: mainStack.push(medicalAdvicePage, {patient: detailPage.patient})
                    }
                }
            }
        }
    }

    // 医嘱编辑页面
    Component {
        id: medicalAdvicePage

        Page {
            id: advicePage
            property var patient: null
            property string medicalAdvice: "请在此输入医嘱..."

            title: "医嘱编辑"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 15

                Label {
                    text: "医嘱编辑 - " + advicePage.patient.name
                    font.pixelSize: 24
                    font.bold: true
                    Layout.alignment: Qt.AlignHCenter
                }

                // 患者基本信息
                GroupBox {
                    title: "患者信息"
                    Layout.fillWidth: true

                    RowLayout {
                        width: parent.width
                        spacing: 15

                        // 患者头像占位
                        Rectangle {
                            width: 80
                            height: 80
                            radius: 40
                            color: "#e0e0e0"
                            Layout.alignment: Qt.AlignVCenter

                            Label {
                                text: advicePage.patient.name.charAt(0)
                                font.pixelSize: 32
                                anchors.centerIn: parent
                            }
                        }

                        // 患者信息
                        ColumnLayout {
                            spacing: 5

                            Label {
                                text: advicePage.patient.name + " (" + advicePage.patient.age + "岁, " + advicePage.patient.gender + ")"
                                font.pixelSize: 18
                                font.bold: true
                            }

                            Label {
                                text: "预约时间: " + advicePage.patient.time
                                font.pixelSize: 16
                                color: "#666"
                            }
                        }
                    }
                }

                // 医嘱编辑区域
                GroupBox {
                    title: "医嘱内容"
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    ScrollView {
                        anchors.fill: parent

                        TextArea {
                            id: adviceText
                            text: advicePage.medicalAdvice
                            wrapMode: TextArea.Wrap
                            font.pixelSize: 16
                            onTextChanged: advicePage.medicalAdvice = text
                        }
                    }
                }

                // 操作按钮
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 10

                    Button {
                        text: "返回"
                        Layout.fillWidth: true
                        onClicked: mainStack.pop()
                    }

                    Button {
                        text: "保存医嘱"
                        Layout.fillWidth: true
                        onClicked: {
                            console.log("保存医嘱:", adviceText.text)
                            Qt.createQmlObject('import QtQuick.Controls 2.15; MessageDialog { text: "医嘱保存成功！"; visible: true }', app)
                        }
                    }

                    Button {
                        text: "打印医嘱"
                        Layout.fillWidth: true
                        onClicked: {
                            console.log("打印医嘱:", adviceText.text)
                            Qt.createQmlObject('import QtQuick.Controls 2.15; MessageDialog { text: "医嘱已发送到打印机！"; visible: true }', app)
                        }
                    }
                }
            }
        }
    }
}

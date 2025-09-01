// EditDoctorProfile.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Page {
    id: editPage
    title: "编辑医生信息"

    property var doctorData: ({
        id: "D001",
        name: "张医生",
        hospital: "市中心医院",
        department: "内科",
        profile: "主任医师，擅长心血管疾病",
        workTime: "周一至周五 上午 8:00-12:00",
        fee: 30,
        maxPatients: 20,
        photo: ""
    })

    // 照片选择对话框
    FileDialog {
        id: photoDialog
        title: "选择医生照片"
        folder: shortcuts.home
        nameFilters: ["图片文件 (*.jpg *.png *.jpeg)"]
        onAccepted: {
            doctorData.photo = photoDialog.fileUrl
            photoPreview.source = photoDialog.fileUrl
        }
    }

    // 顶部标题栏
    header: ToolBar {
        height: 60
        background: Rectangle {
            color: "#3498db"
        }

        RowLayout {
            anchors.fill: parent
            spacing: 10

            // 返回按钮（叉号）
            ToolButton {
                icon.source: "qrc:/icons/close.svg"
                icon.color: "white"
                icon.width: 30
                icon.height: 30
                onClicked: {
                    var p = editPage.parent
                    while (p && typeof p.pop !== "function") p = p.parent
                    if (p) p.pop()
                }
                background: Rectangle {
                    color: "transparent"
                }
            }

            Label {
                text: editPage.title
                font.pixelSize: 20
                color: "white"
                Layout.fillWidth: true
            }

            // 保存按钮
            ToolButton {
                text: "保存"
                font.pixelSize: 16
                font.bold: true
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    font: parent.font
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                onClicked: {
                    // 这里应该实现保存逻辑
                    console.log("保存医生信息:", JSON.stringify(doctorData))

                    // 显示保存成功消息
                    saveSuccessDialog.open()
                }
                background: Rectangle {
                    color: "transparent"
                }
            }
        }
    }

    // 保存成功对话框
    MessageDialog {
        id: saveSuccessDialog
        title: "保存成功"
        text: "医生信息已成功更新！"
        icon: StandardIcon.Information
        onAccepted: {
            var p = editPage.parent
            while (p && typeof p.pop !== "function") p = p.parent
            if (p) p.pop()
        }
    }

    // 主内容区域
    ScrollView {
        anchors.fill: parent
        anchors.margins: 20
        clip: true

        ColumnLayout {
            width: parent.width
            spacing: 20

            // 照片上传区域
            GroupBox {
                title: "医生照片"
                Layout.fillWidth: true

                ColumnLayout {
                    width: parent.width
                    spacing: 15

                    // 照片预览
                    Rectangle {
                        id: photoContainer
                        width: 150
                        height: 180
                        color: "#f0f0f0"
                        border.color: "#cccccc"
                        radius: 5
                        Layout.alignment: Qt.AlignHCenter

                        Image {
                            id: photoPreview
                            anchors.fill: parent
                            anchors.margins: 5
                            source: doctorData.photo ? doctorData.photo : "qrc:/icons/default-doctor.png"
                            fillMode: Image.PreserveAspectFit
                        }
                    }

                    // 上传按钮
                    Button {
                        text: "选择照片"
                        icon.source: "qrc:/icons/camera.svg"
                        Layout.alignment: Qt.AlignHCenter
                        onClicked: photoDialog.open()
                    }
                }
            }

            // 基本信息区域
            GroupBox {
                title: "基本信息"
                Layout.fillWidth: true

                GridLayout {
                    width: parent.width
                    columns: 2
                    columnSpacing: 15
                    rowSpacing: 15

                    Label { text: "医生编号:" }
                    TextField {
                        id: idField
                        text: doctorData.id
                        Layout.fillWidth: true
                        onTextChanged: doctorData.id = text
                    }

                    Label { text: "姓名:" }
                    TextField {
                        id: nameField
                        text: doctorData.name
                        Layout.fillWidth: true
                        onTextChanged: doctorData.name = text
                    }

                    Label { text: "所属医院:" }
                    ComboBox {
                        id: hospitalCombo
                        model: ["市中心医院", "社区医院", "儿童医院"]
                        currentIndex: model.indexOf(doctorData.hospital)
                        Layout.fillWidth: true
                        onCurrentIndexChanged: doctorData.hospital = model[currentIndex]
                    }

                    Label { text: "所属科室:" }
                    ComboBox {
                        id: departmentCombo
                        model: ["内科", "外科", "儿科", "骨科", "眼科", "耳鼻喉科"]
                        currentIndex: model.indexOf(doctorData.department)
                        Layout.fillWidth: true
                        onCurrentIndexChanged: doctorData.department = model[currentIndex]
                    }
                }
            }

            // 专业信息区域
            GroupBox {
                title: "专业信息"
                Layout.fillWidth: true

                ColumnLayout {
                    width: parent.width
                    spacing: 15

                    Label { text: "个人资料:" }
                    TextArea {
                        id: profileField
                        text: doctorData.profile
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        wrapMode: TextArea.Wrap
                        placeholderText: "请输入医生个人资料..."
                        onTextChanged: doctorData.profile = text
                    }

                    Label { text: "上班时间:" }
                    TextField {
                        id: workTimeField
                        text: doctorData.workTime
                        Layout.fillWidth: true
                        placeholderText: "例如：周一至周五 上午 8:00-12:00"
                        onTextChanged: doctorData.workTime = text
                    }

                    RowLayout {
                        spacing: 20

                        ColumnLayout {
                            Label { text: "挂号费用 (元):" }
                            SpinBox {
                                id: feeField
                                value: doctorData.fee
                                from: 0
                                to: 1000
                                stepSize: 5
                                onValueChanged: doctorData.fee = value
                            }
                        }

                        ColumnLayout {
                            Label { text: "单日患者上限:" }
                            SpinBox {
                                id: maxPatientsField
                                value: doctorData.maxPatients
                                from: 1
                                to: 100
                                stepSize: 1
                                onValueChanged: doctorData.maxPatients = value
                            }
                        }
                    }
                }
            }

            // 保存按钮区域
            Button {
                text: "保存修改"
                font.pixelSize: 16
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 10
                Layout.bottomMargin: 20
                onClicked: {
                    // 这里应该实现保存逻辑
                    console.log("保存医生信息:", JSON.stringify(doctorData))

                    // 显示保存成功消息
                    saveSuccessDialog.open()
                }
            }
        }
    }
}

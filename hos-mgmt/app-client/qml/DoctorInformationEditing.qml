// EditDoctorProfile.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.3

Page {
    id: editPage

    title: "编辑医生信息"

    // 外部可传入医生ID或姓名，用于加载医生信息
    property string doctorId: ""
    property string doctorName: ""

    property var doctorData: ({
        id: "",
        name: "",
        hospital: "",
        department: "",
        profile: "",
        workTime: "",
        fee: 0,
        maxPatients: 0,
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
            photoPreview.source = doctorData.photo
        }
    }

    // 页面加载时获取医生信息
    Component.onCompleted: {
        if (doctorId) {
            // 使用 doctorId 向后端请求医生信息
            var xhr = new XMLHttpRequest()
            xhr.open("GET", "http://127.0.0.1:8080/api/doctor/info?doctorId=" + doctorId)
            xhr.onreadystatechange = function() {
                if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {
                    var resp = JSON.parse(xhr.responseText)
                    if (resp.success && resp.info) {
                        // 填充界面字段
                        doctorData.name = resp.info.name
                        doctorData.hospital = resp.info.hospital
                        doctorData.department = resp.info.department
                        doctorData.profile = resp.info.profile
                        doctorData.workTime = resp.info.workTime
                        doctorData.fee = resp.info.fee
                        doctorData.maxPatients = resp.info.maxPatients
                        doctorData.photo = resp.info.photo
                        photoPreview.source = doctorData.photo ? doctorData.photo : "qrc:/icons/default-doctor.png"
                    }
                }
            }
            xhr.send()
        } else {
            feedbackLabel.color = "red"
            feedbackLabel.text = "未指定医生ID"
        }
    }


    // 顶部标题栏
    header: ToolBar {
        height: 60
        background: Rectangle { color: "#3498db" }

        RowLayout {
            anchors.fill: parent
            spacing: 10

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
                background: Rectangle { color: "transparent" }
            }

            Label { text: editPage.title; font.pixelSize: 20; color: "white"; Layout.fillWidth: true }

            ToolButton {
                text: "保存"
                font.pixelSize: 16
                font.bold: true
                contentItem: Text { text: parent.text; color: "white"; font: parent.font }
                onClicked: saveButton.clicked()
                background: Rectangle { color: "transparent" }
            }
        }
    }

    MessageDialog {
        id: saveSuccessDialog
        title: "保存成功"
        text: ""
        icon: StandardIcon.Information
        onAccepted: {
            var p = editPage.parent
            while (p && typeof p.pop !== "function") p = p.parent
            if (p) p.pop()
        }
    }

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
                        text: doctorData.id
                        Layout.fillWidth: true
                        onTextChanged: doctorData.id = text
                    }

                    Label { text: "姓名:" }
                    TextField {
                        text: doctorData.name
                        Layout.fillWidth: true
                        onTextChanged: doctorData.name = text
                    }

                    Label { text: "所属医院:" }
                    ComboBox {
                        model: ["市中心医院", "社区医院", "儿童医院"]
                        currentIndex: model.indexOf(doctorData.hospital)
                        Layout.fillWidth: true
                        onCurrentIndexChanged: doctorData.hospital = model[currentIndex]
                    }

                    Label { text: "所属科室:" }
                    ComboBox {
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
                        text: doctorData.profile
                        Layout.fillWidth: true
                        Layout.preferredHeight: 100
                        wrapMode: TextArea.Wrap
                        placeholderText: "请输入医生个人资料..."
                        onTextChanged: doctorData.profile = text
                    }

                    Label { text: "上班时间:" }
                    TextField {
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
                id: saveButton
                text: "保存修改"
                onClicked: {
                    feedbackLabel.color = "red"
                    feedbackLabel.text = ""

                    if (!doctorData.name) { feedbackLabel.text = "姓名不能为空"; return }

                    var xhr = new XMLHttpRequest()
                    xhr.open("POST", "http://127.0.0.1:8080/api/doctor/update")
                    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8")
                    xhr.onreadystatechange = function() {
                        if (xhr.readyState === XMLHttpRequest.DONE) {
                            try {
                                var resp = JSON.parse(xhr.responseText)
                                if (resp.success) {
                                    if (resp.info && resp.info.id) doctorData.id = resp.info.id
                                    saveSuccessDialog.text = resp.info ? resp.info : "医生信息已成功更新！"
                                    saveSuccessDialog.open()
                                } else {
                                    feedbackLabel.color = "red"
                                    feedbackLabel.text = resp.reason || "保存失败"
                                }
                            } catch(e) {
                                feedbackLabel.color = "red"
                                feedbackLabel.text = "JSON解析错误: " + e + "\n响应内容:" + xhr.responseText
                            }
                        }
                    }
                    xhr.send(JSON.stringify({
                        id: doctorData.id,
                        name: doctorData.name,
                        hospital: doctorData.hospital,
                        department: doctorData.department,
                        profile: doctorData.profile,
                        workTime: doctorData.workTime,
                        fee: doctorData.fee,
                        maxPatients: doctorData.maxPatients,
                        photo: doctorData.photo
                    }))
                }
            }

            Label { id: feedbackLabel; text:""; color:"green"; wrapMode:Text.WordWrap; Layout.fillWidth:true }
        }
    }
}

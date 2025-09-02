import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: profilePage
    title: "个人信息"

    property bool editing: false
    property string username: ""
    property string phone: ""
    property string address: ""
    property string age: ""
    property string gender: ""

    // 状态提示
    property string infoHint: ""
    property bool loading: false

    // 保存原始数据用于取消恢复
    property var rawInfo: ({})

    // 页面加载时获取个人信息
    Component.onCompleted: {
        loading = true
        infoHint = "正在加载..."
        authManager.getPatientInfo(function(username, phone, address, age, gender) {
            loading = false
            if (username === undefined) {
                infoHint = "加载失败，请重试"
                return
            }
            infoHint = ""
            profilePage.username = username
            profilePage.phone = phone
            profilePage.address = address
            profilePage.age = age
            profilePage.gender = gender
            // 保存原始数据用于取消
            rawInfo = { username, phone, address, age, gender }
        })
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Label {
            text: infoHint
            color: "red"
            visible: infoHint !== ""
            font.pointSize: 12
            horizontalAlignment: Qt.AlignHCenter
        }

        // 姓名
        Row {
            spacing: 10
            Label { text: "姓名：" }
            Loader {
                active: !editing
                sourceComponent: Label { text: profilePage.username }
            }
            Loader {
                active: editing
                sourceComponent: TextField {
                    text: profilePage.username
                    placeholderText: "请输入姓名"
                    onTextChanged: profilePage.username = text
                }
            }
        }

        // 电话
        Row {
            spacing: 10
            Label { text: "电话：" }
            Loader {
                active: !editing
                sourceComponent: Label { text: profilePage.phone }
            }
            Loader {
                active: editing
                sourceComponent: TextField {
                    text: profilePage.phone
                    placeholderText: "请输入手机号"
                    inputMethodHints: Qt.ImhDigitsOnly
                    onTextChanged: profilePage.phone = text
                }
            }
        }

        // 地址
        Row {
            spacing: 10
            Label { text: "地址：" }
            Loader {
                active: !editing
                sourceComponent: Label { text: profilePage.address }
            }
            Loader {
                active: editing
                sourceComponent: TextField {
                    text: profilePage.address
                    placeholderText: "请输入地址"
                    onTextChanged: profilePage.address = text
                }
            }
        }

        // 年龄
        Row {
            spacing: 10
            Label { text: "年龄：" }
            Loader {
                active: !editing
                sourceComponent: Label { text: profilePage.age }
            }
            Loader {
                active: editing
                sourceComponent: TextField {
                    text: profilePage.age
                    placeholderText: "请输入年龄"
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator { bottom: 1; top: 120 }
                    onTextChanged: profilePage.age = text
                }
            }
        }

        // 性别
        Row {
            spacing: 10
            Label { text: "性别：" }
            Loader {
                active: !editing
                sourceComponent: Label { text: profilePage.gender }
            }
            Loader {
                active: editing
                sourceComponent: ComboBox {
                    model: ["男", "女", "其他"]
                    currentIndex: profilePage.gender === "女" ? 1 : (profilePage.gender === "其他" ? 2 : 0)
                    onCurrentIndexChanged: profilePage.gender = model[currentIndex]
                }
            }
        }

        // 操作区
        Row {
            spacing: 20

            Button {
                text: editing ? "确认" : "修改"
                enabled: !loading && (editing ? isInputValid() : true)
                onClicked: {
                    if (!editing) {
                        editing = true
                        infoHint = ""
                    } else {
                        // 输入校验
                        if (!isInputValid()) {
                            infoHint = "请填写完整且正确的信息"
                            return
                        }
                        loading = true
                        infoHint = "正在保存..."
                        authManager.updatePatientInfo(
                            username,
                            phone,
                            address,
                            age,
                            gender,
                            function(success) {
                                loading = false
                                if (success) {
                                    editing = false
                                    rawInfo = { username, phone, address, age, gender }
                                    infoHint = "保存成功"
                                    Qt.createQmlObject('import QtQuick.Dialogs 1.2; MessageDialog { text: "保存成功"; visible: true }', profilePage)
                                } else {
                                    infoHint = "保存失败，请重试"
                                    Qt.createQmlObject('import QtQuick.Dialogs 1.2; MessageDialog { text: "保存失败"; visible: true }', profilePage)
                                }
                            }
                        )
                    }
                }
            }
            Button {
                text: editing ? "取消" : "返回"
                enabled: !loading
                onClicked: {
                    if (editing) {
                        // 恢复原信息
                        username = rawInfo.username
                        phone    = rawInfo.phone
                        address  = rawInfo.address
                        age      = rawInfo.age
                        gender   = rawInfo.gender
                        editing  = false
                        infoHint = ""
                    } else {
                        mainStackView.pop()
                    }
                }
            }
        }
    }

    // 输入校验函数
    function isInputValid() {
        if (!username || !phone || !address || !age || !gender)
            return false
        if (phone.length < 6 || phone.length > 20)
            return false
        if (isNaN(parseInt(age)) || parseInt(age) < 1 || parseInt(age) > 120)
            return false
        return true
    }
}

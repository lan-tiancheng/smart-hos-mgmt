import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.mycompany.app 1.0

Item {
    id: root
    anchors.fill: parent
    width: parent ? parent.width : 640
    height: parent ? parent.height : 480

    property bool registering: false

    Rectangle {
        anchors.fill: parent
        color: "#F2F7F2"
    }

    ColumnLayout {
        id: mainLayout
        anchors.centerIn: parent
        spacing: 20
        width: Math.min(parent.width * 0.8, 520)

        Label {
            text: "智慧医疗系统"
            font.pixelSize: 32
            font.bold: true
            color: "#1A5D1A"
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            id: userTypeLayout
            spacing: 10
            Layout.alignment: Qt.AlignHCenter
            Label { text: "我是：" }
            Switch {
                id: userTypeSwitch
                text: checked ? "医生" : "病人"
                onClicked: userTypeSwitch.text = checked ? "医生" : "病人"
            }
        }

        StackLayout {
            id: formStack
            Layout.fillWidth: true
            height: 300

            // 登录表单
            ColumnLayout {
                id: loginForm
                spacing: 10
                Layout.fillWidth: true
                visible: formStack.currentIndex === 0

                TextField { id: usernameField; placeholderText: "用户名"; Layout.fillWidth: true }
                TextField { id: passwordField; placeholderText: "密码"; echoMode: TextInput.Password; Layout.fillWidth: true }

                Label {
                    id: loginStatusLabel
                    text: "请登录或注册"
                    Layout.alignment: Qt.AlignHCenter
                    color: "red"
                    font.pixelSize: 14
                }

                Button {
                    text: "登录"
                    Layout.fillWidth: true
                    onClicked: {
                        if (!authManager || typeof authManager.requestLogin !== "function") {
                            loginStatusLabel.color = "red"
                            loginStatusLabel.text = "客户端错误：未找到登录接口"
                            return
                        }
                        loginStatusLabel.color = "#333"
                        loginStatusLabel.text = "正在登录..."
                        // 登录时也传递职业参数
                        const userTypeStr = userTypeSwitch.checked ? "doctor" : "patient"
                        authManager.requestLogin(userTypeStr, usernameField.text, passwordField.text)
                    }
                }
            }

            // 注册表单
            ColumnLayout {
                id: registerForm
                spacing: 10
                Layout.fillWidth: true
                visible: formStack.currentIndex === 1

                TextField { id: regUsernameField; placeholderText: "用户名"; Layout.fillWidth: true }
                TextField { id: regPasswordField; placeholderText: "密码"; echoMode: TextInput.Password; Layout.fillWidth: true }
                TextField { id: regPhoneField; placeholderText: "电话"; Layout.fillWidth: true }
                TextField { id: regAddressField; placeholderText: "地址"; Layout.fillWidth: true }
                TextField { id: regAgeField; placeholderText: "年龄（数字）"; Layout.fillWidth: true; inputMethodHints: Qt.ImhDigitsOnly }
                TextField { id: regGenderField; placeholderText: "性别（男/女或 male/female）"; Layout.fillWidth: true }

                Label {
                    id: regStatusLabel
                    text: ""
                    color: "red"
                    font.pixelSize: 14
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                Button {
                    text: "注册"
                    Layout.fillWidth: true
                    enabled: !registering
                    onClicked: {
                        if (!authManager || typeof authManager.requestRegister !== "function") {
                            regStatusLabel.color = "red"
                            regStatusLabel.text = "客户端错误：未找到注册接口"
                            return
                        }
                        if (!regUsernameField.text || !regPasswordField.text) {
                            regStatusLabel.color = "red"
                            regStatusLabel.text = "用户名和密码不能为空"
                            return
                        }
                        const age = parseInt(regAgeField.text)
                        if (isNaN(age) || age <= 0) {
                            regStatusLabel.color = "red"
                            regStatusLabel.text = "年龄必须是大于 0 的数字"
                            return
                        }
                        const userTypeStr = userTypeSwitch.checked ? "doctor" : "patient"
                        const phone = regPhoneField.text
                        const address = regAddressField.text
                        const gender = regGenderField.text
                        registering = true
                        regStatusLabel.color = "#333"
                        regStatusLabel.text = "正在注册..."
                        authManager.requestRegister(
                            userTypeStr,
                            regUsernameField.text,
                            regPasswordField.text,
                            phone,
                            address,
                            age,
                            gender
                        )
                    }
                }
            }
        }

        Button {
            text: formStack.currentIndex === 0 ? "没有账户？去注册" : "已有账户？去登录"
            Layout.fillWidth: true
            onClicked: {
                formStack.currentIndex = 1 - formStack.currentIndex
                loginStatusLabel.text = ""
                regStatusLabel.text = ""
                registering = false
                if (authManager && typeof authManager.setRemainingAttempts === "function") {
                    authManager.setRemainingAttempts(5)
                }
            }
        }
    }

    Connections {
        target: authManager

        function onLoginSuccess(userId, userType) {
            loginStatusLabel.color = "green"
            loginStatusLabel.text = "登录成功！UserId: " + userId
            console.log("Login success:", userId, userType)
            if (userType) {
                mainStackView.push("DoctorHomeScreen.qml")
            } else if (!userType) {
                mainStackView.push("PatientHomeScreen.qml")
            }
            else{
                console.log("Error")
            }
        }

        function onLoginFailed(reason) {
            loginStatusLabel.color = "red"
            loginStatusLabel.text = reason
        }

        function onRegisterSuccess() {
            registering = false
            regStatusLabel.color = "green"
            regStatusLabel.text = "注册成功！请登录。"
            formStack.currentIndex = 0
        }

        function onRegisterFailed(reason) {
            registering = false
            regStatusLabel.color = "red"
            regStatusLabel.text = reason || "注册失败"
        }
    }
}

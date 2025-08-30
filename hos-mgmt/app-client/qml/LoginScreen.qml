import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.mycompany.app 1.0

Item {
    id: root
    signal loginSuccess(var userType)

    anchors.fill: parent
    width: parent ? parent.width : 640
    height: parent ? parent.height : 480

    // 注册中的状态
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

        // 标题
        Label {
            text: "智慧医疗系统"
            font.pixelSize: 32
            font.bold: true
            color: "#1A5D1A"
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter
        }

        // 用户类型选择
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

        // 登录/注册切换
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
                            console.error("authManager.requestLogin() 不可用")
                            loginStatusLabel.color = "red"
                            loginStatusLabel.text = "客户端错误：未找到登录接口"
                            return
                        }
                        console.log("开始登录")
                        loginStatusLabel.color = "#333"
                        loginStatusLabel.text = "正在登录..."
                        authManager.requestLogin(usernameField.text, passwordField.text)
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

                // 注册中的进度
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 8
                    BusyIndicator {
                        running: registering
                        visible: registering
                        Layout.alignment: Qt.AlignVCenter
                    }
                    Label {
                        id: regStatusLabel
                        text: ""
                        color: registering ? "#333" : "red"
                        font.pixelSize: 14
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                    }
                }

                Button {
                    text: "注册"
                    Layout.fillWidth: true
                    enabled: !registering
                    onClicked: {
                        // 基本防御：authManager 和方法是否存在
                        if (!authManager || typeof authManager.requestRegister !== "function") {
                            console.error("authManager.requestRegister() 不可用")
                            regStatusLabel.color = "red"
                            regStatusLabel.text = "客户端错误：未找到注册接口"
                            return
                        }

                        // 输入校验
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

                        // 立即给用户反馈
                        registering = true
                        regStatusLabel.color = "#333"
                        regStatusLabel.text = "正在注册，请稍候..."
                        console.log("开始注册", userTypeStr, regUsernameField.text)

                        // 发起调用
                        authManager.requestRegister(
                            userTypeStr,
                            regUsernameField.text,
                            regPasswordField.text,
                            phone,
                            address,
                            age,
                            gender
                        )

                        // 如果 20 秒还没有回调，提示可能网络/服务异常
                        regTimeout.restart()
                    }
                }
            }
        }

        // 切换登录/注册
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

    // 超时保护
    Timer {
        id: regTimeout
        interval: 20000
        repeat: false
        onTriggered: {
            if (registering) {
                registering = false
                regStatusLabel.color = "red"
                regStatusLabel.text = "注册超时，请检查网络或服务器是否运行"
                console.warn("注册请求超时（20s 无回调）")
            }
        }
    }

    // 绑定 AuthManager 信号
    Connections {
        target: authManager

        function onLoginSuccess(userId, userType) {
            console.log("登录成功", userId, userType)
            loginStatusLabel.color = "green"
            loginStatusLabel.text = "登录成功！UserId: " + userId
            root.loginSuccess(userType)
        }

        function onLoginFailed(reason) {
            console.warn("登录失败", reason)
            loginStatusLabel.color = "red"
            loginStatusLabel.text = reason
        }

        function onRegisterSuccess() {
            console.log("注册成功")
            registering = false
            regTimeout.stop()
            regStatusLabel.color = "green"
            regStatusLabel.text = "注册成功！请登录。"
            formStack.currentIndex = 0
        }

        function onRegisterFailed(reason) {
            console.warn("注册失败", reason)
            registering = false
            regTimeout.stop()
            regStatusLabel.color = "red"
            regStatusLabel.text = reason || "注册失败"
        }
    }
}

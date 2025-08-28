import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import com.mycompany.app 1.0

Item {
    id: root
    signal loginSuccess(var userType)

    width: parent ? parent.width : 640
    height: parent ? parent.height : 480

    Rectangle {
        anchors.fill: parent
        color: "#F2F7F2"
    }

    ColumnLayout {
        id: mainLayout
        anchors.centerIn: parent
        spacing: 20
        width: parent.width * 0.8

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
                onClicked: {
                    userTypeSwitch.text = checked ? "医生" : "病人"
                }
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

                TextField {
                    id: usernameField
                    placeholderText: "用户名"
                    Layout.fillWidth: true
                }

                TextField {
                    id: passwordField
                    placeholderText: "密码"
                    echoMode: TextField.Password
                    Layout.fillWidth: true
                }

                Label {
                    id: loginStatusLabel
                    text: "请登录或注册"
                    Layout.alignment: Qt.AlignHCenter
                    color: "red"
                    font.pixelSize: 14
                }

                Button {
                    id: loginButton
                    text: "登录"
                    Layout.fillWidth: true
                    onClicked: {
                        let type = userTypeSwitch.checked ? AuthManager.Doctor : AuthManager.Patient
                        authManager.requestLogin(type, usernameField.text, passwordField.text)
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
                TextField { id: regPasswordField; placeholderText: "密码"; echoMode: TextField.Password; Layout.fillWidth: true }
                TextField { id: regPhoneField; placeholderText: "电话"; Layout.fillWidth: true }
                TextField { id: regAddressField; placeholderText: "地址"; Layout.fillWidth: true }
                TextField { id: regAgeField; placeholderText: "年龄"; Layout.fillWidth: true }
                TextField { id: regGenderField; placeholderText: "性别"; Layout.fillWidth: true }

                Label {
                    id: regStatusLabel
                    text: ""
                    Layout.alignment: Qt.AlignHCenter
                    color: "red"
                    font.pixelSize: 14
                }

                Button {
                    id: registerButton
                    text: "注册"
                    Layout.fillWidth: true
                    onClicked: {
                        let type = userTypeSwitch.checked ? AuthManager.Doctor : AuthManager.Patient
                        let age = parseInt(regAgeField.text)
                        authManager.requestRegister(type, regUsernameField.text, regPasswordField.text,
                                                    regPhoneField.text, regAddressField.text,
                                                    age, regGenderField.text)
                    }
                }
            }
        }

        // 切换登录/注册
        Button {
            id: switchFormButton
            Layout.fillWidth: true
            text: formStack.currentIndex === 0 ? "没有账户？去注册" : "已有账户？去登录"
            onClicked: {
                formStack.currentIndex = 1 - formStack.currentIndex;
                loginStatusLabel.text = "";
                regStatusLabel.text = "";
                authManager.setRemainingAttempts(5);
            }
        }
    }

    // 绑定 AuthManager 信号
    Connections {
        target: authManager
        function onLoginSuccess(userType) {
            root.loginSuccess(userType);
        }
        function onLoginFailed(reason) {
            loginStatusLabel.text = reason;
        }
        function onRegisterSuccess() {
            regStatusLabel.text = "注册成功！请登录。";
            formStack.currentIndex = 0;
        }
        function onRegisterFailed(reason) {
            regStatusLabel.text = reason;
        }
    }
}

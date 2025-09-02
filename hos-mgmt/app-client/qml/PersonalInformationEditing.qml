import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: profilePage
    title: "个人信息编辑"

    property int userId: 1
    property string userType: "patient"

    property var regexName: /^[\u4e00-\u9fa5]+$/
    property var regexDate: /^(19|20)\d{2}-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])$/
    property var regexID: /^\d{17}[\dXx]$/
    property var regexPhone:/^1[3-9]\d{9}$/
    property var regexEmail:/^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$/

    function isValidDateStrict(str) {
        var m = str.match(/^(\d{4})-(\d{2})-(\d{2})$/)
        if (!m) return false
        var y = parseInt(m[1]), mon = parseInt(m[2]), d = parseInt(m[3])
        var dt = new Date(y, mon - 1, d)
        return dt.getFullYear() === y && (dt.getMonth() + 1) === mon && dt.getDate() === d
    }

    function findStackView(item) {
        var p = item
        while (p) {
            if (p && typeof p.push === "function" && typeof p.pop === "function") return p
            p = p.parent
        }
        return null
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        Label { text: "编辑个人信息"; font.pixelSize: 22; Layout.alignment: Qt.AlignHCenter }

        RowLayout { Layout.fillWidth: true; spacing: 10
            Label { text: "姓名:"; Layout.preferredWidth: 90 }
            TextField { id: nameField; placeholderText: "请输入姓名（仅汉字）"; Layout.fillWidth: true }
        }

        RowLayout { Layout.fillWidth: true; spacing: 10
            Label { text: "出生日期:"; Layout.preferredWidth: 90 }
            TextField { id: dobField; placeholderText: "YYYY-MM-DD"; Layout.fillWidth: true }
        }

        RowLayout { Layout.fillWidth: true; spacing: 10
            Label { text: "身份证号:"; Layout.preferredWidth: 90 }
            TextField { id: idCardField; placeholderText: "18位身份证号"; Layout.fillWidth: true }
        }

        RowLayout { Layout.fillWidth: true; spacing: 10
            Label { text: "手机号:"; Layout.preferredWidth: 90 }
            TextField { id: phoneField; placeholderText: "11位手机号"; inputMethodHints: Qt.ImhDigitsOnly; Layout.fillWidth: true }
        }

        RowLayout { Layout.fillWidth: true; spacing: 10
            Label { text: "邮箱:"; Layout.preferredWidth: 90 }
            TextField { id: emailField; placeholderText: "name@example.com"; Layout.fillWidth: true }
        }

        RowLayout { Layout.fillWidth: true; spacing: 12
            Button { text: "返回"; Layout.fillWidth: true; onClicked: { var sv = findStackView(profilePage); if(sv) sv.pop() } }

            Button {
                text: "确认保存"; Layout.fillWidth: true
                onClicked: {
                    feedbackLabel.color = "red"
                    if(!regexName.test(nameField.text)) { feedbackLabel.text="姓名必须为汉字"; return }
                    if(!regexDate.test(dobField.text)||!isValidDateStrict(dobField.text)) { feedbackLabel.text="出生日期不合法"; return }
                    if(!regexID.test(idCardField.text)) { feedbackLabel.text="身份证号不合法"; return }
                    if(!regexPhone.test(phoneField.text)) { feedbackLabel.text="手机号不合法"; return }
                    if(!regexEmail.test(emailField.text)) { feedbackLabel.text="邮箱格式不正确"; return }

                    var xhr = new XMLHttpRequest()
                    xhr.open("POST", "http://127.0.0.1:8080/api/patient/update")
                    xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8")
                    xhr.onreadystatechange = function() {
                        if(xhr.readyState===XMLHttpRequest.DONE){
                            console.log("Response Text:", xhr.responseText)
                            try {
                                var resp = JSON.parse(xhr.responseText)
                                feedbackLabel.color = resp.success ? "green" : "red"
                                feedbackLabel.text = resp.success ? "保存成功！" : (resp.reason || "保存失败")
                            } catch(e) {
                                feedbackLabel.color = "red"
                                feedbackLabel.text = "JSON 解析错误: " + e + "\n响应内容: " + xhr.responseText
                            }
                        }
                    }


                    var data = {
                        userId:userId, profession:userType,
                        username:nameField.text, dob:dobField.text,
                        idCard:idCardField.text, phone:phoneField.text,
                        email:emailField.text, address:"", age:0, gender:""
                    }
                    xhr.send(JSON.stringify(data))
                }
            }

            Button { text:"清空"; Layout.fillWidth:true; onClicked:{nameField.text=""; dobField.text=""; idCardField.text=""; phoneField.text=""; emailField.text=""; feedbackLabel.text=""} }
        }

        Label { id: feedbackLabel; text:""; color:"green"; wrapMode:Text.WordWrap; Layout.fillWidth:true }
    }

    Component.onCompleted: {
        var xhr = new XMLHttpRequest()
        xhr.open("GET", "http://127.0.0.1:8080/api/patient/info?userId="+userId+"&profession="+userType)
        xhr.onreadystatechange = function(){
            if(xhr.readyState===XMLHttpRequest.DONE){
                if(xhr.status===200){
                    var resp=JSON.parse(xhr.responseText)
                    if(resp.success && resp.info){
                        nameField.text=resp.info.username||""
                        dobField.text=resp.info.dob||""
                        idCardField.text=resp.info.idCard||""
                        phoneField.text=resp.info.phone||""
                        emailField.text=resp.info.email||""
                    } else {
                        feedbackLabel.color="red"
                        feedbackLabel.text=resp.reason||"获取用户信息失败"
                    }
                } else {
                    feedbackLabel.color="red"
                    feedbackLabel.text="请求失败: "+xhr.status
                }
            }
        }
        xhr.send()
    }
}

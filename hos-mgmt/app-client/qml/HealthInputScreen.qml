import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    width: parent ? parent.width : 800
    height: parent ? parent.height : 600

    Rectangle { anchors.fill: parent; color: "#f7f8fa" }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // TabBar
        TabBar {
            id: tabBar
            Layout.fillWidth: true
            TabButton { text: "基础信息" }
            TabButton { text: "健康自测" }
        }

        // StackLayout 控制不同页面
        StackLayout {
            id: stackLayout
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex

            // ---------------- 基础信息录入 ----------------
            Item {
                ColumnLayout {
                    anchors.centerIn: parent
                    width: Math.min(parent.width * 0.7, 640)
                    spacing: 12

                    Label { text: "健康数据录入"; font.pixelSize: 22; Layout.alignment: Qt.AlignHCenter }

                    TextField {
                        id: heightField
                        placeholderText: "身高 (cm)"
                        validator: DoubleValidator { bottom: 50; top: 250 }
                        Layout.fillWidth: true
                    }
                    TextField {
                        id: weightField
                        placeholderText: "体重 (kg)"
                        validator: DoubleValidator { bottom: 10; top: 400 }
                        Layout.fillWidth: true
                    }
                    TextField {
                        id: lungField
                        placeholderText: "肺活量 (ml)"
                        validator: IntValidator { bottom: 100; top: 20000 }
                        Layout.fillWidth: true
                    }
                    TextField {
                        id: bpField
                        placeholderText: "血压 (mmHg)，例 120/80"
                        Layout.fillWidth: true
                    }

                    Label { id: resultLabel; text: ""; wrapMode: Text.WordWrap; Layout.fillWidth: true }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 10
                        Button {
                            text: "提交"
                            Layout.fillWidth: true
                            onClicked: {
                                resultLabel.text = ""
                                if (!heightField.acceptableInput || !weightField.acceptableInput ||
                                    !lungField.acceptableInput || bpField.text.trim() === "") {
                                    resultLabel.text = "请完整填写所有字段，格式正确。"
                                    return
                                }
                                // 模拟计算 BMI 和简单健康评分
                                var bmi = parseFloat(weightField.text) / Math.pow(parseFloat(heightField.text)/100, 2)
                                var lungLevel = parseInt(lungField.text)
                                var bpLevel = bpField.text.trim()
                                var overall = bmi < 18.5 ? "偏瘦" : (bmi < 24 ? "正常" : "偏胖")
                                resultLabel.text = "BMI: " + bmi.toFixed(1) + "，肺活量: " + lungLevel + "ml，血压: " + bpLevel + "，总体评估: " + overall
                            }
                        }
                        Button {
                            text: "清空"
                            onClicked: { heightField.text = ""; weightField.text=""; lungField.text=""; bpField.text=""; resultLabel.text="" }
                        }
                    }
                }
            }

            // ---------------- 健康自测 ----------------
            Item {
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 12

                    Label {
                        text: "健康自测问卷"
                        font.pixelSize: 22
                        Layout.alignment: Qt.AlignHCenter
                    }

                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        ColumnLayout {
                            id: questionLayout
                            spacing: 12
                            width: parent.width

                            property var questions: [
                                { text: "您最近是否有头痛、头晕等不适？", options: ["没有", "偶尔", "经常"] },
                                { text: "您的睡眠情况如何？", options: ["良好", "一般", "差"] },
                                { text: "饮食是否规律？", options: ["规律", "偶尔不规律", "经常不规律"] },
                                { text: "您是否有运动习惯？", options: ["每天", "每周", "几乎没有"] }
                            ]
                            property var answers: [0,0,0,0]

                            Repeater {
                                model: questionLayout.questions.length
                                delegate: ColumnLayout {
                                    spacing: 6
                                    Layout.fillWidth: true

                                    Label {
                                        text: (index+1) + ". " + questionLayout.questions[index].text
                                        wrapMode: Text.WordWrap
                                        Layout.fillWidth: true
                                    }

                                    ComboBox {
                                        model: questionLayout.questions[index].options
                                        currentIndex: 0
                                        Layout.fillWidth: true
                                        onCurrentIndexChanged: questionLayout.answers[index] = currentIndex
                                    }
                                }
                            }
                        }
                    }

                    Button {
                        text: "提交自测"
                        Layout.alignment: Qt.AlignHCenter
                        onClicked: {
                            var score = 0
                            for(var i=0; i<questionLayout.answers.length; i++) {
                                score += questionLayout.answers[i]
                            }
                            var resultText = score <= 3 ? "健康状况良好"
                                            : score <= 6 ? "健康状况一般，请注意生活习惯"
                                            : "健康状况较差，建议及时就医"
                            console.log("自测结果:", resultText)

                            // 显示结果给用户
                            resultDialogLabel.text = resultText
                            resultDialog.open()
                        }
                    }
                }
            }
        }

        // 返回按钮 - 现在位于页面底部
        Button {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            text: "返回"
            font.pixelSize: 16
            onClicked: {
                // 返回逻辑
                var p = root.parent
                while (p && typeof p.pop !== "function") p = p.parent
                if (p) p.pop()
            }
        }
    }

    // 结果显示对话框
    Dialog {
        id: resultDialog
        title: "健康自测结果"
        standardButtons: Dialog.Ok

        Label {
            id: resultDialogLabel
            wrapMode: Text.WordWrap
            font.pixelSize: 16
        }
    }
}

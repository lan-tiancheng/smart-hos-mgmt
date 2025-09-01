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
            TabButton { text: "健康评估" }
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
                                authManager.submitHealthData(parseFloat(heightField.text),
                                                             parseFloat(weightField.text),
                                                             parseInt(lungField.text),
                                                             bpField.text.trim())
                            }
                        }
                        Button {
                            text: "清空"
                            onClicked: { heightField.text = ""; weightField.text=""; lungField.text=""; bpField.text=""; resultLabel.text="" }
                        }
                    }
                }

                Connections {
                    target: authManager
                    function onHealthSubmitSuccess(bmi, lungLevel, bpLevel, overall) {
                        resultLabel.text = "BMI: " + bmi.toFixed(1) + "，肺活量: " + lungLevel + "，血压: " + bpLevel + "，总体: " + overall
                    }
                    function onHealthSubmitFailed(reason) {
                        resultLabel.text = "提交失败: " + reason
                    }
                }
            }

            // ---------------- 健康自测 & 医疗充值 ----------------
            Item {
                property var questions: [
                    { text: "您最近是否有头痛、头晕等不适？", options: ["没有", "偶尔", "经常"] },
                    { text: "您的睡眠情况如何？", options: ["良好", "一般", "差"] },
                    { text: "饮食是否规律？", options: ["规律", "偶尔不规律", "经常不规律"] },
                    { text: "您是否有运动习惯？", options: ["每天", "每周", "几乎没有"] }
                ]
                property var answers: [0, 0, 0, 0]
                property int rechargeAmount: 0

                Column {
                    anchors.centerIn: parent
                    spacing: 28

                    Label { text: "健康评估自测"; font.pixelSize: 24 }

                    Repeater {
                        model: questions.length
                        delegate: Column {
                            spacing: 6
                            Label { text: (index+1) + ". " + questions[index].text }
                            ComboBox {
                                model: questions[index].options
                                currentIndex: 0
                                onCurrentIndexChanged: answers[index] = currentIndex
                            }
                        }
                    }

                    Button {
                        text: "提交自测"
                        onClicked: {
                            var score = 0;
                            for (var i=0; i<answers.length; ++i) score += answers[i];
                            var resultText = score < 3 ? "健康状况良好"
                                            : (score < 7 ? "健康状况一般，请注意生活习惯"
                                                         : "健康状况较差，建议及时就医");
                            Qt.createQmlObject('import QtQuick.Controls 2.15; MessageDialog { text: "自测结果：'+resultText+'"; visible: true; }', parent)
                        }
                    }

                    Rectangle { height: 2; width: 320; color: "#cccccc" }

                    Label { text: "医疗充值"; font.pixelSize: 21 }
                    Row {
                        spacing: 12
                        Label { text: "充值金额（元）:" }
                        TextField {
                            width: 80
                            placeholderText: "输入金额"
                            inputMethodHints: Qt.ImhDigitsOnly
                            onTextChanged: rechargeAmount = parseInt(text) || 0
                        }
                        Button {
                            text: "充值"
                            enabled: rechargeAmount > 0
                            onClicked: {
                                Qt.createQmlObject('import QtQuick.Controls 2.15; MessageDialog { text: "充值成功！金额："+rechargeAmount+"元"; visible: true; }', parent)
                                rechargeAmount = 0
                            }
                        }
                    }
                }
            }
        }
    }
}

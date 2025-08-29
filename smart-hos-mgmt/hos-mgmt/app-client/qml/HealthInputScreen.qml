import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    width: parent ? parent.width : 800
    height: parent ? parent.height : 600

    Rectangle { anchors.fill: parent; color: "#ffffff" }

    ColumnLayout {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.7, 640)
        spacing: 10

        Label { text: "健康数据录入"; font.pixelSize: 22; Layout.alignment: Qt.AlignHCenter }

        TextField { id: heightField; placeholderText: "身高 (cm)"; validator: DoubleValidator { bottom: 50; top: 250 } Layout.fillWidth: true }
        TextField { id: weightField; placeholderText: "体重 (kg)"; validator: DoubleValidator { bottom: 10; top: 400 } Layout.fillWidth: true }
        TextField { id: lungField; placeholderText: "肺活量 (ml)"; validator: IntValidator { bottom: 100; top: 20000 } Layout.fillWidth: true }
        TextField { id: bpField; placeholderText: "血压 (mmHg)，例 120/80"; Layout.fillWidth: true }

        Label { id: resultLabel; text: ""; wrapMode: Text.WordWrap; Layout.fillWidth: true }

        RowLayout { Layout.fillWidth: true; spacing: 10
            Button {
                text: "提交"
                Layout.fillWidth: true
                onClicked: {
                    resultLabel.text = ""
                    if (!heightField.acceptableInput || !weightField.acceptableInput || !lungField.acceptableInput || bpField.text.trim() === "") {
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

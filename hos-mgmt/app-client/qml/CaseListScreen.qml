import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    title: "病例列表"

    // 硬编码病例数据（不与数据库交互）
    ListModel {
        id: caseModel
        ListElement { record_date: "2025-06-12"; department: "内科";       doctor: "张三"; diagnosis_result: "上呼吸道感染，口服对乙酰氨基酚退热，注意补水与休息" }
        ListElement { record_date: "2025-06-28"; department: "骨科";       doctor: "李四"; diagnosis_result: "左踝轻度扭伤，制动、冷敷，弹性绷带加压48小时" }
        ListElement { record_date: "2025-07-05"; department: "消化内科";   doctor: "王五"; diagnosis_result: "急性胃炎，奥美拉唑抑酸，清淡饮食，避免辛辣油腻" }
        ListElement { record_date: "2025-07-18"; department: "心内科";     doctor: "赵六"; diagnosis_result: "高血压（1级），建议家庭血压监测，氨氯地平 5mg qd" }
        ListElement { record_date: "2025-07-29"; department: "皮肤科";     doctor: "钱七"; diagnosis_result: "湿疹，外用糠酸莫米松软膏，口服氯雷他定止痒" }
        ListElement { record_date: "2025-08-03"; department: "呼吸内科";   doctor: "孙八"; diagnosis_result: "过敏性咳嗽，吸入布地奈德/福莫特罗，对症处理" }
        ListElement { record_date: "2025-08-14"; department: "神经内科";   doctor: "周九"; diagnosis_result: "紧张性头痛，规律作息，必要时布洛芬止痛" }
        ListElement { record_date: "2025-08-26"; department: "眼科";       doctor: "吴十"; diagnosis_result: "急性结膜炎，左氧氟沙星滴眼液 qid×5d，注意手卫生" }
    }

    // 计算列宽
    function colW(idx) {
        // 0:序号 1:日期 2:科室 3:主治医生 4:诊断结果(自适应)
        switch (idx) {
        case 0: return 60
        case 1: return 120
        case 2: return 140
        case 3: return 160
        default: return Math.max(300, page.width - (60+120+140+160) - 32) // 余量
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "返回"
                // 返回上一个界面（病人主页）
                onClicked: {
                    if (mainStackView) mainStackView.pop()
                    else if (StackView.view) StackView.view.pop()
                }
            }
            Label {
                text: page.title
                font.bold: true
                font.pixelSize: 18
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                Layout.fillWidth: true
            }
            Item { width: 48 } // 占位，使标题居中
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 8

        // 表头
        Frame {
            Layout.fillWidth: true
            padding: 0
            background: Rectangle { color: "#F7F7F7"; border.color: "#E0E0E0"; radius: 6 }
            RowLayout {
                width: parent.width
                height: 40
                spacing: 0
                Item { width: colW(0); height: 40
                    Label { anchors.fill: parent; text: "序号"; font.bold: true; verticalAlignment: Text.AlignVCenter; padding: 8 } }
                Item { width: colW(1); height: 40
                    Label { anchors.fill: parent; text: "日期"; font.bold: true; verticalAlignment: Text.AlignVCenter; padding: 8 } }
                Item { width: colW(2); height: 40
                    Label { anchors.fill: parent; text: "科室"; font.bold: true; verticalAlignment: Text.AlignVCenter; padding: 8 } }
                Item { width: colW(3); height: 40
                    Label { anchors.fill: parent; text: "主治医生"; font.bold: true; verticalAlignment: Text.AlignVCenter; padding: 8 } }
                Item { Layout.fillWidth: true; height: 40
                    Label { anchors.fill: parent; text: "诊断结果"; font.bold: true; verticalAlignment: Text.AlignVCenter; padding: 8 } }
            }
        }

        // 表体
        ListView {
            id: table
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 0
            model: caseModel

            delegate: Frame {
                width: ListView.view.width
                padding: 0
                background: Rectangle {
                    color: (index % 2 === 0) ? "#FFFFFF" : "#FAFAFA"
                    border.color: "#EDEDED"
                }

                RowLayout {
                    width: parent.width
                    height: 42
                    spacing: 0

                    // 序号
                    Item { width: colW(0); height: 42
                        Label { anchors.fill: parent; padding: 8; text: (index + 1).toString(); color: "#333"; verticalAlignment: Text.AlignVCenter } }
                    // 日期
                    Item { width: colW(1); height: 42
                        Label { anchors.fill: parent; padding: 8; text: record_date; color: "#333"; verticalAlignment: Text.AlignVCenter } }
                    // 科室
                    Item { width: colW(2); height: 42
                        Label { anchors.fill: parent; padding: 8; text: department; color: "#333"; verticalAlignment: Text.AlignVCenter } }
                    // 主治医生
                    Item { width: colW(3); height: 42
                        Label { anchors.fill: parent; padding: 8; text: doctor; color: "#333"; verticalAlignment: Text.AlignVCenter } }
                    // 诊断结果
                    Item { Layout.fillWidth: true; height: 42
                        Label {
                            id: diag
                            anchors.fill: parent; padding: 8
                            text: diagnosis_result
                            color: "#333"; elide: Text.ElideRight
                            verticalAlignment: Text.AlignVCenter
                            ToolTip.visible: ma.containsMouse && diag.truncated
                            ToolTip.text: diag.text
                            ToolTip.delay: 400
                            MouseArea { id: ma; anchors.fill: parent; hoverEnabled: true; acceptedButtons: Qt.NoButton }
                        }
                    }
                }
            }
        }
    }
}

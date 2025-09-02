import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    title: "医嘱列表"

    // 硬编码医嘱数据（不与数据库交互）
    ListModel {
        id: prescriptionModel
        ListElement { record_date: "2025-06-12"; department: "内科"; doctor: "张三"; prescription: "对乙酰氨基酚 500mg q8h，口服 5 天" }
        ListElement { record_date: "2025-06-28"; department: "骨科"; doctor: "李四"; prescription: "左踝支具固定，冰敷 48 小时" }
        ListElement { record_date: "2025-07-05"; department: "消化内科"; doctor: "王五"; prescription: "奥美拉唑 20mg qd，清淡饮食" }
        ListElement { record_date: "2025-07-18"; department: "心内科"; doctor: "赵六"; prescription: "氨氯地平 5mg qd，家庭血压监测" }
        ListElement { record_date: "2025-07-29"; department: "皮肤科"; doctor: "钱七"; prescription: "糠酸莫米松软膏外用，口服氯雷他定 qd" }
        ListElement { record_date: "2025-08-03"; department: "呼吸内科"; doctor: "孙八"; prescription: "布地奈德/福莫特罗吸入，按需使用" }
        ListElement { record_date: "2025-08-14"; department: "神经内科"; doctor: "周九"; prescription: "布洛芬止痛，规律作息" }
        ListElement { record_date: "2025-08-26"; department: "眼科"; doctor: "吴十"; prescription: "左氧氟沙星滴眼液 qid×5d，注意手卫生" }
    }

    function colW(idx) {
        switch(idx) {
        case 0: return 60;  // 序号
        case 1: return 120; // 日期
        case 2: return 140; // 科室
        case 3: return 160; // 主治医生
        default: return Math.max(300, page.width - (60+120+140+160) - 60) // 处方+按钮余量
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "返回"
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
            Item { width: 48 }
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
                    Label { anchors.fill: parent; text: "处方"; font.bold: true; verticalAlignment: Text.AlignVCenter; padding: 8 } }
                Item { width: 80; height: 40
                    Label { anchors.fill: parent; text: "操作"; font.bold: true; verticalAlignment: Text.AlignVCenter; padding: 8 } }
            }
        }

        // 表体
        ListView {
            id: table
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            spacing: 0
            model: prescriptionModel

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
                        Label { anchors.fill: parent; padding: 8; text: (index+1).toString(); color: "#333"; verticalAlignment: Text.AlignVCenter } }
                    // 日期
                    Item { width: colW(1); height: 42
                        Label { anchors.fill: parent; padding: 8; text: record_date; color: "#333"; verticalAlignment: Text.AlignVCenter } }
                    // 科室
                    Item { width: colW(2); height: 42
                        Label { anchors.fill: parent; padding: 8; text: department; color: "#333"; verticalAlignment: Text.AlignVCenter } }
                    // 主治医生
                    Item { width: colW(3); height: 42
                        Label { anchors.fill: parent; padding: 8; text: doctor; color: "#333"; verticalAlignment: Text.AlignVCenter } }
                    // 处方内容
                    Item { Layout.fillWidth: true; height: 42
                        Label {
                            id: presc
                            anchors.fill: parent; padding: 8
                            text: prescription
                            color: "#333"
                            elide: Text.ElideRight
                            verticalAlignment: Text.AlignVCenter
                            ToolTip.visible: ma.containsMouse && presc.truncated
                            ToolTip.text: presc.text
                            ToolTip.delay: 400
                            MouseArea { id: ma; anchors.fill: parent; hoverEnabled: true; acceptedButtons: Qt.NoButton }
                        }
                    }
                    // 详情按钮
                    Item { width: 80; height: 42
                        Button {
                            anchors.fill: parent
                            text: "详情"
                            onClicked: {
                                // 弹出一个 MessageDialog 显示完整处方
                                messageDialog.title = "处方详情"
                                messageDialog.text = prescription
                                messageDialog.open()
                            }
                        }
                    }
                }
            }
        }
    }

    MessageDialog {
        id: messageDialog
        icon: StandardIcon.Information
        standardButtons: StandardButton.Ok
    }
}

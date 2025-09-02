import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    anchors.fill: parent
    anchors.margins: 24
    color: "white"

    property string query: ""
    property var drugResults: []

    ColumnLayout {
        anchors.fill: parent
        spacing: 18

        RowLayout {
            spacing: 10
            Layout.alignment: Qt.AlignLeft

            TextField {
                id: searchField
                placeholderText: "请输入药品名称"
                Layout.preferredWidth: 250
                onAccepted: {
                    searchDrug(searchField.text)
                }
            }
            Button {
                text: "搜索"
                Layout.preferredWidth: 80
                onClicked: searchDrug(searchField.text)
            }
        }


        // 展示搜索结果
        ListView {
            id: listView
            model: drugResults
            clip: true
            Layout.fillWidth: true
            Layout.fillHeight: true

            delegate: Rectangle {
                width: listView.width
                height: 180
                color: "#f7fdf7"
                border.color: "#d5d5d5"
                radius: 10
                anchors.margins: 10
                RowLayout {
                    anchors.fill: parent
                    spacing: 18
                    Image {
                        source: model.imgUrl
                        width: 120
                        height: 120
                        fillMode: Image.PreserveAspectFit
                        Rectangle { // 占位
                            anchors.fill: parent
                            visible: !model.imgUrl
                            color: "#efefef"
                            Label {
                                anchors.centerIn: parent
                                text: "暂无图片"
                                color: "#999"
                            }
                        }
                    }
                    ColumnLayout {
                        spacing: 5
                        Label { text: "药品名称：" + model.name; font.bold: true }
                        Label { text: "药品信息：" + model.info }
                        Label { text: "使用说明：" + model.usage }
                        Label { text: "注意事项：" + model.caution; color: "#cc0000" }
                    }
                }
            }
        }
    }

    // 假设 client.getDrugList 支持搜索
    function searchDrug(name) {
        if (!name || name.trim() === "")
            return;
        // TODO: 替换为你的真实接口获取药品数据
        client.getDrugList(name, function(results) {
            drugResults = results
        })
    }
}

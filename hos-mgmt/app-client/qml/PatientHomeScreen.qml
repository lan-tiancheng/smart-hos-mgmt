import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    title: "患者主界面"

    // 可按需修改：支付后端地址（OnlinePayScreen 会自动创建订单并轮询）
    property string payApiBase: "http://127.0.0.1:3000"

    // 统一用 qrc 绝对路径，避免相对路径导致的找不到页面
    function pageUrl(fileName) { return "qrc:/client/qml/qml/" + fileName }

    // 动态列数：根据宽度计算
    readonly property int tileWidth: 160
    readonly property int tileHSpacing: 24
    readonly property int tileVSpacing: 20
    readonly property int columnsDynamic: Math.max(2, Math.floor((contentItem.width - 32) / (tileWidth + tileHSpacing)))

    // 通用图标默认占位
    readonly property url defaultIcon: "qrc:/icons/default.svg"

    // 单个操作卡片（可复用）
    Component {
        id: tileButtonComponent
        Button {
            id: tile
            property url iconSource: defaultIcon
            property color baseColor: "#FFFFFF"
            property color borderColor: "#E0E0E0"
            property color hoverColor: "#F5F5F5"

            implicitWidth: tileWidth
            implicitHeight: 120
            hoverEnabled: true

            background: Rectangle {
                radius: 12
                color: tile.down ? "#E8F5E9" : (tile.hovered ? hoverColor : baseColor)
                border.color: borderColor
                Behavior on color { ColorAnimation { duration: 120 } }
            }

            contentItem: Column {
                anchors.centerIn: parent
                spacing: 8
                Image {
                    source: tile.iconSource || defaultIcon
                    width: 36; height: 36
                    sourceSize.width: 72; sourceSize.height: 72
                    fillMode: Image.PreserveAspectFit
                }
                Label {
                    text: tile.text
                    font.bold: true
                    color: "#212121"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    width: tile.width - 24
                    elide: Text.ElideRight
                }
            }
        }
    }

    // 可滚动内容，适配小屏
    ScrollView {
        anchors.fill: parent
        clip: true

        ColumnLayout {
            id: rootLayout
            width: Math.max(360, parent.width)
            anchors.margins: 16
            spacing: 16

            // 标题与副标题
            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: 6
                Label {
                    text: "患者服务中心"
                    font.pixelSize: 30
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter
                }
                Label {
                    text: "请选择需要的服务"
                    color: "#757575"
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter
                }
            }

            // 快速入口：两项横排
            RowLayout {
                Layout.alignment: Qt.AlignHCenter
                spacing: tileHSpacing

                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "健康评估"
                        item.iconSource = "qrc:/icons/health.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("HealthInputScreen.qml"))
                        })
                    }
                }
                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "个人信息"
                        item.iconSource = "qrc:/icons/profile.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("PatientProfileScreen.qml"))
                        })
                    }
                }
            }

            // 功能区：自适应栅格
            GridLayout {
                id: grid
                Layout.fillWidth: true
                columns: columnsDynamic
                rowSpacing: tileVSpacing
                columnSpacing: tileHSpacing
                Layout.topMargin: 8
                Layout.bottomMargin: 16

                // 挂号
                Loader {
                    sourceComponent: tileButtonComponent
                    Layout.preferredWidth: tileWidth
                    onLoaded: {
                        item.text = "挂号"
                        item.iconSource = "qrc:/icons/register.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("DoctorListScreen.qml"))
                        })
                    }
                }

                // 查看医生信息
                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "查看医生信息"
                        item.iconSource = "qrc:/icons/doctor.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("DoctorListScreen.qml"))
                        })
                    }
                }

                // 查看病例
                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "查看病例"
                        item.iconSource = "qrc:/icons/case.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("CaseListScreen.qml"))
                        })
                    }
                }

                // 预约就诊
                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "预约就诊"
                        item.iconSource = "qrc:/icons/appointment.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("AppointmentScreen.qml"))
                        })
                    }
                }

                // 药品搜索
                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "药品搜索"
                        item.iconSource = "qrc:/icons/drug.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("DrugSearchScreen.qml"))
                        })
                    }
                }

                // 住院信息（若无页面，可先跳到患者信息或提示）
                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "住院信息"
                        item.iconSource = "qrc:/icons/hospital.svg"
                        item.onClicked.connect(function() {
                            // 若已有 HospitalInfoScreen.qml，请改为 pageUrl("HospitalInfoScreen.qml")
                            mainStackView.push(pageUrl("PatientProfileScreen.qml"))
                        })
                    }
                }

                // 线上支付：带入后端地址，OnlinePayScreen 将自动创建订单+轮询
                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "线上支付"
                        item.iconSource = "qrc:/icons/pay.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("OnlinePayScreen.qml"), {
                                apiBase: payApiBase,
                                amountFen: 12800,
                                description: "挂号费"
                            })
                        })
                    }
                }

                // 医疗助手
                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "医疗助手"
                        item.iconSource = "qrc:/icons/ai.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("GLMAiChatScreen.qml"))
                        })
                    }
                }
                Loader {
                    sourceComponent: tileButtonComponent
                    onLoaded: {
                        item.text = "查看医嘱"
                        item.iconSource = "qrc:/icons/adv.svg"
                        item.onClicked.connect(function() {
                            mainStackView.push(pageUrl("DocAdvice.qml"))
                        })
                    }
                }
            }
        }
    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.12

Page {
    id: page
    title: "医生主界面"

    // 登录页会传入这些参数
    property int doctorId: -1
    property string doctorName: ""
    property string apiBase: "http://127.0.0.1:8080"
    property string wsUrl: ""
    property string token: ""

    // 主题与尺寸
    property int iconSizePx: 26
    readonly property color cBlue:  "#5AA9FF"
    readonly property color cPink:  "#FF9AC2"
    readonly property color cText:  "#0F1B2D"
    readonly property color cGlass: "#FFFFFFCC"
    readonly property color cStroke:"#FFFFFF66"

    // ============ 背景：柔和渐变 + 两个柔光圆 ============
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#E6F2FF" }
            GradientStop { position: 0.5; color: "#FDFDFF" }
            GradientStop { position: 1.0; color: "#FFE9F3" }
        }
        Rectangle { // 左上蓝光
            width: Math.max(220, parent.width * 0.22)
            height: width
            radius: width/2
            color: cBlue
            opacity: 0.22
            y: parent.height * 0.18
            x: -width * 0.3
        }
        Rectangle { // 右下粉光
            width: Math.max(260, parent.width * 0.26)
            height: width
            radius: width/2
            color: cPink
            opacity: 0.20
            x: parent.width * 0.65
            y: parent.height * 0.62
        }
    }

    // ============ 中央玻璃面板 ============
    Item {
        anchors.centerIn: parent
        width: Math.min(page.width * 0.92, 1000)
        height: Math.min(page.height * 0.88, 620)

        Rectangle {
            id: glass
            anchors.fill: parent
            color: cGlass
            radius: 22
            border.color: cStroke; border.width: 1
        }
        DropShadow {
            anchors.fill: glass; source: glass
            radius: 26; samples: 32; horizontalOffset: 0; verticalOffset: 14
            color: "#33000000"
        }

        // ============ 内容 ============
        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 28
            spacing: 18

            // 顶部信息（保留“会话列表”入口）
            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                ColumnLayout {
                    Layout.fillWidth: true
                    Label {
                        text: "医生主界面"
                        color: cText
                        font.pixelSize: 30
                        font.bold: true
                    }
                    Label {
                        text: "欢迎，" + (page.doctorName || "医生") + (page.doctorId > 0 ? (" · #" + page.doctorId) : "")
                        color: "#5C6C80"
                        font.pixelSize: 13
                    }
                }

                RowLayout {
                    spacing: 8
                    Button {
                        text: "会话列表"
                        onClicked: {
                            var params = {
                                doctorId: page.doctorId,
                                doctorName: page.doctorName,
                                apiBase: page.apiBase,
                                wsUrl: page.wsUrl,
                                token: page.token
                            }
                            if (typeof mainStackView !== "undefined" && mainStackView.push) {
                                mainStackView.push("qrc:/client/qml/qml/DoctorConversationListScreen.qml", params)
                            } else {
                                console.log("未找到 mainStackView")
                            }
                        }
                    }
                    Button {
                        text: "退出登录"
                        onClicked: {
                            if (typeof mainStackView !== "undefined" && mainStackView.pop)
                                mainStackView.pop()
                        }
                    }
                }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: "#FFFFFF66" }

            // 欢迎横幅
            Rectangle {
                Layout.fillWidth: true
                height: 86
                radius: 16
                color: "#FFFFFFAA"
                border.color: "#FFFFFF66"
                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12
                    Rectangle {
                        width: 52; height: 52; radius: 26
                        color: "#FFFFFF"
                        border.color: "#FFFFFF88"
                        Label { anchors.centerIn: parent; text: "🩺"; font.pixelSize: 24 }
                    }
                    ColumnLayout {
                        Layout.fillWidth: true
                        Label { text: "智慧医疗 · 医生工作台"; color: cText; font.bold: true }
                        Label { text: "快速查看个人信息、预约安排、考勤与请假"; color: "#6B7B93"; font.pixelSize: 12 }
                    }
                }
            }

            // ============ 功能区（按钮栅格） ============
            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 4
                rowSpacing: 18
                columnSpacing: 18

                // 统一样式按钮组件
                Component {
                    id: glassButton
                    Button {
                        display: AbstractButton.TextUnderIcon
                        icon.width: iconSizePx
                        icon.height: iconSizePx
                        font.pixelSize: 13
                        padding: 14
                        background: Rectangle {
                            radius: 14
                            color: "#FFFFFFB3"
                            border.color: "#FFFFFF80"
                            layer.enabled: true
                            layer.effect: DropShadow {
                                horizontalOffset: 0; verticalOffset: 6
                                radius: 16; samples: 24; color: "#1A000000"
                            }
                        }
                        scale: hovered ? 1.04 : 1.0
                        Behavior on scale { NumberAnimation { duration: 120 } }
                    }
                }

                // 第一排按钮
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "个人信息"
                        item.icon.source = "qrc:/client/qml/images/profile.svg"
                        item.onClicked.connect(function() {
                            var params = {
                                doctorId: page.doctorId,
                                doctorName: page.doctorName,
                                apiBase: page.apiBase,
                                wsUrl: page.wsUrl,
                                token: page.token
                            }
                            if (typeof mainStackView !== "undefined" && mainStackView.push)
                                mainStackView.push("qrc:/client/qml/qml/DoctorProfileScreen.qml", params)
                        })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "预约信息"
                        item.icon.source = "qrc:/client/qml/images/appointment.svg"
                        item.onClicked.connect(function() {
                            var params = {
                                doctorId: page.doctorId,
                                doctorName: page.doctorName,
                                apiBase: page.apiBase,
                                wsUrl: page.wsUrl,
                                token: page.token
                            }
                            if (typeof mainStackView !== "undefined" && mainStackView.push)
                                mainStackView.push("qrc:/client/qml/qml/DoctorAppointmentScreen.qml", params)
                        })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "考勤打卡"
                        item.icon.source = "qrc:/client/qml/images/register.svg"
                        item.onClicked.connect(function() {
                            var params = {
                                doctorId: page.doctorId,
                                doctorName: page.doctorName,
                                apiBase: page.apiBase,
                                wsUrl: page.wsUrl,
                                token: page.token
                            }
                            if (typeof mainStackView !== "undefined" && mainStackView.push)
                                mainStackView.push("qrc:/client/qml/qml/DoctorAttendanceScreen.qml", params)
                        })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "请假 / 销假"
                        item.icon.source = "qrc:/client/qml/images/room.svg"
                        item.onClicked.connect(function() {
                            var params = {
                                doctorId: page.doctorId,
                                doctorName: page.doctorName,
                                apiBase: page.apiBase,
                                wsUrl: page.wsUrl,
                                token: page.token
                            }
                            if (typeof mainStackView !== "undefined" && mainStackView.push)
                                mainStackView.push("qrc:/client/qml/qml/DoctorLeaveScreen.qml", params)
                        })
                    }
                }

                // 第二排按钮
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "会话中心"
                        item.icon.source = "qrc:/client/qml/images/chat.svg"
                        item.onClicked.connect(function() {
                            var params = {
                                doctorId: page.doctorId,
                                doctorName: page.doctorName,
                                apiBase: page.apiBase,
                                wsUrl: page.wsUrl,
                                token: page.token
                            }
                            if (typeof mainStackView !== "undefined" && mainStackView.push)
                                mainStackView.push("qrc:/client/qml/qml/DoctorConversationListScreen.qml", params)
                        })
                    }
                }
                Loader {
                    Layout.fillWidth: true
                    sourceComponent: glassButton
                    onLoaded: {
                        item.text = "远端数据采集"
                        item.icon.source = "qrc:/client/qml/images/register.svg"
                        item.onClicked.connect(function() {
                            var params = {
                                doctorId: page.doctorId,
                                doctorName: page.doctorName,
                                apiBase: page.apiBase,
                                wsUrl: page.wsUrl,
                                token: page.token
                            }
                            if (typeof mainStackView !== "undefined" && mainStackView.push)
                                mainStackView.push("qrc:/client/qml/qml/DoctorRemoteDataScreen.qml", params)
                        })
                    }
                }
                Item { Layout.fillWidth: true }
                Item { Layout.fillWidth: true }
            }
        }
    }
}

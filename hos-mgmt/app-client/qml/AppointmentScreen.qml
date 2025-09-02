import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Particles 2.0
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.12

Page {
    id: page
    title: "预约就诊 · Ultra华丽无模糊版"

    /* ========== 尺寸工具：rpx / wh ========== */
    readonly property real _baseW: 1280
    readonly property real _baseH: 800
    readonly property real _scale: Math.min(width / _baseW, height / _baseH)
    function rpx(v) { return v * _scale }
    function wh(p)  { return page.width * p }

    /* ========== 业务数据 ========== */
    property var hospitalList:  [ {id: 1, name:"市医院"}, {id:2, name:"区医院"} ]
    property var departmentList:[ {id: 1, name:"内科"},   {id:2, name:"外科"} ]
    property var clinicList:    [ {id: 1, name:"普通门诊"}, {id:2, name:"专家门诊"} ]
    property var doctorResults: []

    property int selectedHospital:  -1
    property int selectedDepartment:-1
    property int selectedClinic:    -1
    property string selectedDate:   ""
    property var dateList:          []

    property bool loading: false

    /* ========== 主题色 ========== */
    readonly property color cAccent:   "#6C63FF"
    readonly property color cAccent2:  "#00E1FF"
    readonly property color cGlass:    "#30FFFFFF"
    readonly property color cCard:     "#45FFFFFF"

    Material.accent: cAccent
    Material.primary: cAccent2
    Material.theme: Material.Dark

    /* ========== 初始化日期 ========== */
    Component.onCompleted: {
        var today = new Date()
        for (var i = 0; i < 30; ++i) {
            var d = new Date(today.getTime() + i * 86400000)
            dateList.push(Qt.formatDate(d, "yyyy-MM-dd"))
        }
        selectedDate = dateList.length > 0 ? dateList[0] : ""
    }

    /* ========== 背景层：动态渐变 + 粒子 ========== */
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#101431" }
            GradientStop { position: 1.0; color: "#0E1024" }
        }

        ParticleSystem { id: ps }
        Emitter {
            system: ps
            anchors.fill: parent
            emitRate: 3
            lifeSpan: 8000
            size: rpx(50)
            sizeVariation: rpx(30)
            velocity: AngleDirection { angleVariation: 360; magnitude: 10; magnitudeVariation: 5 }
        }
        ImageParticle {
            system: ps
            source: "images/svg/bg_orb.svg"
            color: "#FFFFFF"
            alpha: 0.15
            entryEffect: ImageParticle.Fade
        }
    }

    /* ========== 标题 ========== */
    Column {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: rpx(6)
        anchors.topMargin: rpx(24)

        Text {
            text: "预约就诊"
            font.pixelSize: rpx(34)
            font.bold: true
            color: "white"
        }
        Text {
            text: "选择条件，发现可预约医生"
            color: "#CDE3FF"
            font.pixelSize: rpx(14)
        }
    }

    /* ========== 主卡片容器（无模糊） ========== */
    Rectangle {
        anchors {
            left: parent.left; right: parent.right
            top: parent.top; bottom: parent.bottom
            topMargin: rpx(100); leftMargin: rpx(24); rightMargin: rpx(24); bottomMargin: rpx(24)
        }
        radius: rpx(20)
        color: cGlass
        border.color: "#80FFFFFF"; border.width: 1

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: rpx(20)
            spacing: rpx(16)

            /* ===== 条件选择 ===== */
            RowLayout {
                Layout.fillWidth: true
                spacing: rpx(12)

                // 日期
                ComboBox {
                    id: dateCombo
                    model: dateList
                    currentIndex: selectedDate === "" ? -1 : dateList.indexOf(selectedDate)
                    onCurrentIndexChanged: selectedDate = currentIndex >= 0 ? dateList[currentIndex] : ""
                    Layout.preferredWidth: wh(0.2)
                    implicitHeight: rpx(36)
                }
                // 医院
                ComboBox {
                    id: hospitalBox
                    model: hospitalList
                    textRole: "name"
                    currentIndex: selectedHospital
                    onCurrentIndexChanged: selectedHospital = currentIndex
                    Layout.preferredWidth: wh(0.2)
                    implicitHeight: rpx(36)
                }
                // 科室
                ComboBox {
                    id: departmentBox
                    model: departmentList
                    textRole: "name"
                    currentIndex: selectedDepartment
                    onCurrentIndexChanged: selectedDepartment = currentIndex
                    Layout.preferredWidth: wh(0.2)
                    implicitHeight: rpx(36)
                }
                // 门诊
                ComboBox {
                    id: clinicBox
                    model: clinicList
                    textRole: "name"
                    currentIndex: selectedClinic
                    onCurrentIndexChanged: selectedClinic = currentIndex
                    Layout.preferredWidth: wh(0.2)
                    implicitHeight: rpx(36)
                }

                // 搜索按钮
                Button {
                    id: searchBtn
                    text: "搜索医生 🔍"
                    enabled: selectedHospital >= 0 && selectedDepartment >= 0 && selectedClinic >= 0 && selectedDate !== "" && !loading
                    Layout.preferredWidth: rpx(160)
                    Layout.preferredHeight: rpx(44)
                    background: Rectangle {
                        radius: rpx(22)
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: page.cAccent }
                            GradientStop { position: 1.0; color: page.cAccent2 }
                        }
                        opacity: searchBtn.enabled ? 1.0 : 0.4
                    }
                    onClicked: {
                        loading = true
                        client.searchDoctors({
                            date: selectedDate,
                            hospitalId: hospitalList[selectedHospital].id,
                            departmentId: departmentList[selectedDepartment].id,
                            clinicId: clinicList[selectedClinic].id
                        }, function(results) {
                            doctorResults = results
                            loading = false
                        })
                    }
                }
            }

            /* ===== 医生列表 ===== */
            ListView {
                id: doctorListView
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: doctorResults
                spacing: rpx(10)

                delegate: Rectangle {
                    id: card
                    width: doctorListView.width
                    height: rpx(120)
                    radius: rpx(12)
                    color: page.cCard
                    border.width: 1
                    border.color: h.hovered ? page.cAccent2 : "#50FFFFFF"

                    property var doc: (typeof modelData === "undefined") ? model : modelData
                    HoverHandler { id: h }
                    scale: h.hovered ? 1.02 : 1.0
                    Behavior on scale { NumberAnimation { duration: 150 } }

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: rpx(12)
                        spacing: rpx(10)

                        // 头像图标 / Emoji
                        Rectangle {
                            width: rpx(64); height: rpx(64)
                            radius: rpx(8)
                            color: "#2AFFFFFF"
                            Text {
                                anchors.centerIn: parent
                                text: "\uD83D\uDC68\u200D⚕️" // 🧑‍⚕️ 医生emoji
                                font.pixelSize: rpx(32)
                            }
                        }

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: rpx(6)
                            Text { text: "医生：" + (doc && doc.name ? doc.name : "未知"); color: "white"; font.pixelSize: rpx(18); font.bold: true }
                            Text { text: "科室：" + (doc && doc.department ? doc.department : "-"); color: "#EAF2FF"; font.pixelSize: rpx(14) }
                            Text { text: "职称：" + (doc && doc.title ? doc.title : "-"); color: "#EAF2FF"; font.pixelSize: rpx(14) }
                            Text { text: "门诊时间：" + (doc && doc.workTime ? doc.workTime : "-"); color: "#EAF2FF"; font.pixelSize: rpx(14) }
                        }

                        Button {
                            text: (doc && doc.canReserve) ? "预约 ✅" : "不可约 ❌"
                            enabled: doc && !!doc.canReserve
                            Layout.preferredWidth: rpx(100)
                            Layout.preferredHeight: rpx(36)
                            background: Rectangle {
                                radius: rpx(18)
                                gradient: Gradient {
                                    GradientStop { position: 0.0; color: page.cAccent }
                                    GradientStop { position: 1.0; color: page.cAccent2 }
                                }
                                opacity: enabled ? 1.0 : 0.4
                            }
                            onClicked: {
                                mainStackView.push("RegisterAppointmentScreen.qml", {
                                    doctorId: doc.id,
                                    date: selectedDate,
                                    hospitalId: hospitalList[selectedHospital].id,
                                    departmentId: departmentList[selectedDepartment].id,
                                    clinicId: clinicList[selectedClinic].id
                                })
                            }
                        }
                    }
                }
            }
        }
    }
}

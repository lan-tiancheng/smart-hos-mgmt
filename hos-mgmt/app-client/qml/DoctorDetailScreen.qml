import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    title: "医生详细信息"

    // 由列表页传入的医生对象（兼容驼峰/下划线）
    property var doctor: ({
        name: "",
        workId: "",
        work_id: "",
        department: "",
        personalProfile: "",
        personal_profile: "",
        photoUrl: "",
        photo_url: "",
        workStart: "",
        workEnd: "",
        work_start: "",
        work_end: "",
        working_hours: {}, // { start: "09:00", end: "17:00" }
        consultationFee: "",
        consultation_fee: "",
        dailyLimit: 0,
        daily_limit: 0
    })

    function val(a, b, fallback) {
        if (a !== undefined && a !== null && a !== "") return a
        if (b !== undefined && b !== null && b !== "") return b
        return (fallback !== undefined) ? fallback : ""
    }
    function workStartStr() {
        if (doctor.working_hours && doctor.working_hours.start) return doctor.working_hours.start
        return val(doctor.workStart, doctor.work_start, "--:--")
    }
    function workEndStr() {
        if (doctor.working_hours && doctor.working_hours.end) return doctor.working_hours.end
        return val(doctor.workEnd, doctor.work_end, "--:--")
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "返回"
                onClicked: {
                    // 直接返回患者主页：弹出到栈底（首页）
                    if (mainStackView && mainStackView.depth > 1) {
                        mainStackView.pop(mainStackView.get(0))
                    } else if (StackView.view && StackView.view.depth > 1) {
                        StackView.view.pop(StackView.view.get(0))
                    }
                }
            }
            Label {
                text: page.title
                font.pixelSize: 18
                font.bold: true
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                Layout.fillWidth: true
            }
            Item { width: 48 } // 占位
        }
    }

    Flickable {
        anchors.fill: parent
        contentWidth: width
        contentHeight: contentCol.implicitHeight
        clip: true

        ColumnLayout {
            id: contentCol
            width: parent.width
            spacing: 16
            anchors.margins: 16

            RowLayout {
                spacing: 16
                Layout.fillWidth: true

                Rectangle {
                    width: 96
                    height: 96
                    radius: 8
                    color: "#EEE"
                    border.color: "#DDD"
                    clip: true

                    Image {
                        anchors.fill: parent
                        source: val(doctor.photoUrl, doctor.photo_url, "")
                        fillMode: Image.PreserveAspectCrop
                    }
                    Label {
                        visible: (val(doctor.photoUrl, doctor.photo_url, "") === "")
                        anchors.centerIn: parent
                        text: "无照片"
                        color: "#666"
                        font.pixelSize: 12
                    }
                }

                ColumnLayout {
                    spacing: 6
                    Layout.fillWidth: true
                    Label { text: "姓名：" + val(doctor.name, doctor.realname, "—"); font.pixelSize: 16; color: "#222" }
                    Label { text: "工号：" + val(doctor.workId, doctor.work_id, "—"); color: "#444" }
                    Label { text: "科室：" + val(doctor.department, doctor.dept, "—"); color: "#444" }
                }
            }

            Rectangle { Layout.fillWidth: true; height: 1; color: "#EAEAEA" }

            GroupBox {
                title: "个人资料"
                Layout.fillWidth: true
                Label {
                    text: val(doctor.personalProfile, doctor.personal_profile, "—")
                    wrapMode: Text.WordWrap
                    width: parent.width - 24
                    anchors.margins: 12
                    anchors.left: parent.left
                    anchors.right: parent.right
                }
            }

            GroupBox {
                title: "出诊与费用"
                Layout.fillWidth: true
                ColumnLayout {
                    width: parent.width
                    anchors.margins: 12
                    Label { text: "上班时间：" + workStartStr() + " - " + workEndStr() }
                    Label { text: "挂号费用：" + (val(doctor.consultationFee, doctor.consultation_fee, "") || "—") }
                    Label { text: "单日患者上限：" + (val(doctor.dailyLimit, doctor.daily_limit, "") || "—") }
                }
            }

            Item { Layout.preferredHeight: 16 }
        }
    }
}

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    title: "医生列表"

    // 外部可传入多个医生（JS数组）；内部会转换为 doctorListModel
    property var doctors: []

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
                font.pixelSize: 18
                font.bold: true
                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                Layout.fillWidth: true
            }
            Item { width: 48 }
        }
    }

    // 内部可响应的 ListModel —— delegate 里会引用这些 role
    ListModel { id: doctorListModel }

    // 辅助函数：把一个 JS 对象规范化并 append 到 doctorListModel
    function appendDoctor(obj) {
        // 规范字段名（保留原字段优先）
        var name = obj.name || obj.username || ""
        var work_id = obj.work_id || obj.workId || obj.id || ""
        var department = obj.department || obj.dept || ""
        var profile = obj.personal_profile || obj.profile || ""
        var photo = obj.photo_url || obj.photoUrl || obj.photo || ""
        var wh = obj.working_hours || { start: obj.workStart || obj.work_start || "--:--", end: obj.workEnd || obj.work_end || "--:--" }
        var fee = obj.consultation_fee || obj.consultationFee || obj.fee || 0
        var daily_limit = (obj.daily_limit !== undefined) ? obj.daily_limit : (obj.dailyLimit !== undefined ? obj.dailyLimit : 0)
        var booked = (obj.booked_count !== undefined) ? obj.booked_count : (obj.bookedCount !== undefined ? obj.bookedCount : 0)
        var registered = !!obj.registered

        // 确保 numeric 类型
        daily_limit = Number(daily_limit) || 0
        booked = Number(booked) || 0

        doctorListModel.append({
            name: name,
            work_id: work_id,
            department: department,
            profile: profile,
            photo: photo,
            working_hours: wh,
            consultation_fee: fee,
            daily_limit: daily_limit,
            booked_count: booked,
            registered: registered
        })
    }

    Component.onCompleted: {
        // 如果外部传入 doctors（JS数组），优先使用；否则用示例
        if (doctors && doctors.length > 0) {
            // 清空已有模型
            doctorListModel.clear()
            for (var i = 0; i < doctors.length; ++i) {
                appendDoctor(doctors[i])
            }
        } else {
            // 示例数据
            doctorListModel.clear()
            appendDoctor({
                name: "张三",
                work_id: "D1001",
                department: "内科",
                personal_profile: "从业10年，擅长呼吸系统疾病",
                photo_url: "",
                working_hours: { start: "09:00", end: "17:00" },
                consultation_fee: "50",
                daily_limit: 30,
                booked_count: 10,
                registered: false
            })
            appendDoctor({
                name: "李四",
                work_id: "D1002",
                department: "外科",
                personal_profile: "擅长普外与微创",
                photo_url: "",
                working_hours: { start: "08:30", end: "16:30" },
                consultation_fee: "80",
                daily_limit: 20,
                booked_count: 5,
                registered: false
            })
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        TextField {
            id: searchField
            placeholderText: "搜索姓名 / 科室 / 工号"
            Layout.fillWidth: true
            onTextChanged: listView.forceLayout()
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: doctorListModel

            delegate: Frame {
                width: ListView.view.width
                padding: 10
                background: Rectangle { color: "#FAFAFA"; radius: 6; border.color: "#E6E6E6" }

                // 过滤搜索
                visible: {
                    var key = (searchField.text || "").toLowerCase()
                    if (!key) return true
                    var name = (name || "").toLowerCase()
                    var dept = (department || "").toLowerCase()
                    var workId = (work_id || "").toLowerCase()
                    return name.indexOf(key) !== -1 || dept.indexOf(key) !== -1 || workId.indexOf(key) !== -1
                }

                RowLayout {
                    spacing: 12
                    width: parent.width

                    Rectangle {
                        width: 56; height: 56; radius: 6
                        color: "#EEE"; border.color: "#DDD"; clip: true
                        Image { anchors.fill: parent; fillMode: Image.PreserveAspectCrop; source: (photo || "") }
                        Label {
                            visible: !photo
                            anchors.centerIn: parent
                            text: "无\n照"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            color: "#777"
                            font.pixelSize: 10
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Layout.fillWidth: true

                        Label { text: (name || "—"); font.pixelSize: 16; color: "#222" }
                        Label {
                            text: "工号：" + (work_id || "—") + "    科室：" + (department || "—")
                            color: "#555"
                        }
                        Label {
                            text: "出诊：" +
                                  ((working_hours && working_hours.start) ? (working_hours.start + " - " + working_hours.end)
                                                                         : ("--:-- - --:--"))
                            color: "#777"
                            font.pixelSize: 12
                        }
                        Label {
                            // 已预约 / 总限额 / 剩余
                            text: "已预约：" + (booked_count || 0) +
                                  " 人 / 总限额：" + (daily_limit || 0) +
                                  "，剩余：" + Math.max((daily_limit || 0) - (booked_count || 0), 0)
                            color: "#AA0000"
                            font.pixelSize: 12
                        }
                    }

                    // 挂号按钮：动态文本与可用性由 model 控制
                    Button {
                        id: regBtn
                        text: registered ? "已挂号" : "挂号"
                        enabled: !registered && ((booked_count || 0) < (daily_limit || 0))

                        onClicked: {
                            // 双保险检查
                            var cur = doctorListModel.get(index)
                            if (!cur) return
                            var curBooked = Number(cur.booked_count || 0)
                            var curLimit = Number(cur.daily_limit || 0)
                            if (cur.booked_count >= curLimit) {
                                // 已满，不允许挂号
                                console.warn("挂号失败：名额已满", cur.name)
                                return
                            }
                            // 更新模型：已预约 +1，注册状态 true
                            doctorListModel.set(index, {
                                booked_count: curBooked + 1,
                                registered: true
                            })
                            // （可选）如果你需要在后端记录挂号，可在这里发起 XHR 请求
                            // var xhr = new XMLHttpRequest(); ...
                        }
                    }

                    // 查看详情
                    Button {
                        text: "查看"
                        onClicked: {
                            // 把当前医生数据对象传给详情页
                            var doc = doctorListModel.get(index)
                            if (mainStackView) {
                                mainStackView.push(Qt.resolvedUrl("DoctorDetailScreen.qml"), { doctor: doc })
                            } else if (StackView.view) {
                                StackView.view.push(Qt.resolvedUrl("DoctorDetailScreen.qml"), { doctor: doc })
                            }
                        }
                    }
                }
            }
        }
    }
}

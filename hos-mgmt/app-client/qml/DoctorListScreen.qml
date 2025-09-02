import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    title: "医生挂号"

    ListModel {
        id: doctorModel
        // 数据由接口返回
    }

    /*Component.onCompleted: {
        // 获取医生列表并排班
        client.getDoctorList(function(list){
            doctorModel.clear()
            for(var i=0; i<list.length; ++i){
                doctorModel.append(list[i])
            }
        })
    }*/

    ListView {
        anchors.fill: parent
        model: doctorModel
        delegate: Rectangle {
            width: parent.width
            height: 180
            color: "#f4f8f4"
            border.color: "#e0e0e0"
            radius: 8
            anchors.margins: 10
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 10
                spacing: 6
                RowLayout {
                    spacing: 15
                    Label { text: "医生编号: " + model.doctorId }
                    Label { text: "科室: " + model.department }
                    Label { text: "工号: " + model.jobId }
                }
                RowLayout {
                    spacing: 15
                    Label { text: "姓名: " + model.name }
                    Label { text: "挂号费: " + model.fee + "元" }
                }
                Label { text: "个人资料: " + model.profile }
                RowLayout {
                    spacing: 15
                    Label { text: "上班时间: " + model.workTime }
                    Label { text: "单日患者上限: " + model.dayLimit }
                    Label { text: "已预约人数: " + model.reserved }
                    Label {
                        text: "剩余预约数: " + (model.dayLimit - model.reserved)
                        color: (model.dayLimit-model.reserved)>0 ? "green":"red"
                    }
                }
                Button {
                    text: "挂号"
                    enabled: (model.dayLimit - model.reserved) > 0
                    onClicked: {
                        mainStackView.push("RegisterAppointmentScreen.qml", {doctorId: model.doctorId})
                    }
                }
            }
        }
    }
}

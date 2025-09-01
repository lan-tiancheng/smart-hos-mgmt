import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: root
    title: "预约挂号"

    // 医生数据
    property var doctors: [
        { id: "D001", department: "内科", workId: "1001", name: "张医生",
          profile: "主任医师，擅长心血管疾病诊治。",
          workTime: "周一至周五 上午 8:00-12:00", fee: 30, maxPatients: 20, booked: 12 },
        { id: "D002", department: "外科", workId: "2001", name: "李医生",
          profile: "副主任医师，擅长胃肠外科手术。",
          workTime: "周二、周四 下午 14:00-18:00", fee: 50, maxPatients: 15, booked: 8 },
        { id: "D003", department: "儿科", workId: "3001", name: "王医生",
          profile: "儿科专家，专注儿童哮喘与呼吸系统疾病。",
          workTime: "周三、周五 上午 9:00-12:00", fee: 25, maxPatients: 25, booked: 20 }
    ]

    // 动态生成科室列表
    property var departments: doctors.map(function(d){return d.department})
                                     .filter(function(value,index,self){return self.indexOf(value)===index})

    property string selectedDepartment: departments.length > 0 ? departments[0] : ""
    property string searchName: ""

    // 寻找父级 StackView
    function findStackView(item){
        var p = item
        while(p){
            if(p && typeof p.push==="function" && typeof p.pop==="function") return p
            p = p.parent
        }
        return null
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // 顶部操作行：返回 + 科室选择 + 姓名搜索
        RowLayout {
            spacing: 12

            Button {
                text: "返回"
                onClicked: {
                    var sv = findStackView(root)
                    if(sv) sv.pop()
                }
            }

            Label { text: "选择科室:" }
            ComboBox {
                id: departmentCombo
                model: departments
                currentIndex: 0
                onCurrentIndexChanged: selectedDepartment = departments[currentIndex]
            }

            Label { text: "搜索医生:" }
            TextField {
                id: searchField
                placeholderText: "请输入医生姓名"
                Layout.preferredWidth: 120
                onTextChanged: searchName = text
            }
        }

        // 医生列表
        ListView {
            id: doctorList
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 10

            model: doctors.filter(function(d){
                return d.department === selectedDepartment &&
                       (searchName === "" || d.name.indexOf(searchName) !== -1)
            })

            delegate: Frame {
                width: parent.width
                background: Rectangle { color: "white"; radius: 8; border.color: "#cccccc" }

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10
                    spacing: 6

                    Label { text: "医生编号: " + model.id }
                    Label { text: "科室: " + model.department }
                    Label { text: "工号: " + model.workId }
                    Label { text: "姓名: " + model.name }
                    Label { text: "个人资料: " + model.profile; wrapMode: Text.WordWrap }
                    Label { text: "上班时间: " + model.workTime }
                    Label { text: "挂号费用: " + model.fee + " 元" }
                    Label { text: "单日患者上限: " + model.maxPatients }
                    Label { text: "已预约人数: " + model.booked }
                    Label { text: "剩余预约数: " + (model.maxPatients - model.booked) }

                    RowLayout {
                        Layout.alignment: Qt.AlignRight
                        Button {
                            text: "挂号"
                            enabled: model.booked < model.maxPatients
                            onClicked: {
                                Qt.createQmlObject('import QtQuick.Controls 2.15; MessageDialog { text: "挂号成功！\\n医生: '+model.name+'\\n科室: '+model.department+'\\n费用: '+model.fee+'元"; visible: true; }', root)
                            }
                        }
                    }
                }
            }
        }
    }
}

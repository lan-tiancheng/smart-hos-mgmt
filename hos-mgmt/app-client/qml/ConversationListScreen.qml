import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtWebSockets 1.0

// 通用会话列表（医生/患者均可使用）
// 入口需传入：apiBase, wsUrl, token, selfRole("doctor"/"patient"), selfId, selfName
Page {
    id: page
    title: "会话"

    property string apiBase: ""
    property string wsUrl: ""
    property string token: ""
    property string selfRole: "doctor"   // "doctor" or "patient"
    property int selfId: -1
    property string selfName: ""

    property int pollIntervalMs: 6000
    property alias searchText: searchField.text

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton { text: "返回"; onClicked: { if (typeof mainStackView !== "undefined" && mainStackView.pop) mainStackView.pop(); else if (StackView.view) StackView.view.pop() } }
            Label { text: page.title; font.pixelSize: 18; font.bold: true; Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter; Layout.fillWidth: true }
            ToolButton { text: "刷新"; onClicked: refreshConversations() }
        }
    }

    ListModel { id: convModel }

    WebSocket {
        id: ws
        active: wsUrl !== ""
        url: {
            if (!wsUrl) return ""
            var q = "?token=" + encodeURIComponent(token) + "&scope=conversations"
            if (selfRole === "doctor" && selfId>0) q += "&doctorId=" + selfId
            if (selfRole === "patient" && selfId>0) q += "&patientId=" + selfId
            return wsUrl + (wsUrl.indexOf("?")>-1 ? "&" : "?") + q.slice(1)
        }
        onTextMessageReceived: function(_) { refreshConversations() }
        onErrorStringChanged: console.log("Conv WS error:", errorString)
    }

    Timer { id: pollTimer; interval: pollIntervalMs; repeat: true; running: apiBase !== ""; onTriggered: refreshConversations() }

    Component.onCompleted: {
        console.log("ConersationListScreen => role:", selfRole, " selfId:", selfId, " apiBase:", apiBase, " wsUrl:", wsUrl)
        loadInitial()
    }

    function api(path) { return apiBase.replace(/\/+$/,"") + path }
    function two(n){ return (n<10?"0":"")+n }
    function formatTime(t){
        if (!t) return ""
        var d=new Date(t); if (isNaN(d.getTime())) return t
        var now=new Date(); var same=d.toDateString()===now.toDateString()
        return same ? (two(d.getHours())+":"+two(d.getMinutes())) : (d.getFullYear()+"-"+two(d.getMonth()+1)+"-"+two(d.getDate()))
    }

    function loadInitial() {
        if (apiBase === "") {
            convModel.clear()
            convModel.append({ conversation_id: 10001, peer_name: "示例 A", last_content: "你好", last_time: "2025-08-30T09:20:00Z", unread: 1, patient_id: 501, doctor_id: 301 })
            convModel.append({ conversation_id: 10002, peer_name: "示例 B", last_content: "好的", last_time: "2025-08-29T16:42:00Z", unread: 0, patient_id: 502, doctor_id: 301 })
            return
        }
        refreshConversations()
    }

    function refreshConversations() {
        if (apiBase === "" || selfId <= 0) return
        var url = "/api/chat/conversations"
        url += (selfRole === "doctor") ? ("?doctorId=" + selfId) : ("?patientId=" + selfId)
        var xhr = new XMLHttpRequest()
        xhr.open("GET", api(url))
        if (token) xhr.setRequestHeader("Authorization", "Bearer " + token)
        xhr.onreadystatechange = function(){
            if (xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200){
                try {
                    var arr = JSON.parse(xhr.responseText) || []
                    if (arr && !Array.isArray(arr) && (arr.data || arr.conversations)) arr = arr.data || arr.conversations || []
                    convModel.clear()
                    for (var i=0;i<arr.length;i++){
                        var it = arr[i]
                        convModel.append({
                            conversation_id: it.conversation_id || it.id || it.conversationId || 0,
                            peer_name: it.peer_name || it.peerName || it.patient_name || it.doctor_name || "会话",
                            patient_id: it.patient_id || it.patientId || 0,
                            doctor_id: it.doctor_id || it.doctorId || 0,
                            last_content: it.last_content || it.lastMessage || it.content || "",
                            last_time: it.last_time || it.lastTime || it.updated_at || it.updatedAt || it.time || "",
                            unread: it.unread || it.unread_count || 0
                        })
                    }
                } catch(e){ console.log("conversations parse error:", e) }
            }
        }
        xhr.send()
    }

    ColumnLayout {
        anchors.fill: parent; anchors.margins: 12; spacing: 8
        RowLayout {
            Layout.fillWidth: true; spacing: 8
            TextField { id: searchField; Layout.fillWidth: true; placeholderText: "搜索姓名" }
            Button { text: "新建"; onClicked: {
                // 自行实现选择对象的入口（例如跳 DoctorListScreen 或医院科室页）
                if (typeof mainStackView !== "undefined" && mainStackView.push)
                    mainStackView.push("qrc:/client/qml/qml/DoctorListScreen.qml", { apiBase, wsUrl, token, patientId: (selfRole==="patient"? selfId : -1) })
                else if (StackView.view)
                    StackView.view.push("qrc:/client/qml/qml/DoctorListScreen.qml", { apiBase, wsUrl, token, patientId: (selfRole==="patient"? selfId : -1) })
            }}
        }
        ListView {
            id: listView
            Layout.fillWidth: true; Layout.fillHeight: true; clip: true; spacing: 6
            model: convModel
            delegate: ItemDelegate {
                width: ListView.view.width
                visible: (searchText.trim().length===0) || (peer_name.indexOf(searchText)!==-1)
                contentItem: RowLayout {
                    spacing: 10
                    Rectangle { width: 40; height: 40; radius: 20; color: "#E3F2FD"; border.color:"#BBDEFB"
                        Label { anchors.centerIn: parent; text: peer_name.length>0 ? peer_name.charAt(0) : "聊"; color:"#1565C0"; font.bold: true }
                    }
                    ColumnLayout {
                        Layout.fillWidth: true; spacing: 2
                        RowLayout { Layout.fillWidth: true
                            Label { text: peer_name; font.bold:true; Layout.fillWidth:true }
                            Label { text: formatTime(last_time); color:"#9E9E9E"; font.pixelSize: 12 }
                        }
                        RowLayout { Layout.fillWidth: true
                            Label { text: last_content; color:"#616161"; elide: Text.ElideRight; Layout.fillWidth:true }
                            Rectangle {
                                visible: unread>0; radius: 9; color:"#D32F2F"; height: 18
                                width: Math.max(18, unreadLabel.implicitWidth+10)
                                Label { id: unreadLabel; anchors.centerIn: parent; text: Math.min(unread,99); color:"white"; font.pixelSize:12 }
                            }
                        }
                    }
                }
                onClicked: {
                    var cid = Number(conversation_id)||0
                    var pid = Number(patient_id)||0
                    var did = Number(doctor_id)||0
                    var params = {
                        apiBase: page.apiBase, wsUrl: page.wsUrl, token: page.token,
                        conversationId: cid>0?cid:-1,
                        patientId: (cid>0? -1 : pid),
                        doctorId: (cid>0? -1 : did),
                        selfName: page.selfName || (page.selfRole==="doctor" ? "医生" : "我"),
                        peerName: peer_name
                    }
                    if (page.selfRole === "doctor") {
                        params.selfRole = "doctor"; params.selfId = page.selfId>0 ? page.selfId : did
                        var url = "qrc:/client/qml/qml/DoctorChatScreen.qml"
                        if (typeof mainStackView !== "undefined" && mainStackView.push) mainStackView.push(url, params)
                        else if (StackView.view) StackView.view.push(url, params)
                    } else {
                        params.selfRole = "patient"; params.selfId = page.selfId>0 ? page.selfId : pid
                        var urlp = "qrc:/client/qml/qml/PatientChatScreen.qml"
                        if (typeof mainStackView !== "undefined" && mainStackView.push) mainStackView.push(urlp, params)
                        else if (StackView.view) StackView.view.push(urlp, params)
                    }
                }
            }
            footer: Rectangle { height: 8; width: 1; color: "transparent" }
        }
    }
}

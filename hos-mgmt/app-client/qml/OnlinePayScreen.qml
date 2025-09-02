import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    title: "微信支付"

    // 外部可传：amountFen、apiBase
    // 如果传入了 orderNo/qrImageSource，则本页不再自动创建订单
    property string orderNo: ""
    property int amountFen: 12800
    property real amountYuan: amountFen / 100.0
    property url qrImageSource: "qrc:/client/qml/wechat_qr.png"

    // 后端地址（如 http://127.0.0.1:3000）。仅设置 apiBase 即可，页面会自动创建订单
    property string apiBase: ""
    property string description: "就诊费用"

    // 行为设置
    property bool autoCreateOrder: true     // 进页后自动创建订单
    property bool autoPoll: true            // 自动轮询
    property int pollIntervalMs: 3000

    // 支付状态
    property string payStatus: "PENDING"    // PENDING / SUCCESS / FAILED / CLOSED
    property string statusText: (payStatus === "SUCCESS" ? "付款完成"
                               : payStatus === "FAILED"  ? "支付失败"
                               : payStatus === "CLOSED"  ? "已关闭/超时"
                               : "待支付")
    property color statusColor: (payStatus === "SUCCESS" ? "#1DBF60"
                               : payStatus === "FAILED"  ? "#E53935"
                               : payStatus === "CLOSED"  ? "#757575"
                               : "#F9A825")
    property bool devSimulate: false

    // 错误提示
    property string errMsg: ""

    function fmtYuan(v) { return Number(v).toFixed(2) }
    function hasBackend() { return apiBase !== "" }
    function canQuery() { return hasBackend() && orderNo !== "" }

    // 1) 创建订单（真实调用你的后端 /pay/wechat/native）
    function createOrder() {
        errMsg = ""
        payStatus = "PENDING"
        if (!hasBackend()) {
            errMsg = "未设置后端地址（apiBase），无法创建订单"
            return
        }
        busy.running = true
        var xhr = new XMLHttpRequest()
        xhr.open("POST", apiBase.replace(/\/+$/, "") + "/pay/wechat/native")
        xhr.setRequestHeader("Content-Type", "application/json")
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                busy.running = false
                if (xhr.status === 200) {
                    try {
                        var resp = JSON.parse(xhr.responseText)
                        orderNo = resp.orderNo || ""
                        amountFen = (resp.amountFen || amountFen)
                        qrImageSource = resp.qrUrl || qrImageSource
                        if (!orderNo || !qrImageSource) {
                            errMsg = "创建订单成功但缺少 orderNo/qrUrl"
                        } else {
                            // 成功创建后，确保开始轮询
                            pollTimer.restart()
                        }
                    } catch (e) {
                        errMsg = "解析创建订单响应失败"
                        console.log("parse create order error:", e)
                    }
                } else {
                    errMsg = "创建订单失败：" + xhr.status
                    console.log("create order failed:", xhr.status, xhr.responseText)
                }
            }
        }
        var payload = { amountFen: amountFen, description: description }
        xhr.send(JSON.stringify(payload))
    }

    // 2) 查询支付状态（真实调用你的后端 /pay/wechat/query）
    function queryPayStatus() {
        if (!canQuery()) return
        busy.running = true
        var xhr = new XMLHttpRequest()
        var url = apiBase.replace(/\/+$/, "") + "/pay/wechat/query?orderNo=" + encodeURIComponent(orderNo)
        xhr.open("GET", url)
        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                busy.running = false
                if (xhr.status === 200) {
                    try {
                        var resp = JSON.parse(xhr.responseText)
                        var st = resp.status || resp.trade_state || (resp.paid ? "SUCCESS" : "PENDING")
                        st = ("" + st).toUpperCase()
                        if (st.indexOf("SUCCESS") !== -1 || resp.paid === true) {
                            payStatus = "SUCCESS"
                            pollTimer.running = false
                        } else if (st.indexOf("CLOSED") !== -1 || st.indexOf("PAYERROR") !== -1 || st.indexOf("REVOKED") !== -1) {
                            payStatus = (st.indexOf("CLOSED") !== -1) ? "CLOSED" : "FAILED"
                            pollTimer.running = false
                        } else {
                            payStatus = "PENDING"
                        }
                    } catch (e) {
                        console.log("Parse error:", e)
                    }
                } else {
                    console.log("HTTP error:", xhr.status, xhr.responseText)
                }
            }
        }
        xhr.send()
    }

    // 首次进入页面自动下单（仅当你没有提前传入 orderNo/qrImageSource）
    Component.onCompleted: {
        if (autoCreateOrder && hasBackend() && (!orderNo || !qrImageSource)) {
            createOrder()
        }
    }

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "返回"
                onClicked: {
                    if (mainStackView && mainStackView.depth > 1) {
                        mainStackView.pop(mainStackView.get(0))
                    } else if (StackView.view && StackView.view.depth > 1) {
                        StackView.view.pop(StackView.view.get(0))
                    }
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

    Timer {
        id: pollTimer
        interval: pollIntervalMs
        repeat: true
        running: autoPoll && canQuery() && payStatus === "PENDING"
        onTriggered: queryPayStatus()
        function restart() { running = false; running = autoPoll && canQuery() && payStatus === "PENDING" }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        // 错误提示条
        Rectangle {
            visible: errMsg !== ""
            Layout.fillWidth: true
            height: visible ? implicitHeight : 0
            implicitHeight: 42
            radius: 8
            color: "#FDECEA"
            border.color: "#F5C6CB"
            RowLayout {
                anchors.fill: parent; anchors.margins: 10; spacing: 8
                Label { text: "❌"; color: "#C0392B" }
                Label { text: errMsg; color: "#C0392B"; wrapMode: Text.Wrap; Layout.fillWidth: true }
                Button { text: "重试下单"; visible: hasBackend(); onClicked: createOrder() }
            }
        }

        // 状态条
        Rectangle {
            Layout.fillWidth: true
            height: 44; radius: 8
            color: statusColor; opacity: 0.12; border.color: statusColor
            RowLayout {
                anchors.fill: parent; anchors.margins: 10; spacing: 10
                Rectangle { width: 10; height: 10; radius: 2; color: statusColor; Layout.alignment: Qt.AlignVCenter }
                Label { text: statusText + (payStatus === "PENDING" && canQuery() ? "（自动查询中…）" : ""); color: statusColor; font.bold: true; Layout.fillWidth: true }
                BusyIndicator { id: busy; running: false; visible: running }
            }
        }

        // 金额+订单号
        Frame {
            Layout.fillWidth: true
            background: Rectangle { color: "#FAFAFA"; radius: 8; border.color: "#E0E0E0" }
            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 6

                RowLayout {
                    spacing: 8
                    Label { text: "待付款金额"; color: "#616161" }
                    Label { text: "￥" + fmtYuan(amountYuan); font.pixelSize: 28; font.bold: true; color: "#212121" }
                }
                RowLayout {
                    visible: orderNo !== ""
                    spacing: 8
                    Label { text: "订单号：" + orderNo; color: "#757575" }
                }
            }
        }

        // 二维码
        GroupBox {
            title: "微信付款码（请使用微信扫码）"
            Layout.fillWidth: true
            Layout.fillHeight: true
            Rectangle {
                anchors.centerIn: parent
                width: Math.min(parent.width - 48, 320); height: width
                radius: 12; color: "#FFFFFF"; border.color: "#E0E0E0"

                Image {
                    id: qr
                    anchors.fill: parent; anchors.margins: 16
                    source: qrImageSource
                    fillMode: Image.PreserveAspectFit
                    cache: false
                }
                Column {
                    anchors.centerIn: parent; spacing: 6
                    visible: !qrImageSource || qr.status !== Image.Ready
                    Label { text: hasBackend() ? "正在获取二维码…" : "未设置后端，显示内置占位图"; color: "#9E9E9E"; horizontalAlignment: Text.AlignHCenter }
                    Label { text: !hasBackend() ? "默认：qrc:/client/qml/wechat_qr.png" : ""; color: "#BDBDBD"; font.pixelSize: 12; horizontalAlignment: Text.AlignHCenter }
                }
            }
        }

        // 操作区
        RowLayout {
            Layout.fillWidth: true; spacing: 10

            // 手动查询
            Button {
                text: (payStatus === "PENDING" ? "我已完成支付，查询状态" : "已支付")
                enabled: payStatus === "PENDING"
                onClicked: {
                    if (devSimulate || !canQuery()) { payStatus = "SUCCESS"; pollTimer.running = false }
                    else { queryPayStatus() }
                }
            }

            // 重新下单（当失败/关闭时，或你想换一笔金额时）
            Button {
                text: "重新获取二维码"
                visible: hasBackend()
                onClicked: {
                    // 可在重新下单前根据需要调整 amountFen/description
                    orderNo = ""
                    qrImageSource = ""
                    createOrder()
                }
            }

            CheckBox {
                id: simulateBox
                text: "开发者模拟支付成功"
                checked: devSimulate
                onToggled: { devSimulate = checked; if (devSimulate) pollTimer.running = false }
            }

            Item { Layout.fillWidth: true }
        }

        // 成功提示
        Rectangle {
            visible: payStatus === "SUCCESS"
            Layout.fillWidth: true; height: 52
            radius: 10; color: "#E8F5E9"; border.color: "#C8E6C9"
            RowLayout {
                anchors.fill: parent; anchors.margins: 12; spacing: 8
                Label { text: "✅ 付款完成"; color: "#2E7D32"; font.bold: true }
                Item { Layout.fillWidth: true }
                Button {
                    text: "返回患者主页"
                    onClicked: {
                        if (mainStackView && mainStackView.depth > 1) {
                            mainStackView.pop(mainStackView.get(0))
                        } else if (StackView.view && StackView.view.depth > 1) {
                            StackView.view.pop(StackView.view.get(0))
                        }
                    }
                }
            }
        }
    }
}

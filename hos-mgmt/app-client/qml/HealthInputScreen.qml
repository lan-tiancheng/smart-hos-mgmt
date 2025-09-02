// HealthInputScreen.qml — Qt5 兼容 · 轻玻璃拟态（蓝白粉）
// 逻辑保持：authManager.submitHealthData(...) 与信号 onHealthSubmitSuccess/Failed 不变
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Page {
    id: root
    title: "健康数据录入"

    // 统一图片目录（可选图标）
    readonly property url imgDir: Qt.resolvedUrl("images/")
    function img(name) { return imgDir + name }

    // 主题
    readonly property color cBlue:  "#5AA9FF"
    readonly property color cPink:  "#FF9AC2"
    readonly property color cText:  "#0F1B2D"
    readonly property color cGlass: "#FFFFFFCC"
    readonly property color cStroke:"#FFFFFF66"

    // 实时计算/提示
    property string bpHint: ""
    property real   bmiPreview: 0.0

    // 直接保存 4 个输入框的引用（避免遍历找不到导致 null）
    property var fHeight: null
    property var fWeight: null
    property var fLung:   null
    property var fBp:     null

    // ========== 背景（更快·全局柔光） ==========
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#E6F2FF" }
            GradientStop { position: 0.5; color: "#FDFDFF" }
            GradientStop { position: 1.0; color: "#FFE9F3" }
        }

        Rectangle {
            id: glowA
            width: Math.max(parent.width * 0.22, 220)
            height: width; radius: width/2
            color: cBlue; opacity: 0.24
            x: -width * 0.3; y: parent.height * 0.14
            SequentialAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: parent.width * 0.75; duration: 8000; easing.type: Easing.InOutSine }
                NumberAnimation { to: -glowA.width * 0.3;  duration: 8000; easing.type: Easing.InOutSine }
            }
        }
        Rectangle {
            id: glowB
            width: Math.max(parent.width * 0.26, 260)
            height: width; radius: width/2
            color: cPink; opacity: 0.20
            x: parent.width * 0.65; y: parent.height * 0.62
            ParallelAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: parent.width * 0.12; duration: 9000; easing.type: Easing.InOutQuad }
                NumberAnimation { to: parent.width * 0.65; duration: 9000; easing.type: Easing.InOutQuad }
            }
            ParallelAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { to: parent.height * 0.18; duration: 9000; easing.type: Easing.InOutQuad }
                NumberAnimation { to: parent.height * 0.62; duration: 9000; easing.type: Easing.InOutQuad }
            }
        }
        Rectangle {
            id: glowC
            width: Math.max(parent.width * 0.16, 160)
            height: width; radius: width/2
            color: "#FFFFFF"; opacity: 0.12
            x: parent.width * 0.18; y: parent.height * 0.55
            SequentialAnimation on x {
                loops: Animation.Infinite
                NumberAnimation { to: parent.width * 0.82; duration: 6000; easing.type: Easing.InOutSine }
                NumberAnimation { to: parent.width * 0.18; duration: 6000; easing.type: Easing.InOutSine }
            }
            SequentialAnimation on y {
                loops: Animation.Infinite
                NumberAnimation { to: parent.height * 0.28; duration: 6000; easing.type: Easing.InOutSine }
                NumberAnimation { to: parent.height * 0.55; duration: 6000; easing.type: Easing.InOutSine }
            }
        }
    }

    // ========== 中央玻璃卡 ==========
    Item {
        id: panel
        anchors.centerIn: parent
        width:  Math.min(root.width  * 0.92, 1000)
        height: Math.min(root.height * 0.88, 640)

        ShaderEffectSource { id: bgSrc; anchors.fill: parent; sourceItem: root.contentItem; hideSource: false; live: true }
        FastBlur { anchors.fill: parent; source: bgSrc; radius: 26 }
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

        // ===== 顶部标题条 =====
        Rectangle {
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
            height: 86; radius: 22
            color: "#FFFFFFAA"; border.color: "#FFFFFF66"
            anchors.margins: 0
            RowLayout {
                anchors.fill: parent; anchors.margins: 18; spacing: 12
                Rectangle {
                    width: 52; height: 52; radius: 26
                    color: "#FFFFFF"; border.color: "#FFFFFF88"
                    Label { anchors.centerIn: parent; text: "📋"; font.pixelSize: 24 }
                }
                ColumnLayout {
                    Layout.fillWidth: true
                    Label { text: "健康数据录入"; color: cText; font.bold: true; font.pixelSize: 22 }
                    Label { text: "请输入身高、体重、肺活量与血压（形如 120/80）"; color: "#6B7B93"; font.pixelSize: 12 }
                }
                Button { text: "返回"; onClicked: mainStackView.pop() }
            }
        }

        // ===== 内容区：左表单 / 右预览 =====
        RowLayout {
            anchors.left: parent.left; anchors.right: parent.right
            anchors.top: parent.top; anchors.bottom: parent.bottom
            anchors.margins: 26
            anchors.topMargin: 112
            spacing: 20

            // ---------- 左：表单 ----------
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 18
                color: "#FFFFFFB0"
                border.color: cStroke

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 12

                    // 字段组件封装：图标 + 文本框
                    Component {
                        id: fieldRow
                        RowLayout {
                            property alias field: tf
                            property string hintText: ""
                            property string emoji: ""
                            property url    iconUrl: ""

                            Layout.fillWidth: true; spacing: 10

                            Item {
                                width: 36; height: 36
                                Rectangle { anchors.fill: parent; radius: 9; color: "#FFFFFF"; border.color: "#FFFFFF88" }
                                Image {
                                    anchors.centerIn: parent
                                    source: iconUrl
                                    width: 20; height: 20
                                    visible: status === Image.Ready
                                    fillMode: Image.PreserveAspectFit; smooth: true
                                }
                                Label {
                                    anchors.centerIn: parent
                                    text: emoji
                                    visible: !parent.children[1].visible
                                    font.pixelSize: 16
                                }
                            }

                            TextField {
                                id: tf
                                Layout.fillWidth: true
                                placeholderText: hintText
                                background: Rectangle {
                                    radius: 10
                                    color: "#FFFFFFD8"
                                    border.color: control.activeFocus ? cBlue : "#FFFFFF88"
                                    border.width: 1
                                }
                                states: State {
                                    when: tf.activeFocus
                                    PropertyChanges { target: tf; scale: 1.01 }
                                }
                                Behavior on scale { NumberAnimation { duration: 120 } }
                            }
                        }
                    }

                    // 身高
                    Loader {
                        sourceComponent: fieldRow
                        onLoaded: {
                            item.hintText = "身高 (cm)";
                            item.emoji = "📏";
                            item.iconUrl = img("ruler.svg");
                            item.field.inputMethodHints = Qt.ImhDigitsOnly;
                            root.fHeight = item.field;                 // 保存引用
                            item.field.onTextChanged.connect(updatePreview);
                        }
                    }
                    // 体重
                    Loader {
                        sourceComponent: fieldRow
                        onLoaded: {
                            item.hintText = "体重 (kg)";
                            item.emoji = "⚖️";
                            item.iconUrl = img("weight.svg");
                            item.field.inputMethodHints = Qt.ImhDigitsOnly;
                            root.fWeight = item.field;                 // 保存引用
                            item.field.onTextChanged.connect(updatePreview);
                        }
                    }
                    // 肺活量
                    Loader {
                        sourceComponent: fieldRow
                        onLoaded: {
                            item.hintText = "肺活量 (ml)";
                            item.emoji = "🫁";
                            item.iconUrl = img("lungs.svg");
                            item.field.inputMethodHints = Qt.ImhDigitsOnly;
                            root.fLung = item.field;                   // 保存引用
                        }
                    }
                    // 血压
                    Loader {
                        id: bpLoader
                        sourceComponent: fieldRow
                        onLoaded: {
                            item.hintText = "血压 (mmHg)，例 120/80";
                            item.emoji = "🩸";
                            item.iconUrl = img("bp.svg");
                            item.field.inputMethodHints = Qt.ImhDigitsOnly | Qt.ImhNoPredictiveText;
                            root.fBp = item.field;                     // 保存引用
                            item.field.onTextChanged.connect(function() {
                                var t = item.field.text.trim();
                                if (t.length === 0) { bpHint = ""; return }
                                var ok = /^\d{2,3}\/\d{2,3}$/.test(t);
                                bpHint = ok ? "" : "血压格式应为 120/80";
                            });
                        }
                    }

                    // 提示/错误
                    Label {
                        text: bpHint
                        color: "#D62D30"
                        visible: bpHint !== ""
                        font.pixelSize: 12
                        Layout.fillWidth: true
                    }

                    // 操作区
                    RowLayout {
                        Layout.fillWidth: true; spacing: 10
                        Button {
                            id: submitBtn
                            text: "提交"
                            Layout.fillWidth: true
                            onClicked: {
                                bpHint = "";

                                // —— 直接使用引用，避免 null ——
                                var hTxt = fHeight ? fHeight.text.trim() : "";
                                var wTxt = fWeight ? fWeight.text.trim() : "";
                                var lTxt = fLung   ? fLung.text.trim()   : "";
                                var bpt  = fBp     ? fBp.text.trim()     : "";

                                var h = parseFloat(hTxt);
                                var w = parseFloat(wTxt);
                                var l = parseInt(lTxt);

                                if (isNaN(h) || isNaN(w) || isNaN(l) || bpt === "") {
                                    toast.show("请完整填写所有字段", true); return;
                                }
                                if (!(h >= 50 && h <= 250))   { toast.show("身高范围 50–250 cm", true); return; }
                                if (!(w >= 10 && w <= 400))   { toast.show("体重范围 10–400 kg", true); return; }
                                if (!(l >= 100 && l <= 20000)){ toast.show("肺活量范围 100–20000 ml", true); return; }
                                if (!/^\d{2,3}\/\d{2,3}$/.test(bpt)) {
                                    bpHint = "血压格式应为 120/80"; toast.show(bpHint, true); return;
                                }

                                authManager.submitHealthData(h, w, l, bpt);
                            }
                        }
                        Button {
                            text: "清空"
                            onClicked: {
                                if (fHeight) fHeight.text = "";
                                if (fWeight) fWeight.text = "";
                                if (fLung)   fLung.text = "";
                                if (fBp)     fBp.text = "";
                                bpHint = ""; bmiPreview = 0.0;
                                resultLabel.text = "";
                                ring.requestPaint();
                            }
                        }
                    }
                }
            }

            // ---------- 右：可视化预览 ----------
            Rectangle {
                Layout.preferredWidth: Math.max(320, panel.width * 0.34)
                Layout.fillHeight: true
                radius: 18
                color: "#FFFFFFB0"
                border.color: cStroke

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 12

                    Label { text: "实时预览"; color: cText; font.bold: true; font.pixelSize: 16 }

                    Item {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 180

                        Canvas {
                            id: ring
                            anchors.centerIn: parent
                            width: Math.min(parent.width * 0.8, 160)
                            height: width
                            onPaint: {
                                var ctx = getContext("2d")
                                ctx.reset()
                                var cx = width/2, cy = height/2, r = width*0.42
                                ctx.lineWidth = r*0.28
                                ctx.strokeStyle = "#EDF2FF"
                                ctx.beginPath()
                                ctx.arc(cx, cy, r, 0, 2*Math.PI, false)
                                ctx.stroke()

                                var v = Math.max(0, Math.min(40, bmiPreview))
                                var ang = (v/40) * Math.PI * 2
                                ctx.strokeStyle = "#5AA9FF"
                                ctx.beginPath()
                                ctx.arc(cx, cy, r, -Math.PI/2, -Math.PI/2 + ang, false)
                                ctx.stroke()
                            }
                        }
                        Label {
                            anchors.centerIn: parent
                            text: bmiPreview > 0 ? ("BMI " + bmiPreview.toFixed(1)) : "BMI —"
                            color: cText; font.bold: true; font.pixelSize: 18
                        }
                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.bottom: parent.bottom
                            text: bmiLevel(bmiPreview)
                            color: "#6B7B93"; font.pixelSize: 12
                        }
                    }

                    Label { id: resultLabel; text: ""; wrapMode: Text.WordWrap; Layout.fillWidth: true }

                    Item { Layout.fillHeight: true }

                    Rectangle {
                        Layout.fillWidth: true
                        radius: 10
                        color: "#FFFFFFA8"
                        border.color: "#FFFFFF66"
                        RowLayout {
                            anchors.fill: parent; anchors.margins: 10; spacing: 8
                            Label { text: "💡"; font.pixelSize: 16 }
                            Label {
                                text: "身高/体重一填即算 BMI。血压格式形如 120/80。"
                                color: "#5C6C80"; wrapMode: Text.WordWrap
                            }
                        }
                    }
                }
            }
        }
    }

    // 顶部 Toast
    Rectangle {
        id: toast
        radius: 10
        color: "#CC222222"
        anchors.horizontalCenter: parent.horizontalCenter
        y: shown ? 24 : -height
        width: Math.min(parent.width*0.8, 420)
        height: msg.implicitHeight + 16
        opacity: shown ? 1 : 0
        visible: opacity > 0
        property bool shown: false
        function show(text, danger) { msg.text = text || ""; msg.color = danger ? "#FFDEE3" : "#FFF"; shown = true; hideTimer.restart() }
        Timer { id: hideTimer; interval: 2200; repeat: false; onTriggered: toast.shown = false }
        Behavior on y { NumberAnimation { duration: 200; easing.type: Easing.OutCubic } }
        Behavior on opacity { NumberAnimation { duration: 200 } }
        Label { id: msg; anchors.centerIn: parent; color: "#FFF"; wrapMode: Text.WordWrap }
    }

    // 实时预览计算（使用显式引用，避免 null）
    function updatePreview() {
        var h = fHeight ? parseFloat((fHeight.text || "").trim()) : NaN
        var w = fWeight ? parseFloat((fWeight.text || "").trim()) : NaN
        if (!isNaN(h) && !isNaN(w) && h > 0) {
            var m = h / 100.0
            bmiPreview = w / (m*m)
        } else {
            bmiPreview = 0.0
        }
        ring.requestPaint()
    }

    function bmiLevel(v) {
        if (v <= 0) return "—"
        if (v < 18.5) return "偏低"
        if (v < 24.0) return "正常"
        if (v < 28.0) return "超重"
        return "肥胖"
    }

    // ===== 后端回调（保持原逻辑） =====
    Connections {
        target: authManager
        function onHealthSubmitSuccess(bmi, lungLevel, bpLevel, overall) {
            resultLabel.text = "BMI: " + bmi.toFixed(1) + "，肺活量: " + lungLevel + "，血压: " + bpLevel + "，总体: " + overall
            toast.show("提交成功")
        }
        function onHealthSubmitFailed(reason) {
            resultLabel.text = "提交失败: " + reason
            toast.show("提交失败：" + (reason || ""), true)
        }
    }
}

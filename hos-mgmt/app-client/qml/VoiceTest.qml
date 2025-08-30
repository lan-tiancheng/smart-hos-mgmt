import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.12
import Qt.labs.platform 1.1   // 用于获取跨平台可写临时目录

Item {
    id: root
    width: parent ? parent.width : 800
    height: parent ? parent.height : 600

    // 最近一次录音文件
    property url recordedUrl: ""

    function makeTempFileUrl() {
        // 跨平台临时目录
        var dir = StandardPaths.writableLocation(StandardPaths.TempLocation)
        var name = "asr_test_" + Date.now() + ".wav"
        // 归一化为 file:// URL
        var path = dir + "/" + name
        if (Qt.platform.os === "windows")
            return "file:///" + path.replace(/\\/g, "/")
        return "file://" + path
    }

    Rectangle { anchors.fill: parent; color: "#ffffff" }

    ColumnLayout {
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.8, 720)
        spacing: 16

        Label {
            text: "语音录音测试（原生）"
            font.pixelSize: 24
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            spacing: 12
            Layout.alignment: Qt.AlignLeft

            Button {
                id: recBtn
                text: recorder.state === AudioRecorder.RecordingState ? "停止录音" : "开始录音"
                onClicked: {
                    if (recorder.state === AudioRecorder.RecordingState) {
                        recorder.stop()
                    } else {
                        // 为本次录音生成一个临时文件
                        recorder.outputLocation = makeTempFileUrl()
                        logArea.append("将录音到: " + recorder.outputLocation)
                        recorder.record()
                    }
                }
            }

            Label {
                text: recorder.state === AudioRecorder.RecordingState ? "状态: 录音中" :
                      (recorder.state === AudioRecorder.PausedState ? "状态: 暂停" : "状态: 空闲")
                color: "#333"
            }
        }

        RowLayout {
            spacing: 12
            Layout.alignment: Qt.AlignLeft

            Button {
                text: "播放"
                enabled: recordedUrl !== ""
                onClicked: {
                    player.stop()
                    player.source = recordedUrl
                    player.play()
                    logArea.append("开始播放: " + recordedUrl)
                }
            }

            Button {
                text: "停止播放"
                enabled: recordedUrl !== ""
                onClicked: {
                    player.stop()
                    logArea.append("停止播放")
                }
            }

            Label {
                text: player.playbackState === Audio.PlayingState ? "状态: 播放中" :
                      (player.playbackState === Audio.PausedState ? "状态: 暂停" :
                      (player.playbackState === Audio.StoppedState ? "状态: 停止" : "状态: 未知"))
                color: "#333"
            }
        }

        TextField {
            Layout.fillWidth: true
            readOnly: true
            placeholderText: "录音文件路径"
            text: recordedUrl
        }

        TextArea {
            id: logArea
            Layout.fillWidth: true
            Layout.preferredHeight: 200
            readOnly: true
            placeholderText: "日志输出..."
        }
    }

    // 原生录音器（不使用自定义组件）
    AudioRecorder {
        id: recorder

        audioInput: "default"

        // WAV PCM 16k 单声道
        container: "audio/x-wav"
        audioEncoder.codec: "audio/pcm"
        audioEncoder.sampleRate: 16000
        audioEncoder.channelCount: 1
        audioEncoder.quality: AudioEncoderSettings.VeryHighQuality

        onStateChanged: {
            if (state === AudioRecorder.RecordingState) {
                logArea.append("开始录音...")
            } else if (state === AudioRecorder.StoppedState) {
                // 停止后，直接使用 outputLocation 作为结果
                recordedUrl = outputLocation
                logArea.append("录音结束，保存到: " + recordedUrl)
            }
        }

        onErrorChanged: {
            if (error !== AudioRecorder.NoError) {
                logArea.append("录音错误: " + errorString)
            }
        }
    }

    // 本地回放播放器
    Audio {
        id: player
        onErrorChanged: if (error !== Audio.NoError) logArea.append("播放错误: " + errorString)
    }
}

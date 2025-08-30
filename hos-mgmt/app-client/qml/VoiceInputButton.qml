import QtQuick 2.12
import QtQuick.Controls 2.5
import QtMultimedia 5.12

Item {
    id: root
    width: 120
    height: 40

    signal recordingFinished(url fileUrl)

    // 录音输出路径（Linux）
    property url outputUrl: "file:///tmp/asr.wav"

    AudioRecorder {
        id: recorder
        // 可选：指定设备，默认"default"
        audioInput: "default"
        outputLocation: root.outputUrl

        // WAV PCM 16k 单声道
        container: "audio/x-wav"
        audioEncoder.codec: "audio/pcm"
        audioEncoder.sampleRate: 16000
        audioEncoder.channelCount: 1
        audioEncoder.quality: AudioEncoderSettings.VeryHighQuality

        onStateChanged: {
            if (state === AudioRecorder.StoppedState) {
                // 录音停止时发出信号，把文件路径回传给上层
                root.recordingFinished(outputLocation)
            }
        }
    }

    Button {
        id: btn
        anchors.fill: parent
        text: recorder.state === AudioRecorder.RecordingState ? "停止" : "语音"
        onClicked: {
            if (recorder.state === AudioRecorder.RecordingState) {
                recorder.stop()
            } else {
                recorder.record()
            }
        }
    }
}

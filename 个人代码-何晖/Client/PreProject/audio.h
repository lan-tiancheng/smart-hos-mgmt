#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>

#include <QAudioDeviceInfo> //查询音频设备
#include <QAudioInput> //音频输入
#include <QAudioFormat> //音频存储

#include <QFile>

#include <speech.h>

#include <QMessageBox>
#include <QDebug>

class Audio : public QObject
{
    Q_OBJECT
public:
    explicit Audio(QObject *parent = nullptr);

signals:

public slots:

public:
    void startAudio(QString fileName);//初始化

    void stopAudio();//停止录音

    QString startSpeech();//开始录音并识别

private:
    QString AudioFileName;//用于记录音频文件名
    QFile *AudioFile;//用于操作音频文件

    QAudioInput *AudioDevice;//音频设备对象

    Speech *speech;//语音识别对象

};

#endif // AUDIO_H

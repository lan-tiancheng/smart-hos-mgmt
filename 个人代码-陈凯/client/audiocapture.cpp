#include "audiocapture.h"

AudioCapture::AudioCapture(QObject *parent) : QObject(parent)
{
    //初始化
    pAudioInput = nullptr;
    pFile = nullptr;
}

//开始录音
void AudioCapture::startCapture(QString filename)
{
    //打开默认的音频输入设备
    QAudioDeviceInfo audioDeviceInfo = QAudioDeviceInfo::defaultInputDevice();

    //判断本地是否有录音设备
    if(audioDeviceInfo.isNull() == false)
    {
        /* 创建文件并打开 */
        pFile = new QFile;
        pFile->setFileName(filename);
        pFile->open(QIODevice::WriteOnly | QIODevice::Truncate);

        // 设置音频文件格式
        QAudioFormat format;

        // 设置采样频率，常见的有16000、44100、48000
        format.setSampleRate(16000);

        // 设置通道数，单声道、双声道、5.1声道
        format.setChannelCount(1);

        // 设置每次采样得到的样本数据位值，8位、16位
        format.setSampleSize(16);

        // 设置编码方法
        format.setCodec("audio/pcm");

        // 判断当前设备设置是否支持该音频格式
        if(audioDeviceInfo.isFormatSupported(format) == NULL)
        {
            format = audioDeviceInfo.nearestFormat(format);
        }

        // 创建录音对象
        pAudioInput = new QAudioInput(format, this);

        // 开始录音
        pAudioInput->start(pFile);
    }

    else
    {
        // 没有录音设备
        QMessageBox::information(NULL, tr("Record"), tr("Current No Record Device"));
    }
}

void AudioCapture::stopCapture()
{
    if(pAudioInput != NULL)
    {
        // 停止录音
        pAudioInput->stop();
    }

    if(pFile != NULL)
    {
        // 关闭文件
        pFile->close();
        delete pFile;
        pFile = nullptr;
    }
}

AudioCapture::~AudioCapture()
{
    //释放资源
    if(pAudioInput != nullptr)
    {
        delete pAudioInput;
        pAudioInput = nullptr;
    }

    if(pFile != nullptr)
    {
        delete pFile;
        pFile = nullptr;
    }
}

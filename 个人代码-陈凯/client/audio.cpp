#include "audio.h"

Audio::Audio(QObject *parent) : QObject(parent)
{
    speech = new Speech(this);
}

void Audio::startAudio(QString fileName)
{
    if(fileName.isEmpty())
    {
        QMessageBox::warning(NULL,"警告(Audio)","无音频文件名");
        return;
    }
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();//用于检测音频设备状态信息
    if(device.isNull())
    {
        QMessageBox::warning(NULL,"警告(Audio)","无音频设备");
    }else{
        /* 记录录音文件 */
        AudioFileName = fileName;
        /* 音频编码要求 */
        QAudioFormat m_format;
        /* 设置采样频率 */
        m_format.setSampleRate(10000);
        /* 设置通道数 */
        m_format.setChannelCount(1);
        /* 设置位深 */
        m_format.setSampleSize(16);
        /* 设置编码格式 */
        m_format.setCodec("audio/pcm");//http上传推荐pcm格式；也可封装成json上传

        /* 判断设备是否支持该格式 */
        if(!device.isFormatSupported(m_format))
        {
            /* 寻找最接近的格式 */
            m_format = device.nearestFormat(m_format);
        }

        //打开文件，创建一个音频文件
        AudioFile = new QFile;
        AudioFile->setFileName(fileName);
        AudioFile->open(QIODevice::WriteOnly);

        /* 创建录音对象 */
        AudioDevice = new QAudioInput(m_format,this);
        AudioDevice->start(AudioFile);
    }

}

QString Audio::startSpeech()
{
    if(AudioFileName.isEmpty())//检查录音文件是否存在
    {
        QMessageBox::warning(NULL,"警告","文件不存在");
        return QString("");
    }
    return speech->speechIdentify(AudioFileName); //语音识别，并返回识别后的结果，调用speech中的函数
}

void Audio::stopAudio()
{
    /* 停止录音 */
    AudioDevice->stop();

    /* 关闭文件 */
    AudioFile->close();

    /* 删除文件对象指针并置空 */
    delete AudioFile;
    AudioFile = nullptr;


}

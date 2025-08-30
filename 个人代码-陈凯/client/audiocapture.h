#ifndef AUDIOCAPTURE_H
#define AUDIOCAPTURE_H

#include <QObject>
#include <QAudioInput>
#include <QFile>
#include <QMessageBox>

class AudioCapture : public QObject
{
    Q_OBJECT
public:
    explicit AudioCapture(QObject *parent = nullptr);
    void startCapture(QString filename);    //开始录音,文件名由调用者传入
    void stopCapture();                     //结束录音
    ~AudioCapture();                        //析构函数,释放相关资源
signals:
private:
    QAudioInput *pAudioInput;               //录音对象
    QFile       *pFile;                     //存取文件
};

#endif // AUDIOCAPTURE_H

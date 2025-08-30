#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "audiocapture.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AudioWd; }
QT_END_NAMESPACE

class AudioWd : public QWidget
{
    Q_OBJECT

public:
    AudioWd(QWidget *parent = nullptr);
    ~AudioWd();

private slots:
    void on_startPtn_clicked();     // 点击Start按钮后触发的槽函数

    void on_stopPtn_clicked();      // 点击Stop按钮后触发的槽函数

private:
    Ui::AudioWd *ui;                 //操作界面上的相关控件
    AudioCapture myAudioCapture;    //录音功能封装对象
};
#endif // WIDGET_H

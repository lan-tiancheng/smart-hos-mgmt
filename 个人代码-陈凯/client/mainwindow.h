#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextToSpeech>
#include <QVoice>
#include <QTextEdit>
#include "audio.h"//语音识别

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void soundstart();
    void soundend();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Audio *my_audio;
    QTextToSpeech *my_say;
    QPushButton *StartBtn;
    QPushButton *EndBtn;
    QPushButton *TestBtn;
    QTextEdit *textEditReco;
};

#endif // MAINWINDOW_H

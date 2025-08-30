#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QWidget>
#include "medicinesearchwindow.h"
#include "medicalexpensewd.h"
#include "quizwd.h"
#include <QTextToSpeech>
#include <QVoice>
#include "audio.h"//语音识别

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();
signals:
    void infoSearchSend(int);
    void infoMedicalExpenseSend();

private slots:
    void search();
    void on_quizBtn_clicked();

    void on_tempBtn_clicked();

public slots:
    void on_medicalexpenseBtn_clicked();

private:
    Ui::HomeWindow *ui;

};

#endif // HOMEWINDOW_H

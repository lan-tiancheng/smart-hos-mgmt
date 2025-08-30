/********************************************************************************
** Form generated from reading UI file 'audio.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIO_H
#define UI_AUDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_audio
{
public:

    void setupUi(QWidget *audio)
    {
        if (audio->objectName().isEmpty())
            audio->setObjectName(QString::fromUtf8("audio"));
        audio->resize(400, 300);

        retranslateUi(audio);

        QMetaObject::connectSlotsByName(audio);
    } // setupUi

    void retranslateUi(QWidget *audio)
    {
        audio->setWindowTitle(QApplication::translate("audio", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class audio: public Ui_audio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIO_H

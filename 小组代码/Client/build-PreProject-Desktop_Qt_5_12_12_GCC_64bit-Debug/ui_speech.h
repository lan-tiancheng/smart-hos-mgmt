/********************************************************************************
** Form generated from reading UI file 'speech.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPEECH_H
#define UI_SPEECH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_speech
{
public:

    void setupUi(QWidget *speech)
    {
        if (speech->objectName().isEmpty())
            speech->setObjectName(QString::fromUtf8("speech"));
        speech->resize(400, 300);

        retranslateUi(speech);

        QMetaObject::connectSlotsByName(speech);
    } // setupUi

    void retranslateUi(QWidget *speech)
    {
        speech->setWindowTitle(QApplication::translate("speech", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class speech: public Ui_speech {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPEECH_H

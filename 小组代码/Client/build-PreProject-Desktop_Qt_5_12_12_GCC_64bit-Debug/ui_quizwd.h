/********************************************************************************
** Form generated from reading UI file 'quizwd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIZWD_H
#define UI_QUIZWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_quizWd
{
public:

    void setupUi(QWidget *quizWd)
    {
        if (quizWd->objectName().isEmpty())
            quizWd->setObjectName(QString::fromUtf8("quizWd"));
        quizWd->resize(400, 300);

        retranslateUi(quizWd);

        QMetaObject::connectSlotsByName(quizWd);
    } // setupUi

    void retranslateUi(QWidget *quizWd)
    {
        quizWd->setWindowTitle(QApplication::translate("quizWd", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class quizWd: public Ui_quizWd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIZWD_H

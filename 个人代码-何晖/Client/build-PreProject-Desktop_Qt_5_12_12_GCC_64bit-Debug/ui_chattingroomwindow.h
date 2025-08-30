/********************************************************************************
** Form generated from reading UI file 'chattingroomwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATTINGROOMWINDOW_H
#define UI_CHATTINGROOMWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChattingroomWindow
{
public:

    void setupUi(QWidget *ChattingroomWindow)
    {
        if (ChattingroomWindow->objectName().isEmpty())
            ChattingroomWindow->setObjectName(QString::fromUtf8("ChattingroomWindow"));
        ChattingroomWindow->resize(400, 300);

        retranslateUi(ChattingroomWindow);

        QMetaObject::connectSlotsByName(ChattingroomWindow);
    } // setupUi

    void retranslateUi(QWidget *ChattingroomWindow)
    {
        ChattingroomWindow->setWindowTitle(QApplication::translate("ChattingroomWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChattingroomWindow: public Ui_ChattingroomWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATTINGROOMWINDOW_H

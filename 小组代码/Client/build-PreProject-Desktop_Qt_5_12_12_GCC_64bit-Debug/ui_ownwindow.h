/********************************************************************************
** Form generated from reading UI file 'ownwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OWNWINDOW_H
#define UI_OWNWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OwnWindow
{
public:

    void setupUi(QWidget *OwnWindow)
    {
        if (OwnWindow->objectName().isEmpty())
            OwnWindow->setObjectName(QString::fromUtf8("OwnWindow"));
        OwnWindow->resize(400, 300);

        retranslateUi(OwnWindow);

        QMetaObject::connectSlotsByName(OwnWindow);
    } // setupUi

    void retranslateUi(QWidget *OwnWindow)
    {
        OwnWindow->setWindowTitle(QApplication::translate("OwnWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OwnWindow: public Ui_OwnWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OWNWINDOW_H

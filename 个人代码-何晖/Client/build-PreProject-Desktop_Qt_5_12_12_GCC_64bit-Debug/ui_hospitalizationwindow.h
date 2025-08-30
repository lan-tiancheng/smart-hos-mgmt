/********************************************************************************
** Form generated from reading UI file 'hospitalizationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOSPITALIZATIONWINDOW_H
#define UI_HOSPITALIZATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HospitalizationWindow
{
public:

    void setupUi(QWidget *HospitalizationWindow)
    {
        if (HospitalizationWindow->objectName().isEmpty())
            HospitalizationWindow->setObjectName(QString::fromUtf8("HospitalizationWindow"));
        HospitalizationWindow->resize(400, 300);

        retranslateUi(HospitalizationWindow);

        QMetaObject::connectSlotsByName(HospitalizationWindow);
    } // setupUi

    void retranslateUi(QWidget *HospitalizationWindow)
    {
        HospitalizationWindow->setWindowTitle(QApplication::translate("HospitalizationWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HospitalizationWindow: public Ui_HospitalizationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOSPITALIZATIONWINDOW_H

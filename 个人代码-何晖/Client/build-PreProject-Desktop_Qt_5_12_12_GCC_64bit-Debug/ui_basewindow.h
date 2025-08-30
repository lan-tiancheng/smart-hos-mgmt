/********************************************************************************
** Form generated from reading UI file 'basewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEWINDOW_H
#define UI_BASEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseWindow
{
public:

    void setupUi(QWidget *BaseWindow)
    {
        if (BaseWindow->objectName().isEmpty())
            BaseWindow->setObjectName(QString::fromUtf8("BaseWindow"));
        BaseWindow->resize(400, 300);

        retranslateUi(BaseWindow);

        QMetaObject::connectSlotsByName(BaseWindow);
    } // setupUi

    void retranslateUi(QWidget *BaseWindow)
    {
        BaseWindow->setWindowTitle(QApplication::translate("BaseWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BaseWindow: public Ui_BaseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'womanwd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WOMANWD_H
#define UI_WOMANWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WomanWd
{
public:

    void setupUi(QWidget *WomanWd)
    {
        if (WomanWd->objectName().isEmpty())
            WomanWd->setObjectName(QString::fromUtf8("WomanWd"));
        WomanWd->resize(400, 300);

        retranslateUi(WomanWd);

        QMetaObject::connectSlotsByName(WomanWd);
    } // setupUi

    void retranslateUi(QWidget *WomanWd)
    {
        WomanWd->setWindowTitle(QApplication::translate("WomanWd", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WomanWd: public Ui_WomanWd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WOMANWD_H

/********************************************************************************
** Form generated from reading UI file 'outwd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTWD_H
#define UI_OUTWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OutWd
{
public:

    void setupUi(QWidget *OutWd)
    {
        if (OutWd->objectName().isEmpty())
            OutWd->setObjectName(QString::fromUtf8("OutWd"));
        OutWd->resize(400, 300);

        retranslateUi(OutWd);

        QMetaObject::connectSlotsByName(OutWd);
    } // setupUi

    void retranslateUi(QWidget *OutWd)
    {
        OutWd->setWindowTitle(QApplication::translate("OutWd", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OutWd: public Ui_OutWd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTWD_H

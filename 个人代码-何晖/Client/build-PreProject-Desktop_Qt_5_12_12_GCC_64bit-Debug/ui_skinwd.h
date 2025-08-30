/********************************************************************************
** Form generated from reading UI file 'skinwd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKINWD_H
#define UI_SKINWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SkinWd
{
public:

    void setupUi(QWidget *SkinWd)
    {
        if (SkinWd->objectName().isEmpty())
            SkinWd->setObjectName(QString::fromUtf8("SkinWd"));
        SkinWd->resize(400, 300);

        retranslateUi(SkinWd);

        QMetaObject::connectSlotsByName(SkinWd);
    } // setupUi

    void retranslateUi(QWidget *SkinWd)
    {
        SkinWd->setWindowTitle(QApplication::translate("SkinWd", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SkinWd: public Ui_SkinWd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKINWD_H

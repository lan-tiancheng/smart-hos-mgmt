/********************************************************************************
** Form generated from reading UI file 'ownillness.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OWNILLNESS_H
#define UI_OWNILLNESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ownillness
{
public:

    void setupUi(QWidget *ownillness)
    {
        if (ownillness->objectName().isEmpty())
            ownillness->setObjectName(QString::fromUtf8("ownillness"));
        ownillness->resize(400, 300);

        retranslateUi(ownillness);

        QMetaObject::connectSlotsByName(ownillness);
    } // setupUi

    void retranslateUi(QWidget *ownillness)
    {
        ownillness->setWindowTitle(QApplication::translate("ownillness", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ownillness: public Ui_ownillness {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OWNILLNESS_H

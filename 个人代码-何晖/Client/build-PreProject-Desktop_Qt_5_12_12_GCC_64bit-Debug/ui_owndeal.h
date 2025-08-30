/********************************************************************************
** Form generated from reading UI file 'owndeal.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OWNDEAL_H
#define UI_OWNDEAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_owndeal
{
public:

    void setupUi(QWidget *owndeal)
    {
        if (owndeal->objectName().isEmpty())
            owndeal->setObjectName(QString::fromUtf8("owndeal"));
        owndeal->resize(400, 300);

        retranslateUi(owndeal);

        QMetaObject::connectSlotsByName(owndeal);
    } // setupUi

    void retranslateUi(QWidget *owndeal)
    {
        owndeal->setWindowTitle(QApplication::translate("owndeal", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class owndeal: public Ui_owndeal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OWNDEAL_H

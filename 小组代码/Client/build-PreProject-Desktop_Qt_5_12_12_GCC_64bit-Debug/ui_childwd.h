/********************************************************************************
** Form generated from reading UI file 'childwd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHILDWD_H
#define UI_CHILDWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChildWd
{
public:

    void setupUi(QWidget *ChildWd)
    {
        if (ChildWd->objectName().isEmpty())
            ChildWd->setObjectName(QString::fromUtf8("ChildWd"));
        ChildWd->resize(716, 571);

        retranslateUi(ChildWd);

        QMetaObject::connectSlotsByName(ChildWd);
    } // setupUi

    void retranslateUi(QWidget *ChildWd)
    {
        ChildWd->setWindowTitle(QApplication::translate("ChildWd", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChildWd: public Ui_ChildWd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHILDWD_H

/********************************************************************************
** Form generated from reading UI file 'insidewd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSIDEWD_H
#define UI_INSIDEWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InsideWd
{
public:

    void setupUi(QWidget *InsideWd)
    {
        if (InsideWd->objectName().isEmpty())
            InsideWd->setObjectName(QString::fromUtf8("InsideWd"));
        InsideWd->resize(400, 300);

        retranslateUi(InsideWd);

        QMetaObject::connectSlotsByName(InsideWd);
    } // setupUi

    void retranslateUi(QWidget *InsideWd)
    {
        InsideWd->setWindowTitle(QApplication::translate("InsideWd", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InsideWd: public Ui_InsideWd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSIDEWD_H

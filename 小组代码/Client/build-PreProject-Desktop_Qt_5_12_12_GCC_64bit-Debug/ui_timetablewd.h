/********************************************************************************
** Form generated from reading UI file 'timetablewd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMETABLEWD_H
#define UI_TIMETABLEWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimetableWd
{
public:

    void setupUi(QWidget *TimetableWd)
    {
        if (TimetableWd->objectName().isEmpty())
            TimetableWd->setObjectName(QString::fromUtf8("TimetableWd"));
        TimetableWd->resize(400, 326);

        retranslateUi(TimetableWd);

        QMetaObject::connectSlotsByName(TimetableWd);
    } // setupUi

    void retranslateUi(QWidget *TimetableWd)
    {
        TimetableWd->setWindowTitle(QApplication::translate("TimetableWd", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimetableWd: public Ui_TimetableWd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMETABLEWD_H

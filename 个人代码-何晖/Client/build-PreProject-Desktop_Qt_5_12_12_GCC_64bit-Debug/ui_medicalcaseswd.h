/********************************************************************************
** Form generated from reading UI file 'medicalcaseswd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDICALCASESWD_H
#define UI_MEDICALCASESWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MedicalcasesWd
{
public:
    QTextBrowser *textBrowser;

    void setupUi(QWidget *MedicalcasesWd)
    {
        if (MedicalcasesWd->objectName().isEmpty())
            MedicalcasesWd->setObjectName(QString::fromUtf8("MedicalcasesWd"));
        MedicalcasesWd->resize(471, 467);
        textBrowser = new QTextBrowser(MedicalcasesWd);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(100, 190, 256, 192));

        retranslateUi(MedicalcasesWd);

        QMetaObject::connectSlotsByName(MedicalcasesWd);
    } // setupUi

    void retranslateUi(QWidget *MedicalcasesWd)
    {
        MedicalcasesWd->setWindowTitle(QApplication::translate("MedicalcasesWd", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MedicalcasesWd: public Ui_MedicalcasesWd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDICALCASESWD_H

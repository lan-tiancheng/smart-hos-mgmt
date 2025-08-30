/********************************************************************************
** Form generated from reading UI file 'medicalexpensewd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDICALEXPENSEWD_H
#define UI_MEDICALEXPENSEWD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MedicalExpenseWd
{
public:
    QLabel *label_image;

    void setupUi(QWidget *MedicalExpenseWd)
    {
        if (MedicalExpenseWd->objectName().isEmpty())
            MedicalExpenseWd->setObjectName(QString::fromUtf8("MedicalExpenseWd"));
        MedicalExpenseWd->resize(530, 467);
        label_image = new QLabel(MedicalExpenseWd);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        label_image->setGeometry(QRect(90, 60, 301, 281));
        label_image->setStyleSheet(QString::fromUtf8("image: url(:/supporting.jpg);"));

        retranslateUi(MedicalExpenseWd);

        QMetaObject::connectSlotsByName(MedicalExpenseWd);
    } // setupUi

    void retranslateUi(QWidget *MedicalExpenseWd)
    {
        MedicalExpenseWd->setWindowTitle(QApplication::translate("MedicalExpenseWd", "Form", nullptr));
        label_image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MedicalExpenseWd: public Ui_MedicalExpenseWd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDICALEXPENSEWD_H

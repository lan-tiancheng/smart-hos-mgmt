/********************************************************************************
** Form generated from reading UI file 'absence.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABSENCE_H
#define UI_ABSENCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Absence
{
public:
    QLabel *messageLabel;
    QPushButton *okButton;

    void setupUi(QDialog *Absence)
    {
        if (Absence->objectName().isEmpty())
            Absence->setObjectName(QString::fromUtf8("Absence"));
        Absence->resize(300, 150);
        messageLabel = new QLabel(Absence);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setGeometry(QRect(20, 20, 260, 60));
        messageLabel->setAlignment(Qt::AlignCenter);
        okButton = new QPushButton(Absence);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(100, 90, 100, 30));

        retranslateUi(Absence);

        QMetaObject::connectSlotsByName(Absence);
    } // setupUi

    void retranslateUi(QDialog *Absence)
    {
        Absence->setWindowTitle(QApplication::translate("Absence", "Success", nullptr));
        messageLabel->setText(QApplication::translate("Absence", "Absence marked successfully!", nullptr));
        okButton->setText(QApplication::translate("Absence", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Absence: public Ui_Absence {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABSENCE_H

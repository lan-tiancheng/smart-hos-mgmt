/********************************************************************************
** Form generated from reading UI file 'medicinesearchwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDICINESEARCHWINDOW_H
#define UI_MEDICINESEARCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MedicineSearchWindow
{
public:
    QPushButton *backbtn;
    QLineEdit *lineEdit;
    QPushButton *searchBtn;

    void setupUi(QWidget *MedicineSearchWindow)
    {
        if (MedicineSearchWindow->objectName().isEmpty())
            MedicineSearchWindow->setObjectName(QString::fromUtf8("MedicineSearchWindow"));
        MedicineSearchWindow->resize(700, 700);
        MedicineSearchWindow->setStyleSheet(QString::fromUtf8(""));
        backbtn = new QPushButton(MedicineSearchWindow);
        backbtn->setObjectName(QString::fromUtf8("backbtn"));
        backbtn->setGeometry(QRect(10, 10, 89, 25));
        lineEdit = new QLineEdit(MedicineSearchWindow);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(190, 70, 271, 41));
        searchBtn = new QPushButton(MedicineSearchWindow);
        searchBtn->setObjectName(QString::fromUtf8("searchBtn"));
        searchBtn->setGeometry(QRect(500, 70, 101, 41));

        retranslateUi(MedicineSearchWindow);

        QMetaObject::connectSlotsByName(MedicineSearchWindow);
    } // setupUi

    void retranslateUi(QWidget *MedicineSearchWindow)
    {
        MedicineSearchWindow->setWindowTitle(QApplication::translate("MedicineSearchWindow", "Form", nullptr));
        backbtn->setText(QApplication::translate("MedicineSearchWindow", "back", nullptr));
        lineEdit->setPlaceholderText(QApplication::translate("MedicineSearchWindow", "\350\257\267\350\276\223\345\205\245\346\203\263\350\246\201\346\237\245\346\211\276\347\232\204\345\206\205\345\256\271", nullptr));
        searchBtn->setText(QApplication::translate("MedicineSearchWindow", "?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MedicineSearchWindow: public Ui_MedicineSearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDICINESEARCHWINDOW_H

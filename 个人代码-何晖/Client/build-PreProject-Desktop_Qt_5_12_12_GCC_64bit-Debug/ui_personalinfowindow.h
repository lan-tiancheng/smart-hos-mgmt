/********************************************************************************
** Form generated from reading UI file 'personalinfowindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONALINFOWINDOW_H
#define UI_PERSONALINFOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PersonalInfoWindow
{
public:
    QLineEdit *nameEdit;
    QLineEdit *nicknameEdit;
    QLineEdit *userEdit;
    QLineEdit *passwordEdit;
    QLineEdit *emailEdit;
    QDateEdit *birthdateEdit;
    QCheckBox *male;
    QCheckBox *female;
    QLabel *title;

    void setupUi(QWidget *PersonalInfoWindow)
    {
        if (PersonalInfoWindow->objectName().isEmpty())
            PersonalInfoWindow->setObjectName(QString::fromUtf8("PersonalInfoWindow"));
        PersonalInfoWindow->resize(544, 538);
        nameEdit = new QLineEdit(PersonalInfoWindow);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setGeometry(QRect(70, 120, 113, 25));
        nicknameEdit = new QLineEdit(PersonalInfoWindow);
        nicknameEdit->setObjectName(QString::fromUtf8("nicknameEdit"));
        nicknameEdit->setGeometry(QRect(70, 280, 113, 25));
        userEdit = new QLineEdit(PersonalInfoWindow);
        userEdit->setObjectName(QString::fromUtf8("userEdit"));
        userEdit->setGeometry(QRect(70, 330, 113, 25));
        passwordEdit = new QLineEdit(PersonalInfoWindow);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setGeometry(QRect(70, 380, 113, 25));
        emailEdit = new QLineEdit(PersonalInfoWindow);
        emailEdit->setObjectName(QString::fromUtf8("emailEdit"));
        emailEdit->setGeometry(QRect(70, 440, 113, 25));
        birthdateEdit = new QDateEdit(PersonalInfoWindow);
        birthdateEdit->setObjectName(QString::fromUtf8("birthdateEdit"));
        birthdateEdit->setGeometry(QRect(70, 230, 110, 26));
        male = new QCheckBox(PersonalInfoWindow);
        male->setObjectName(QString::fromUtf8("male"));
        male->setGeometry(QRect(70, 160, 92, 23));
        female = new QCheckBox(PersonalInfoWindow);
        female->setObjectName(QString::fromUtf8("female"));
        female->setGeometry(QRect(70, 190, 92, 23));
        title = new QLabel(PersonalInfoWindow);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(80, 80, 161, 17));

        retranslateUi(PersonalInfoWindow);

        QMetaObject::connectSlotsByName(PersonalInfoWindow);
    } // setupUi

    void retranslateUi(QWidget *PersonalInfoWindow)
    {
        PersonalInfoWindow->setWindowTitle(QApplication::translate("PersonalInfoWindow", "Form", nullptr));
        nameEdit->setPlaceholderText(QApplication::translate("PersonalInfoWindow", "\345\247\223\345\220\215", nullptr));
        nicknameEdit->setPlaceholderText(QApplication::translate("PersonalInfoWindow", "\346\230\265\347\247\260", nullptr));
        userEdit->setPlaceholderText(QApplication::translate("PersonalInfoWindow", "\350\264\246\345\217\267", nullptr));
        passwordEdit->setPlaceholderText(QApplication::translate("PersonalInfoWindow", "\345\257\206\347\240\201", nullptr));
        emailEdit->setPlaceholderText(QApplication::translate("PersonalInfoWindow", "\351\202\256\347\256\261", nullptr));
        male->setText(QApplication::translate("PersonalInfoWindow", "\347\224\267", nullptr));
        female->setText(QApplication::translate("PersonalInfoWindow", "\345\245\263", nullptr));
        title->setText(QApplication::translate("PersonalInfoWindow", "\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PersonalInfoWindow: public Ui_PersonalInfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONALINFOWINDOW_H

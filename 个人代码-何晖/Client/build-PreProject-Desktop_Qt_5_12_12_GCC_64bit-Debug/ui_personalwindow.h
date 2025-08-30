/********************************************************************************
** Form generated from reading UI file 'personalwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONALWINDOW_H
#define UI_PERSONALWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PersonalWindow
{
public:
    QLabel *medicalcasesText;
    QLabel *medicalcases;
    QLabel *personalinfoText;
    QLabel *personalinfo;
    QPushButton *personalinfoBtn;
    QPushButton *medicalcasesBtn;

    void setupUi(QWidget *PersonalWindow)
    {
        if (PersonalWindow->objectName().isEmpty())
            PersonalWindow->setObjectName(QString::fromUtf8("PersonalWindow"));
        PersonalWindow->resize(800, 600);
        medicalcasesText = new QLabel(PersonalWindow);
        medicalcasesText->setObjectName(QString::fromUtf8("medicalcasesText"));
        medicalcasesText->setGeometry(QRect(400, 480, 67, 17));
        medicalcases = new QLabel(PersonalWindow);
        medicalcases->setObjectName(QString::fromUtf8("medicalcases"));
        medicalcases->setGeometry(QRect(390, 360, 81, 51));
        medicalcases->setStyleSheet(QString::fromUtf8("image: url(:/chat-icon.jpg);"));
        personalinfoText = new QLabel(PersonalWindow);
        personalinfoText->setObjectName(QString::fromUtf8("personalinfoText"));
        personalinfoText->setGeometry(QRect(250, 480, 67, 17));
        personalinfo = new QLabel(PersonalWindow);
        personalinfo->setObjectName(QString::fromUtf8("personalinfo"));
        personalinfo->setGeometry(QRect(230, 350, 101, 61));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(personalinfo->sizePolicy().hasHeightForWidth());
        personalinfo->setSizePolicy(sizePolicy);
        personalinfo->setStyleSheet(QString::fromUtf8("image: url(:/chat-icon.jpg);"));
        personalinfo->setPixmap(QPixmap(QString::fromUtf8(":/personal-profile-icon.jpg")));
        personalinfoBtn = new QPushButton(PersonalWindow);
        personalinfoBtn->setObjectName(QString::fromUtf8("personalinfoBtn"));
        personalinfoBtn->setGeometry(QRect(250, 420, 61, 51));
        personalinfoBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255,0);"));
        medicalcasesBtn = new QPushButton(PersonalWindow);
        medicalcasesBtn->setObjectName(QString::fromUtf8("medicalcasesBtn"));
        medicalcasesBtn->setGeometry(QRect(400, 420, 61, 51));

        retranslateUi(PersonalWindow);

        QMetaObject::connectSlotsByName(PersonalWindow);
    } // setupUi

    void retranslateUi(QWidget *PersonalWindow)
    {
        PersonalWindow->setWindowTitle(QApplication::translate("PersonalWindow", "Form", nullptr));
        medicalcasesText->setText(QApplication::translate("PersonalWindow", "\344\270\252\344\272\272\347\227\205\344\276\213", nullptr));
        medicalcases->setText(QString());
        personalinfoText->setText(QApplication::translate("PersonalWindow", "\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
        personalinfo->setText(QString());
        personalinfoBtn->setText(QString());
        medicalcasesBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PersonalWindow: public Ui_PersonalWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONALWINDOW_H

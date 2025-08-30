/********************************************************************************
** Form generated from reading UI file 'ownmessage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OWNMESSAGE_H
#define UI_OWNMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ownmessage
{
public:

    void setupUi(QWidget *ownmessage)
    {
        if (ownmessage->objectName().isEmpty())
            ownmessage->setObjectName(QString::fromUtf8("ownmessage"));
        ownmessage->resize(400, 300);

        retranslateUi(ownmessage);

        QMetaObject::connectSlotsByName(ownmessage);
    } // setupUi

    void retranslateUi(QWidget *ownmessage)
    {
        ownmessage->setWindowTitle(QApplication::translate("ownmessage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ownmessage: public Ui_ownmessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OWNMESSAGE_H

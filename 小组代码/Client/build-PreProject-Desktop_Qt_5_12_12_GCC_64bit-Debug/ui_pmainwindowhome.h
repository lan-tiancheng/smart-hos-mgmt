/********************************************************************************
** Form generated from reading UI file 'pmainwindowhome.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PMAINWINDOWHOME_H
#define UI_PMAINWINDOWHOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PMainWindowHome
{
public:

    void setupUi(QWidget *PMainWindowHome)
    {
        if (PMainWindowHome->objectName().isEmpty())
            PMainWindowHome->setObjectName(QString::fromUtf8("PMainWindowHome"));
        PMainWindowHome->resize(719, 670);

        retranslateUi(PMainWindowHome);

        QMetaObject::connectSlotsByName(PMainWindowHome);
    } // setupUi

    void retranslateUi(QWidget *PMainWindowHome)
    {
        PMainWindowHome->setWindowTitle(QApplication::translate("PMainWindowHome", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PMainWindowHome: public Ui_PMainWindowHome {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PMAINWINDOWHOME_H

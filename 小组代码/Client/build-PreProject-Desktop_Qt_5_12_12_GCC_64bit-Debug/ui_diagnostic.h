/********************************************************************************
** Form generated from reading UI file 'diagnostic.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAGNOSTIC_H
#define UI_DIAGNOSTIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DiagnosticDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEditResult;
    QHBoxLayout *buttonLayout;
    QPushButton *buttonConfirm;
    QPushButton *buttonCancel;

    void setupUi(QDialog *DiagnosticDialog)
    {
        if (DiagnosticDialog->objectName().isEmpty())
            DiagnosticDialog->setObjectName(QString::fromUtf8("DiagnosticDialog"));
        DiagnosticDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(DiagnosticDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEditResult = new QTextEdit(DiagnosticDialog);
        textEditResult->setObjectName(QString::fromUtf8("textEditResult"));

        verticalLayout->addWidget(textEditResult);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        buttonConfirm = new QPushButton(DiagnosticDialog);
        buttonConfirm->setObjectName(QString::fromUtf8("buttonConfirm"));

        buttonLayout->addWidget(buttonConfirm);

        buttonCancel = new QPushButton(DiagnosticDialog);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        buttonLayout->addWidget(buttonCancel);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(DiagnosticDialog);

        QMetaObject::connectSlotsByName(DiagnosticDialog);
    } // setupUi

    void retranslateUi(QDialog *DiagnosticDialog)
    {
        DiagnosticDialog->setWindowTitle(QApplication::translate("DiagnosticDialog", "\350\257\212\346\226\255\347\273\223\346\236\234", nullptr));
        textEditResult->setPlaceholderText(QApplication::translate("DiagnosticDialog", "\350\257\267\350\276\223\345\205\245\350\257\212\346\226\255\347\273\223\346\236\234...", nullptr));
        buttonConfirm->setText(QApplication::translate("DiagnosticDialog", "\347\241\256\350\256\244", nullptr));
        buttonCancel->setText(QApplication::translate("DiagnosticDialog", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiagnosticDialog: public Ui_DiagnosticDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAGNOSTIC_H

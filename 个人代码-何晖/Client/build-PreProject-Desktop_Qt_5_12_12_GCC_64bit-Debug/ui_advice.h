/********************************************************************************
** Form generated from reading UI file 'advice.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADVICE_H
#define UI_ADVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_advice
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEditResult;
    QHBoxLayout *buttonLayout;
    QPushButton *buttonConfirm;
    QPushButton *buttonCancel;

    void setupUi(QWidget *advice)
    {
        if (advice->objectName().isEmpty())
            advice->setObjectName(QString::fromUtf8("advice"));
        advice->resize(400, 300);
        verticalLayout = new QVBoxLayout(advice);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEditResult = new QTextEdit(advice);
        textEditResult->setObjectName(QString::fromUtf8("textEditResult"));

        verticalLayout->addWidget(textEditResult);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        buttonConfirm = new QPushButton(advice);
        buttonConfirm->setObjectName(QString::fromUtf8("buttonConfirm"));

        buttonLayout->addWidget(buttonConfirm);

        buttonCancel = new QPushButton(advice);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        buttonLayout->addWidget(buttonCancel);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(advice);

        QMetaObject::connectSlotsByName(advice);
    } // setupUi

    void retranslateUi(QWidget *advice)
    {
        advice->setWindowTitle(QApplication::translate("advice", "\345\214\273\345\230\261", nullptr));
        textEditResult->setPlaceholderText(QApplication::translate("advice", "\350\257\267\350\276\223\345\205\245\345\214\273\345\230\261...", nullptr));
        buttonConfirm->setText(QApplication::translate("advice", "\347\241\256\350\256\244", nullptr));
        buttonCancel->setText(QApplication::translate("advice", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class advice: public Ui_advice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADVICE_H

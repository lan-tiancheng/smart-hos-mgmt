/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *head_label;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *emailEdit;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *passEdit;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    ClickedLabel *forget_label;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *loginBtn;
    QSpacerItem *horizontalSpacer_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(500, 800);
        LoginDialog->setMinimumSize(QSize(500, 800));
        LoginDialog->setMaximumSize(QSize(500, 800));
        verticalLayout_2 = new QVBoxLayout(LoginDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(LoginDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        head_label = new QLabel(widget);
        head_label->setObjectName(QString::fromUtf8("head_label"));
        head_label->setMinimumSize(QSize(200, 200));
        head_label->setMaximumSize(QSize(200, 200));
        head_label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(head_label, 1, 0, 1, 1);

        err_tip = new QLabel(widget);
        err_tip->setObjectName(QString::fromUtf8("err_tip"));
        err_tip->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(err_tip, 0, 0, 1, 1);


        verticalLayout->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        emailEdit = new QLineEdit(LoginDialog);
        emailEdit->setObjectName(QString::fromUtf8("emailEdit"));

        horizontalLayout->addWidget(emailEdit);


        verticalLayout->addLayout(horizontalLayout);

        widget_2 = new QWidget(LoginDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        passEdit = new QLineEdit(widget_2);
        passEdit->setObjectName(QString::fromUtf8("passEdit"));

        horizontalLayout_2->addWidget(passEdit);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(LoginDialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(790, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        forget_label = new ClickedLabel(widget_3);
        forget_label->setObjectName(QString::fromUtf8("forget_label"));
        forget_label->setMinimumSize(QSize(0, 20));
        forget_label->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_3->addWidget(forget_label);


        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(LoginDialog);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(381, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        loginBtn = new QPushButton(widget_4);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));

        horizontalLayout_4->addWidget(loginBtn);

        horizontalSpacer_3 = new QSpacerItem(380, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(widget_4);

        widget_5 = new QWidget(LoginDialog);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_5 = new QHBoxLayout(widget_5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(381, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        pushButton_2 = new QPushButton(widget_5);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout_5->addWidget(pushButton_2);

        horizontalSpacer_5 = new QSpacerItem(380, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout->addWidget(widget_5);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", nullptr));
        head_label->setText(QString());
        err_tip->setText(QString());
        label->setText(QApplication::translate("LoginDialog", "\347\224\250\346\210\267", nullptr));
        label_3->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", nullptr));
        forget_label->setText(QApplication::translate("LoginDialog", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        loginBtn->setText(QApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        pushButton_2->setText(QApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H

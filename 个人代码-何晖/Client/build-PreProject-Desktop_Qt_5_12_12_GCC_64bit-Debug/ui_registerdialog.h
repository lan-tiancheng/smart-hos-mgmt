/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickedlabel.h"
#include "timerbtn.h"

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QLabel *err_tip;
    QHBoxLayout *horizontalLayout;
    QLabel *user_label;
    QLineEdit *user_edit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *email_label;
    QLineEdit *email_edit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *pass_label;
    QLineEdit *pass_edit;
    ClickedLabel *pass_visible;
    QHBoxLayout *horizontalLayout_5;
    QLabel *confirm_label;
    QLineEdit *confirm_edit;
    ClickedLabel *confirm_visible;
    QHBoxLayout *horizontalLayout_6;
    QLabel *varify_label;
    QLineEdit *varify_edit;
    TimerBtn *get_code;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *sure_btn;
    QPushButton *cancel_btn;
    QSpacerItem *verticalSpacer_3;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_10;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_8;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_7;
    QLabel *errTip;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label;
    QLineEdit *nameEdit;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_2;
    QRadioButton *manRadioButton;
    QRadioButton *womanRadbutton;
    QRadioButton *otherSex;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_3;
    QLineEdit *yearEdit;
    QLabel *label_5;
    QLineEdit *monthEdit;
    QLabel *label_6;
    QLineEdit *dataEdit;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_4;
    QLineEdit *IDcardEdit;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_7;
    QLineEdit *phoneEdit;
    QPushButton *confirmInfo;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_5;
    QLabel *tip_lb;
    QLabel *tip2_lb;
    QSpacerItem *verticalSpacer_6;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *return_btn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName(QString::fromUtf8("RegisterDialog"));
        RegisterDialog->resize(500, 800);
        RegisterDialog->setMinimumSize(QSize(500, 800));
        RegisterDialog->setMaximumSize(QSize(500, 800));
        horizontalLayout_8 = new QHBoxLayout(RegisterDialog);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(RegisterDialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_3 = new QVBoxLayout(page);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        widget = new QWidget(page);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        err_tip = new QLabel(widget);
        err_tip->setObjectName(QString::fromUtf8("err_tip"));
        err_tip->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(err_tip);


        verticalLayout_3->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        user_label = new QLabel(page);
        user_label->setObjectName(QString::fromUtf8("user_label"));
        user_label->setMinimumSize(QSize(0, 25));
        user_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_label);

        user_edit = new QLineEdit(page);
        user_edit->setObjectName(QString::fromUtf8("user_edit"));
        user_edit->setMinimumSize(QSize(0, 25));
        user_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_edit);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        email_label = new QLabel(page);
        email_label->setObjectName(QString::fromUtf8("email_label"));
        email_label->setMinimumSize(QSize(0, 25));
        email_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(email_label);

        email_edit = new QLineEdit(page);
        email_edit->setObjectName(QString::fromUtf8("email_edit"));
        email_edit->setMinimumSize(QSize(0, 25));
        email_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(email_edit);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pass_label = new QLabel(page);
        pass_label->setObjectName(QString::fromUtf8("pass_label"));
        pass_label->setMinimumSize(QSize(0, 25));
        pass_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(pass_label);

        pass_edit = new QLineEdit(page);
        pass_edit->setObjectName(QString::fromUtf8("pass_edit"));
        pass_edit->setMinimumSize(QSize(0, 25));
        pass_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_4->addWidget(pass_edit);

        pass_visible = new ClickedLabel(page);
        pass_visible->setObjectName(QString::fromUtf8("pass_visible"));
        pass_visible->setMinimumSize(QSize(20, 20));
        pass_visible->setMaximumSize(QSize(20, 20));
        pass_visible->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(pass_visible);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        confirm_label = new QLabel(page);
        confirm_label->setObjectName(QString::fromUtf8("confirm_label"));
        confirm_label->setMinimumSize(QSize(0, 25));
        confirm_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(confirm_label);

        confirm_edit = new QLineEdit(page);
        confirm_edit->setObjectName(QString::fromUtf8("confirm_edit"));
        confirm_edit->setMinimumSize(QSize(0, 25));
        confirm_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_5->addWidget(confirm_edit);

        confirm_visible = new ClickedLabel(page);
        confirm_visible->setObjectName(QString::fromUtf8("confirm_visible"));
        confirm_visible->setMinimumSize(QSize(20, 20));
        confirm_visible->setMaximumSize(QSize(20, 20));
        confirm_visible->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(confirm_visible);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        varify_label = new QLabel(page);
        varify_label->setObjectName(QString::fromUtf8("varify_label"));
        varify_label->setMinimumSize(QSize(0, 25));
        varify_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(varify_label);

        varify_edit = new QLineEdit(page);
        varify_edit->setObjectName(QString::fromUtf8("varify_edit"));
        varify_edit->setMinimumSize(QSize(0, 25));
        varify_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(varify_edit);

        get_code = new TimerBtn(page);
        get_code->setObjectName(QString::fromUtf8("get_code"));
        get_code->setMinimumSize(QSize(0, 25));
        get_code->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(get_code);


        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        sure_btn = new QPushButton(page);
        sure_btn->setObjectName(QString::fromUtf8("sure_btn"));
        sure_btn->setMinimumSize(QSize(0, 25));
        sure_btn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(sure_btn);

        cancel_btn = new QPushButton(page);
        cancel_btn->setObjectName(QString::fromUtf8("cancel_btn"));
        cancel_btn->setMinimumSize(QSize(0, 25));
        cancel_btn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_7->addWidget(cancel_btn);


        verticalLayout_3->addLayout(horizontalLayout_7);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_6 = new QVBoxLayout(page_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        widget_10 = new QWidget(page_2);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        verticalLayout_2 = new QVBoxLayout(widget_10);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_8 = new QWidget(widget_10);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        horizontalLayout_14 = new QHBoxLayout(widget_8);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_8 = new QLabel(widget_8);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(label_8);


        verticalLayout_2->addWidget(widget_8);

        widget_9 = new QWidget(widget_10);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        verticalLayout_7 = new QVBoxLayout(widget_9);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        errTip = new QLabel(widget_9);
        errTip->setObjectName(QString::fromUtf8("errTip"));
        errTip->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(errTip);


        verticalLayout_2->addWidget(widget_9);

        widget_3 = new QWidget(widget_10);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_9 = new QHBoxLayout(widget_3);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label = new QLabel(widget_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_9->addWidget(label);

        nameEdit = new QLineEdit(widget_3);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

        horizontalLayout_9->addWidget(nameEdit);


        verticalLayout_2->addWidget(widget_3);

        widget_4 = new QWidget(widget_10);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout_10 = new QHBoxLayout(widget_4);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_2 = new QLabel(widget_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_10->addWidget(label_2);

        manRadioButton = new QRadioButton(widget_4);
        manRadioButton->setObjectName(QString::fromUtf8("manRadioButton"));

        horizontalLayout_10->addWidget(manRadioButton);

        womanRadbutton = new QRadioButton(widget_4);
        womanRadbutton->setObjectName(QString::fromUtf8("womanRadbutton"));

        horizontalLayout_10->addWidget(womanRadbutton);

        otherSex = new QRadioButton(widget_4);
        otherSex->setObjectName(QString::fromUtf8("otherSex"));

        horizontalLayout_10->addWidget(otherSex);


        verticalLayout_2->addWidget(widget_4);

        widget_5 = new QWidget(widget_10);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_11 = new QHBoxLayout(widget_5);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_3 = new QLabel(widget_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_11->addWidget(label_3);

        yearEdit = new QLineEdit(widget_5);
        yearEdit->setObjectName(QString::fromUtf8("yearEdit"));

        horizontalLayout_11->addWidget(yearEdit);

        label_5 = new QLabel(widget_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_11->addWidget(label_5);

        monthEdit = new QLineEdit(widget_5);
        monthEdit->setObjectName(QString::fromUtf8("monthEdit"));

        horizontalLayout_11->addWidget(monthEdit);

        label_6 = new QLabel(widget_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_11->addWidget(label_6);

        dataEdit = new QLineEdit(widget_5);
        dataEdit->setObjectName(QString::fromUtf8("dataEdit"));

        horizontalLayout_11->addWidget(dataEdit);


        verticalLayout_2->addWidget(widget_5);

        widget_6 = new QWidget(widget_10);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_12 = new QHBoxLayout(widget_6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_4 = new QLabel(widget_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_12->addWidget(label_4);

        IDcardEdit = new QLineEdit(widget_6);
        IDcardEdit->setObjectName(QString::fromUtf8("IDcardEdit"));

        horizontalLayout_12->addWidget(IDcardEdit);


        verticalLayout_2->addWidget(widget_6);

        widget_7 = new QWidget(widget_10);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        horizontalLayout_13 = new QHBoxLayout(widget_7);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_7 = new QLabel(widget_7);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_13->addWidget(label_7);

        phoneEdit = new QLineEdit(widget_7);
        phoneEdit->setObjectName(QString::fromUtf8("phoneEdit"));

        horizontalLayout_13->addWidget(phoneEdit);


        verticalLayout_2->addWidget(widget_7);

        confirmInfo = new QPushButton(widget_10);
        confirmInfo->setObjectName(QString::fromUtf8("confirmInfo"));

        verticalLayout_2->addWidget(confirmInfo);


        verticalLayout_6->addWidget(widget_10);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_5 = new QVBoxLayout(page_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);

        tip_lb = new QLabel(page_3);
        tip_lb->setObjectName(QString::fromUtf8("tip_lb"));
        tip_lb->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(tip_lb);

        tip2_lb = new QLabel(page_3);
        tip2_lb->setObjectName(QString::fromUtf8("tip2_lb"));
        tip2_lb->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(tip2_lb);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_6);

        widget_2 = new QWidget(page_3);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        return_btn = new QPushButton(widget_2);
        return_btn->setObjectName(QString::fromUtf8("return_btn"));
        return_btn->setMinimumSize(QSize(0, 25));
        return_btn->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(return_btn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_5->addWidget(widget_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);

        stackedWidget->addWidget(page_3);

        verticalLayout->addWidget(stackedWidget);


        horizontalLayout_8->addLayout(verticalLayout);


        retranslateUi(RegisterDialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QApplication::translate("RegisterDialog", "Dialog", nullptr));
        err_tip->setText(QApplication::translate("RegisterDialog", "\351\224\231\350\257\257\346\217\220\347\244\272", nullptr));
        user_label->setText(QApplication::translate("RegisterDialog", "\347\224\250\346\210\267\357\274\232", nullptr));
        email_label->setText(QApplication::translate("RegisterDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        pass_label->setText(QApplication::translate("RegisterDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        pass_visible->setText(QString());
        confirm_label->setText(QApplication::translate("RegisterDialog", "\347\241\256\350\256\244\357\274\232", nullptr));
        confirm_visible->setText(QString());
        varify_label->setText(QApplication::translate("RegisterDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        get_code->setText(QApplication::translate("RegisterDialog", "\350\216\267\345\217\226", nullptr));
        sure_btn->setText(QApplication::translate("RegisterDialog", "\347\241\256\350\256\244", nullptr));
        cancel_btn->setText(QApplication::translate("RegisterDialog", "\345\217\226\346\266\210", nullptr));
        label_8->setText(QApplication::translate("RegisterDialog", "\345\256\214\345\226\204\346\202\250\347\232\204\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
        errTip->setText(QString());
        label->setText(QApplication::translate("RegisterDialog", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_2->setText(QApplication::translate("RegisterDialog", "\346\200\247\345\210\253\357\274\232", nullptr));
        manRadioButton->setText(QApplication::translate("RegisterDialog", "\347\224\267", nullptr));
        womanRadbutton->setText(QApplication::translate("RegisterDialog", "\345\245\263", nullptr));
        otherSex->setText(QApplication::translate("RegisterDialog", "\345\205\266\344\273\226", nullptr));
        label_3->setText(QApplication::translate("RegisterDialog", "\345\207\272\347\224\237\346\227\245\346\234\237\357\274\232    \345\271\264", nullptr));
        label_5->setText(QApplication::translate("RegisterDialog", "\346\234\210", nullptr));
        label_6->setText(QApplication::translate("RegisterDialog", "\346\227\245", nullptr));
        label_4->setText(QApplication::translate("RegisterDialog", "\350\272\253\344\273\275\350\257\201\345\217\267", nullptr));
        label_7->setText(QApplication::translate("RegisterDialog", "\346\211\213\346\234\272\345\217\267", nullptr));
        confirmInfo->setText(QApplication::translate("RegisterDialog", "\347\241\256\350\256\244\345\256\214\346\210\220", nullptr));
        tip_lb->setText(QApplication::translate("RegisterDialog", "\346\263\250\345\206\214\346\210\220\345\212\237\357\274\2145 s\345\220\216\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
        tip2_lb->setText(QApplication::translate("RegisterDialog", "\345\217\257\347\202\271\345\207\273\350\277\224\345\233\236\346\214\211\351\222\256\347\233\264\346\216\245\350\277\224\345\233\236\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        return_btn->setText(QApplication::translate("RegisterDialog", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H

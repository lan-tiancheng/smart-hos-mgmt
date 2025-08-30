/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QTextBrowser *msgBrowser;
    QHBoxLayout *horizontalLayout_2;
    QFontComboBox *fontCbx;
    QComboBox *sizeCbx;
    QToolButton *boldTBtn;
    QToolButton *italicTBtn;
    QToolButton *underlineTBtn;
    QToolButton *colorTBtn;
    QToolButton *sendTBtn;
    QToolButton *saveTBtn;
    QToolButton *clearTBtn;
    QTextEdit *msgTextEdit;
    QTableWidget *usrTblWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *sendBtn;
    QSpacerItem *horizontalSpacer_3;
    QLabel *usrNumLbl;
    QSpacerItem *horizontalSpacer;
    QPushButton *exitBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(730, 450);
        Widget->setMinimumSize(QSize(730, 450));
        Widget->setMaximumSize(QSize(730, 450));
        verticalLayout_3 = new QVBoxLayout(Widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        msgBrowser = new QTextBrowser(Widget);
        msgBrowser->setObjectName(QString::fromUtf8("msgBrowser"));
        msgBrowser->setMinimumSize(QSize(533, 241));
        msgBrowser->setMaximumSize(QSize(533, 241));

        verticalLayout->addWidget(msgBrowser);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        fontCbx = new QFontComboBox(Widget);
        fontCbx->setObjectName(QString::fromUtf8("fontCbx"));
        fontCbx->setMinimumSize(QSize(188, 20));

        horizontalLayout_2->addWidget(fontCbx);

        sizeCbx = new QComboBox(Widget);
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->addItem(QString());
        sizeCbx->setObjectName(QString::fromUtf8("sizeCbx"));
        sizeCbx->setMinimumSize(QSize(69, 20));

        horizontalLayout_2->addWidget(sizeCbx);

        boldTBtn = new QToolButton(Widget);
        boldTBtn->setObjectName(QString::fromUtf8("boldTBtn"));
        boldTBtn->setMinimumSize(QSize(33, 32));
        boldTBtn->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/bold.png"), QSize(), QIcon::Selected, QIcon::Off);
        boldTBtn->setIcon(icon);
        boldTBtn->setIconSize(QSize(26, 26));

        horizontalLayout_2->addWidget(boldTBtn);

        italicTBtn = new QToolButton(Widget);
        italicTBtn->setObjectName(QString::fromUtf8("italicTBtn"));
        italicTBtn->setMinimumSize(QSize(33, 32));
        italicTBtn->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/italic.png"), QSize(), QIcon::Normal, QIcon::Off);
        italicTBtn->setIcon(icon1);
        italicTBtn->setIconSize(QSize(26, 26));

        horizontalLayout_2->addWidget(italicTBtn);

        underlineTBtn = new QToolButton(Widget);
        underlineTBtn->setObjectName(QString::fromUtf8("underlineTBtn"));
        underlineTBtn->setMinimumSize(QSize(33, 32));
        underlineTBtn->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/under.png"), QSize(), QIcon::Normal, QIcon::Off);
        underlineTBtn->setIcon(icon2);
        underlineTBtn->setIconSize(QSize(26, 26));

        horizontalLayout_2->addWidget(underlineTBtn);

        colorTBtn = new QToolButton(Widget);
        colorTBtn->setObjectName(QString::fromUtf8("colorTBtn"));
        colorTBtn->setMinimumSize(QSize(33, 32));
        colorTBtn->setMaximumSize(QSize(33, 32));
        colorTBtn->setStyleSheet(QString::fromUtf8(""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        colorTBtn->setIcon(icon3);
        colorTBtn->setIconSize(QSize(22, 22));

        horizontalLayout_2->addWidget(colorTBtn);

        sendTBtn = new QToolButton(Widget);
        sendTBtn->setObjectName(QString::fromUtf8("sendTBtn"));
        sendTBtn->setMinimumSize(QSize(33, 32));
        sendTBtn->setStyleSheet(QString::fromUtf8(""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/send.png"), QSize(), QIcon::Normal, QIcon::Off);
        sendTBtn->setIcon(icon4);
        sendTBtn->setIconSize(QSize(22, 22));

        horizontalLayout_2->addWidget(sendTBtn);

        saveTBtn = new QToolButton(Widget);
        saveTBtn->setObjectName(QString::fromUtf8("saveTBtn"));
        saveTBtn->setMinimumSize(QSize(33, 32));
        saveTBtn->setStyleSheet(QString::fromUtf8(""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveTBtn->setIcon(icon5);
        saveTBtn->setIconSize(QSize(22, 22));

        horizontalLayout_2->addWidget(saveTBtn);

        clearTBtn = new QToolButton(Widget);
        clearTBtn->setObjectName(QString::fromUtf8("clearTBtn"));
        clearTBtn->setMinimumSize(QSize(33, 32));
        clearTBtn->setStyleSheet(QString::fromUtf8(""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearTBtn->setIcon(icon6);
        clearTBtn->setIconSize(QSize(22, 22));

        horizontalLayout_2->addWidget(clearTBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        msgTextEdit = new QTextEdit(Widget);
        msgTextEdit->setObjectName(QString::fromUtf8("msgTextEdit"));
        msgTextEdit->setMinimumSize(QSize(533, 95));
        msgTextEdit->setMaximumSize(QSize(533, 95));

        verticalLayout->addWidget(msgTextEdit);


        horizontalLayout_3->addLayout(verticalLayout);

        usrTblWidget = new QTableWidget(Widget);
        if (usrTblWidget->columnCount() < 2)
            usrTblWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        usrTblWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        usrTblWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        usrTblWidget->setObjectName(QString::fromUtf8("usrTblWidget"));

        horizontalLayout_3->addWidget(usrTblWidget);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        sendBtn = new QPushButton(Widget);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));

        horizontalLayout->addWidget(sendBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        usrNumLbl = new QLabel(Widget);
        usrNumLbl->setObjectName(QString::fromUtf8("usrNumLbl"));

        horizontalLayout->addWidget(usrNumLbl);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        exitBtn = new QPushButton(Widget);
        exitBtn->setObjectName(QString::fromUtf8("exitBtn"));

        horizontalLayout->addWidget(exitBtn);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        sizeCbx->setItemText(0, QApplication::translate("Widget", "8", nullptr));
        sizeCbx->setItemText(1, QApplication::translate("Widget", "9", nullptr));
        sizeCbx->setItemText(2, QApplication::translate("Widget", "10", nullptr));
        sizeCbx->setItemText(3, QApplication::translate("Widget", "11", nullptr));
        sizeCbx->setItemText(4, QApplication::translate("Widget", "12", nullptr));
        sizeCbx->setItemText(5, QApplication::translate("Widget", "13", nullptr));
        sizeCbx->setItemText(6, QApplication::translate("Widget", "14", nullptr));
        sizeCbx->setItemText(7, QApplication::translate("Widget", "15", nullptr));
        sizeCbx->setItemText(8, QApplication::translate("Widget", "16", nullptr));
        sizeCbx->setItemText(9, QApplication::translate("Widget", "17", nullptr));
        sizeCbx->setItemText(10, QApplication::translate("Widget", "18", nullptr));
        sizeCbx->setItemText(11, QApplication::translate("Widget", "19", nullptr));
        sizeCbx->setItemText(12, QApplication::translate("Widget", "20", nullptr));
        sizeCbx->setItemText(13, QApplication::translate("Widget", "21", nullptr));
        sizeCbx->setItemText(14, QApplication::translate("Widget", "22", nullptr));

        boldTBtn->setText(QString());
        italicTBtn->setText(QString());
        underlineTBtn->setText(QString());
        colorTBtn->setText(QString());
        sendTBtn->setText(QString());
        saveTBtn->setText(QString());
        clearTBtn->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = usrTblWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Widget", "\347\224\250\346\210\267\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = usrTblWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Widget", "IP\345\234\260\345\235\200", nullptr));
        sendBtn->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        usrNumLbl->setText(QApplication::translate("Widget", "\345\234\250\347\272\277\347\224\250\346\210\267\357\274\2320\344\272\272", nullptr));
        exitBtn->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H

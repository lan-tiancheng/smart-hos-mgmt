/********************************************************************************
** Form generated from reading UI file 'change.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGE_H
#define UI_CHANGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_change
{
public:
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tabGoods;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEditID;
    QLineEdit *lineEditOwnerID;
    QTextEdit *textEditSummary;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonCommit;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *lineEditName;

    void setupUi(QWidget *change)
    {
        if (change->objectName().isEmpty())
            change->setObjectName(QString::fromUtf8("change"));
        change->resize(369, 442);
        pushButton = new QPushButton(change);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 31, 31));
        tabWidget = new QTabWidget(change);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 30, 371, 421));
        tabGoods = new QWidget();
        tabGoods->setObjectName(QString::fromUtf8("tabGoods"));
        tabGoods->setStyleSheet(QString::fromUtf8("background-color: skyblue;"));
        gridLayout_2 = new QGridLayout(tabGoods);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEditID = new QLineEdit(tabGoods);
        lineEditID->setObjectName(QString::fromUtf8("lineEditID"));
        lineEditID->setMinimumSize(QSize(160, 30));

        gridLayout_2->addWidget(lineEditID, 0, 1, 1, 2);

        lineEditOwnerID = new QLineEdit(tabGoods);
        lineEditOwnerID->setObjectName(QString::fromUtf8("lineEditOwnerID"));
        lineEditOwnerID->setMinimumSize(QSize(160, 30));

        gridLayout_2->addWidget(lineEditOwnerID, 2, 1, 1, 2);

        textEditSummary = new QTextEdit(tabGoods);
        textEditSummary->setObjectName(QString::fromUtf8("textEditSummary"));

        gridLayout_2->addWidget(textEditSummary, 3, 1, 1, 2);

        label_2 = new QLabel(tabGoods);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_2, 3, 0, 1, 1);

        label = new QLabel(tabGoods);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 30));
        label->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(147, 37, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 5, 0, 1, 2);

        pushButtonCommit = new QPushButton(tabGoods);
        pushButtonCommit->setObjectName(QString::fromUtf8("pushButtonCommit"));
        pushButtonCommit->setMinimumSize(QSize(80, 40));
        pushButtonCommit->setMaximumSize(QSize(80, 40));

        gridLayout_2->addWidget(pushButtonCommit, 5, 2, 1, 1);

        label_4 = new QLabel(tabGoods);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        label_3 = new QLabel(tabGoods);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        lineEditName = new QLineEdit(tabGoods);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        lineEditName->setMinimumSize(QSize(160, 30));

        gridLayout_2->addWidget(lineEditName, 1, 1, 1, 2);

        tabWidget->addTab(tabGoods, QString());

        retranslateUi(change);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(change);
    } // setupUi

    void retranslateUi(QWidget *change)
    {
        change->setWindowTitle(QApplication::translate("change", "Form", nullptr));
        pushButton->setText(QApplication::translate("change", "<", nullptr));
        label_2->setText(QApplication::translate("change", "\345\214\273\347\224\237\344\277\241\346\201\257\350\265\204\346\226\231", nullptr));
        label->setText(QApplication::translate("change", "\345\214\273\347\224\237\345\247\223\345\220\215", nullptr));
        pushButtonCommit->setText(QApplication::translate("change", "\347\241\256\350\256\244\344\277\256\346\224\271", nullptr));
        label_4->setText(QApplication::translate("change", "\345\214\273\347\224\237\350\264\246\345\217\267", nullptr));
        label_3->setText(QApplication::translate("change", "\346\211\200\345\261\236\347\247\221\345\256\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGoods), QApplication::translate("change", "\345\235\220\350\257\212\345\256\211\346\216\222\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class change: public Ui_change {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGE_H

/********************************************************************************
** Form generated from reading UI file 'pbd.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PBD_H
#define UI_PBD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pbd
{
public:
    QLabel *label_6;
    QPushButton *pushButton_return;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QTableView *tableView_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QTableView *tableView_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QTableView *tableView_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QTableView *tableView_4;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;

    void setupUi(QWidget *pbd)
    {
        if (pbd->objectName().isEmpty())
            pbd->setObjectName(QString::fromUtf8("pbd"));
        pbd->resize(810, 630);
        pbd->setAutoFillBackground(false);
        pbd->setStyleSheet(QString::fromUtf8(""));
        label_6 = new QLabel(pbd);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(180, 20, 321, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Liberation Sans"));
        font.setPointSize(18);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignCenter);
        pushButton_return = new QPushButton(pbd);
        pushButton_return->setObjectName(QString::fromUtf8("pushButton_return"));
        pushButton_return->setGeometry(QRect(0, 0, 31, 31));
        layoutWidget = new QWidget(pbd);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(100, 110, 341, 381));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(15);
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        tableView = new QTableView(layoutWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout->addWidget(tableView);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        horizontalLayout_2->addWidget(label_5);

        tableView_5 = new QTableView(layoutWidget);
        tableView_5->setObjectName(QString::fromUtf8("tableView_5"));

        horizontalLayout_2->addWidget(tableView_5);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        horizontalLayout_3->addWidget(label_2);

        tableView_2 = new QTableView(layoutWidget);
        tableView_2->setObjectName(QString::fromUtf8("tableView_2"));

        horizontalLayout_3->addWidget(tableView_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        horizontalLayout_4->addWidget(label_3);

        tableView_3 = new QTableView(layoutWidget);
        tableView_3->setObjectName(QString::fromUtf8("tableView_3"));

        horizontalLayout_4->addWidget(tableView_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        horizontalLayout_5->addWidget(label_4);

        tableView_4 = new QTableView(layoutWidget);
        tableView_4->setObjectName(QString::fromUtf8("tableView_4"));

        horizontalLayout_5->addWidget(tableView_4);


        verticalLayout->addLayout(horizontalLayout_5);

        layoutWidget1 = new QWidget(pbd);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(510, 160, 191, 271));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QFont font2;
        font2.setPointSize(14);
        pushButton_2->setFont(font2);

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_4 = new QPushButton(layoutWidget1);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setFont(font2);

        verticalLayout_2->addWidget(pushButton_4);

        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setFont(font2);

        verticalLayout_2->addWidget(pushButton_3);


        retranslateUi(pbd);

        QMetaObject::connectSlotsByName(pbd);
    } // setupUi

    void retranslateUi(QWidget *pbd)
    {
        pbd->setWindowTitle(QApplication::translate("pbd", "Form", nullptr));
        label_6->setText(QApplication::translate("pbd", "\346\202\243\350\200\205\351\242\204\347\272\246\344\277\241\346\201\257", nullptr));
        pushButton_return->setText(QApplication::translate("pbd", "<", nullptr));
        label->setText(QApplication::translate("pbd", "\346\202\243\350\200\205\345\247\223\345\220\215:", nullptr));
        label_5->setText(QApplication::translate("pbd", "\346\202\243\350\200\205\350\264\246\345\217\267:", nullptr));
        label_2->setText(QApplication::translate("pbd", "\351\242\204\347\272\246\346\227\266\351\227\264:", nullptr));
        label_3->setText(QApplication::translate("pbd", "\346\211\200\345\261\236\347\247\221\345\256\244:", nullptr));
        label_4->setText(QApplication::translate("pbd", "\347\224\265\350\257\235:", nullptr));
        pushButton_2->setText(QApplication::translate("pbd", "\350\257\212\346\226\255\347\273\223\346\236\234", nullptr));
        pushButton_4->setText(QApplication::translate("pbd", "\347\225\231\344\270\213\345\214\273\345\230\261", nullptr));
        pushButton_3->setText(QApplication::translate("pbd", "\344\275\217\351\231\242\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pbd: public Ui_pbd {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PBD_H

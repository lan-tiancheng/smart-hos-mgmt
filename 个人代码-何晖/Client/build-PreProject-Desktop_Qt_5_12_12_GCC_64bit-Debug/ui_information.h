/********************************************************************************
** Form generated from reading UI file 'information.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFORMATION_H
#define UI_INFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_information
{
public:
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tabGoods;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLabel *name;
    QLabel *label_2;
    QLabel *label;
    QLabel *department;
    QLabel *intr;
    QPushButton *pushButtonCommit_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *eamil;
    QLabel *label_3;

    void setupUi(QWidget *information)
    {
        if (information->objectName().isEmpty())
            information->setObjectName(QString::fromUtf8("information"));
        information->resize(780, 641);
        pushButton = new QPushButton(information);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 31, 31));
        tabWidget = new QTabWidget(information);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 30, 800, 300));
        tabWidget->setMinimumSize(QSize(800, 300));
        tabWidget->setMaximumSize(QSize(800, 300));
        tabGoods = new QWidget();
        tabGoods->setObjectName(QString::fromUtf8("tabGoods"));
        tabGoods->setStyleSheet(QString::fromUtf8("background-color: skyblue;"));
        gridLayout_2 = new QGridLayout(tabGoods);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(tabGoods);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        name = new QLabel(tabGoods);
        name->setObjectName(QString::fromUtf8("name"));

        gridLayout_2->addWidget(name, 0, 1, 1, 1);

        label_2 = new QLabel(tabGoods);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_2, 3, 0, 1, 1);

        label = new QLabel(tabGoods);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 30));
        label->setMaximumSize(QSize(80, 16777215));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        department = new QLabel(tabGoods);
        department->setObjectName(QString::fromUtf8("department"));

        gridLayout_2->addWidget(department, 1, 1, 1, 1);

        intr = new QLabel(tabGoods);
        intr->setObjectName(QString::fromUtf8("intr"));

        gridLayout_2->addWidget(intr, 3, 1, 1, 1);

        pushButtonCommit_2 = new QPushButton(tabGoods);
        pushButtonCommit_2->setObjectName(QString::fromUtf8("pushButtonCommit_2"));
        pushButtonCommit_2->setMinimumSize(QSize(80, 40));
        pushButtonCommit_2->setMaximumSize(QSize(80, 40));

        gridLayout_2->addWidget(pushButtonCommit_2, 5, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(147, 37, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 5, 0, 1, 2);

        eamil = new QLabel(tabGoods);
        eamil->setObjectName(QString::fromUtf8("eamil"));

        gridLayout_2->addWidget(eamil, 2, 1, 1, 1);

        label_3 = new QLabel(tabGoods);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 30));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        tabWidget->addTab(tabGoods, QString());

        retranslateUi(information);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(information);
    } // setupUi

    void retranslateUi(QWidget *information)
    {
        information->setWindowTitle(QApplication::translate("information", "Form", nullptr));
        pushButton->setText(QApplication::translate("information", "<", nullptr));
        label_4->setText(QApplication::translate("information", "\345\214\273\347\224\237\350\264\246\345\217\267", nullptr));
        name->setText(QApplication::translate("information", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("information", "\345\214\273\347\224\237\344\277\241\346\201\257\350\265\204\346\226\231", nullptr));
        label->setText(QApplication::translate("information", "\345\214\273\347\224\237\345\247\223\345\220\215", nullptr));
        department->setText(QApplication::translate("information", "TextLabel", nullptr));
        intr->setText(QApplication::translate("information", "TextLabel", nullptr));
        pushButtonCommit_2->setText(QApplication::translate("information", "\344\277\256\346\224\271", nullptr));
        eamil->setText(QApplication::translate("information", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("information", "\346\211\200\345\261\236\347\247\221\345\256\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGoods), QApplication::translate("information", "\345\235\220\350\257\212\345\256\211\346\216\222\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class information: public Ui_information {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFORMATION_H

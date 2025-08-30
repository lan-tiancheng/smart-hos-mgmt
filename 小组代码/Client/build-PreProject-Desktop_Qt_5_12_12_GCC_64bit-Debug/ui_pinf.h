/********************************************************************************
** Form generated from reading UI file 'pinf.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PINF_H
#define UI_PINF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pinf
{
public:
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *tabRecordation_2;
    QGridLayout *gridLayout_8;
    QSpacerItem *horizontalSpacerRecordation_2;
    QGridLayout *gridLayoutRecordation_2;
    QPushButton *pushButtonRecordationRefresh_2;
    QTableView *tableViewRecordation_2;
    QWidget *tabUser_2;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacerUser_2;
    QGridLayout *gridLayoutUser_2;
    QPushButton *pushButtonUserRefresh_2;
    QTableView *tableViewUser_2;
    QWidget *tabGoods_2;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacerGoods_2;
    QGridLayout *gridLayoutGoods_2;
    QPushButton *pushButtonGoodsRefresh_2;
    QTableView *tableViewGoods_2;
    QWidget *tabStatistics_2;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonStatisticsRefresh_2;
    QTableView *tableViewStatistics_2;

    void setupUi(QWidget *pinf)
    {
        if (pinf->objectName().isEmpty())
            pinf->setObjectName(QString::fromUtf8("pinf"));
        pinf->resize(1357, 818);
        pushButton = new QPushButton(pinf);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 0, 31, 31));
        tabWidget = new QTabWidget(pinf);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(-3, 30, 1361, 790));
        tabRecordation_2 = new QWidget();
        tabRecordation_2->setObjectName(QString::fromUtf8("tabRecordation_2"));
        gridLayout_8 = new QGridLayout(tabRecordation_2);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        horizontalSpacerRecordation_2 = new QSpacerItem(975, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacerRecordation_2, 0, 0, 1, 1);

        gridLayoutRecordation_2 = new QGridLayout();
        gridLayoutRecordation_2->setObjectName(QString::fromUtf8("gridLayoutRecordation_2"));
        pushButtonRecordationRefresh_2 = new QPushButton(tabRecordation_2);
        pushButtonRecordationRefresh_2->setObjectName(QString::fromUtf8("pushButtonRecordationRefresh_2"));
        pushButtonRecordationRefresh_2->setMinimumSize(QSize(80, 40));

        gridLayoutRecordation_2->addWidget(pushButtonRecordationRefresh_2, 0, 0, 1, 1);


        gridLayout_8->addLayout(gridLayoutRecordation_2, 0, 1, 1, 1);

        tableViewRecordation_2 = new QTableView(tabRecordation_2);
        tableViewRecordation_2->setObjectName(QString::fromUtf8("tableViewRecordation_2"));

        gridLayout_8->addWidget(tableViewRecordation_2, 1, 0, 1, 2);

        tabWidget->addTab(tabRecordation_2, QString());
        tabUser_2 = new QWidget();
        tabUser_2->setObjectName(QString::fromUtf8("tabUser_2"));
        gridLayout_3 = new QGridLayout(tabUser_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalSpacerUser_2 = new QSpacerItem(975, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacerUser_2, 0, 0, 1, 1);

        gridLayoutUser_2 = new QGridLayout();
        gridLayoutUser_2->setObjectName(QString::fromUtf8("gridLayoutUser_2"));
        pushButtonUserRefresh_2 = new QPushButton(tabUser_2);
        pushButtonUserRefresh_2->setObjectName(QString::fromUtf8("pushButtonUserRefresh_2"));
        pushButtonUserRefresh_2->setMinimumSize(QSize(80, 40));

        gridLayoutUser_2->addWidget(pushButtonUserRefresh_2, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayoutUser_2, 0, 1, 1, 1);

        tableViewUser_2 = new QTableView(tabUser_2);
        tableViewUser_2->setObjectName(QString::fromUtf8("tableViewUser_2"));

        gridLayout_3->addWidget(tableViewUser_2, 1, 0, 1, 2);

        tabWidget->addTab(tabUser_2, QString());
        tabGoods_2 = new QWidget();
        tabGoods_2->setObjectName(QString::fromUtf8("tabGoods_2"));
        gridLayout_6 = new QGridLayout(tabGoods_2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalSpacerGoods_2 = new QSpacerItem(975, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacerGoods_2, 0, 0, 1, 1);

        gridLayoutGoods_2 = new QGridLayout();
        gridLayoutGoods_2->setObjectName(QString::fromUtf8("gridLayoutGoods_2"));
        pushButtonGoodsRefresh_2 = new QPushButton(tabGoods_2);
        pushButtonGoodsRefresh_2->setObjectName(QString::fromUtf8("pushButtonGoodsRefresh_2"));
        pushButtonGoodsRefresh_2->setMinimumSize(QSize(80, 40));

        gridLayoutGoods_2->addWidget(pushButtonGoodsRefresh_2, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayoutGoods_2, 0, 1, 1, 1);

        tableViewGoods_2 = new QTableView(tabGoods_2);
        tableViewGoods_2->setObjectName(QString::fromUtf8("tableViewGoods_2"));

        gridLayout_6->addWidget(tableViewGoods_2, 1, 0, 1, 2);

        tabWidget->addTab(tabGoods_2, QString());
        tabStatistics_2 = new QWidget();
        tabStatistics_2->setObjectName(QString::fromUtf8("tabStatistics_2"));
        gridLayout_4 = new QGridLayout(tabStatistics_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(1147, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonStatisticsRefresh_2 = new QPushButton(tabStatistics_2);
        pushButtonStatisticsRefresh_2->setObjectName(QString::fromUtf8("pushButtonStatisticsRefresh_2"));
        pushButtonStatisticsRefresh_2->setMinimumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(pushButtonStatisticsRefresh_2);


        gridLayout_4->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        tableViewStatistics_2 = new QTableView(tabStatistics_2);
        tableViewStatistics_2->setObjectName(QString::fromUtf8("tableViewStatistics_2"));

        gridLayout_4->addWidget(tableViewStatistics_2, 1, 0, 1, 2);

        tabWidget->addTab(tabStatistics_2, QString());

        retranslateUi(pinf);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(pinf);
    } // setupUi

    void retranslateUi(QWidget *pinf)
    {
        pinf->setWindowTitle(QApplication::translate("pinf", "Form", nullptr));
        pushButton->setText(QApplication::translate("pinf", "<", nullptr));
        pushButtonRecordationRefresh_2->setText(QApplication::translate("pinf", "\345\210\267\346\226\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabRecordation_2), QApplication::translate("pinf", "\351\242\204\347\272\246\350\256\260\345\275\225", nullptr));
        pushButtonUserRefresh_2->setText(QApplication::translate("pinf", "\345\210\267\346\226\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabUser_2), QApplication::translate("pinf", "\350\257\212\346\226\255\350\256\260\345\275\225", nullptr));
        pushButtonGoodsRefresh_2->setText(QApplication::translate("pinf", "\345\210\267\346\226\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabGoods_2), QApplication::translate("pinf", "\345\244\204\346\226\271\350\256\260\345\275\225", nullptr));
        pushButtonStatisticsRefresh_2->setText(QApplication::translate("pinf", "\345\210\267\346\226\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabStatistics_2), QApplication::translate("pinf", "\344\275\217\351\231\242\350\256\260\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pinf: public Ui_pinf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PINF_H

/********************************************************************************
** Form generated from reading UI file 'hospital.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOSPITAL_H
#define UI_HOSPITAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hospital
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *buttonLayout;
    QPushButton *saveButton;
    QPushButton *closeButton;
    QPushButton *returnButton;

    void setupUi(QWidget *Hospital)
    {
        if (Hospital->objectName().isEmpty())
            Hospital->setObjectName(QString::fromUtf8("Hospital"));
        Hospital->resize(600, 400);
        verticalLayout = new QVBoxLayout(Hospital);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableWidget = new QTableWidget(Hospital);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
        tableWidget->setRowCount(1);
        tableWidget->setColumnCount(5);

        verticalLayout->addWidget(tableWidget);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        saveButton = new QPushButton(Hospital);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        buttonLayout->addWidget(saveButton);

        closeButton = new QPushButton(Hospital);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        buttonLayout->addWidget(closeButton);

        returnButton = new QPushButton(Hospital);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));

        buttonLayout->addWidget(returnButton);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(Hospital);

        QMetaObject::connectSlotsByName(Hospital);
    } // setupUi

    void retranslateUi(QWidget *Hospital)
    {
        Hospital->setWindowTitle(QApplication::translate("Hospital", "Hospital", nullptr));
        tableWidget->setProperty("horizontalHeaderLabels", QVariant(QStringList()
            << QApplication::translate("Hospital", "\346\202\243\350\200\205\345\247\223\345\220\215", nullptr)
            << QApplication::translate("Hospital", "\347\227\205\346\210\277\345\217\267", nullptr)
            << QApplication::translate("Hospital", "\347\227\205\345\272\212\345\217\267", nullptr)
            << QApplication::translate("Hospital", "\345\214\273\347\224\237\345\247\223\345\220\215", nullptr)
            << QApplication::translate("Hospital", "\345\205\245\351\231\242\346\227\245\346\234\237", nullptr)));
        saveButton->setText(QApplication::translate("Hospital", "\344\277\235\345\255\230", nullptr));
        closeButton->setStyleSheet(QApplication::translate("Hospital", "QPushButton { border: none; color: red; font-size: 20px; }", nullptr));
        closeButton->setText(QApplication::translate("Hospital", "\303\227", nullptr));
        returnButton->setText(QApplication::translate("Hospital", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Hospital: public Ui_Hospital {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOSPITAL_H

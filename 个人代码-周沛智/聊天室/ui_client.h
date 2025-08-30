/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QLabel *label;
    QProgressBar *progressBar;
    QLabel *msgLable;
    QPushButton *cancleBtn;
    QPushButton *closeBtn;

    void setupUi(QDialog *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(400, 190);
        label = new QLabel(Client);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 40, 61, 21));
        progressBar = new QProgressBar(Client);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(120, 40, 271, 23));
        progressBar->setValue(0);
        msgLable = new QLabel(Client);
        msgLable->setObjectName(QString::fromUtf8("msgLable"));
        msgLable->setGeometry(QRect(40, 70, 331, 71));
        cancleBtn = new QPushButton(Client);
        cancleBtn->setObjectName(QString::fromUtf8("cancleBtn"));
        cancleBtn->setGeometry(QRect(80, 150, 75, 23));
        closeBtn = new QPushButton(Client);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setGeometry(QRect(240, 150, 75, 23));

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QDialog *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Dialog", nullptr));
        label->setText(QApplication::translate("Client", "<html><head/><body><p><span style=\" font-size:12pt;\">\345\267\262\345\256\214\346\210\220</span></p></body></html>", nullptr));
        msgLable->setText(QApplication::translate("Client", "\347\255\211\345\276\205\346\216\245\346\224\266\346\226\207\344\273\266\302\267\302\267\302\267", nullptr));
        cancleBtn->setText(QApplication::translate("Client", "\345\217\226\346\266\210", nullptr));
        closeBtn->setText(QApplication::translate("Client", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H

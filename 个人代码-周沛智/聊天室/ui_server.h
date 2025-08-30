/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_server
{
public:
    QLabel *label;
    QLabel *messageLbl;
    QProgressBar *progressBar;
    QPushButton *sendBtn;
    QPushButton *openBtn;
    QPushButton *colseBtn;

    void setupUi(QDialog *server)
    {
        if (server->objectName().isEmpty())
            server->setObjectName(QString::fromUtf8("server"));
        server->resize(400, 207);
        label = new QLabel(server);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 121, 21));
        messageLbl = new QLabel(server);
        messageLbl->setObjectName(QString::fromUtf8("messageLbl"));
        messageLbl->setGeometry(QRect(40, 110, 331, 51));
        progressBar = new QProgressBar(server);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(120, 80, 261, 23));
        progressBar->setValue(0);
        sendBtn = new QPushButton(server);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));
        sendBtn->setGeometry(QRect(40, 80, 75, 23));
        openBtn = new QPushButton(server);
        openBtn->setObjectName(QString::fromUtf8("openBtn"));
        openBtn->setGeometry(QRect(180, 30, 75, 23));
        colseBtn = new QPushButton(server);
        colseBtn->setObjectName(QString::fromUtf8("colseBtn"));
        colseBtn->setGeometry(QRect(300, 170, 75, 23));

        retranslateUi(server);

        QMetaObject::connectSlotsByName(server);
    } // setupUi

    void retranslateUi(QDialog *server)
    {
        server->setWindowTitle(QApplication::translate("server", "Dialog", nullptr));
        label->setText(QApplication::translate("server", "<html><head/><body><p><span style=\" font-size:12pt;\">\351\200\211\346\213\251\346\226\207\344\273\266/\346\226\207\344\273\266\345\244\271</span></p></body></html>", nullptr));
        messageLbl->setText(QApplication::translate("server", "\350\257\267\351\200\211\346\213\251\350\246\201\345\217\221\351\200\201\347\232\204\346\226\207\344\273\266\357\274\201", nullptr));
        sendBtn->setText(QApplication::translate("server", "\345\217\221\351\200\201", nullptr));
        openBtn->setText(QApplication::translate("server", "\346\211\223\345\274\200...", nullptr));
        colseBtn->setText(QApplication::translate("server", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class server: public Ui_server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H

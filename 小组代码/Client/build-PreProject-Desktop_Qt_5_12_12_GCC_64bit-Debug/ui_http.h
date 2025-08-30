/********************************************************************************
** Form generated from reading UI file 'http.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTTP_H
#define UI_HTTP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_http
{
public:

    void setupUi(QWidget *http)
    {
        if (http->objectName().isEmpty())
            http->setObjectName(QString::fromUtf8("http"));
        http->resize(400, 300);

        retranslateUi(http);

        QMetaObject::connectSlotsByName(http);
    } // setupUi

    void retranslateUi(QWidget *http)
    {
        http->setWindowTitle(QApplication::translate("http", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class http: public Ui_http {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTTP_H

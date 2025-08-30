/********************************************************************************
** Form generated from reading UI file 'bookwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKWINDOW_H
#define UI_BOOKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BookWindow
{
public:
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;

    void setupUi(QWidget *BookWindow)
    {
        if (BookWindow->objectName().isEmpty())
            BookWindow->setObjectName(QString::fromUtf8("BookWindow"));
        BookWindow->resize(800, 600);
        listWidget = new QListWidget(BookWindow);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 191, 601));
        listWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(114, 159, 207);"));
        stackedWidget = new QStackedWidget(BookWindow);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(190, 0, 521, 601));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        retranslateUi(BookWindow);

        QMetaObject::connectSlotsByName(BookWindow);
    } // setupUi

    void retranslateUi(QWidget *BookWindow)
    {
        BookWindow->setWindowTitle(QApplication::translate("BookWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookWindow: public Ui_BookWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'hmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HMAINWINDOW_H
#define UI_HMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hMainWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *hMainWindow)
    {
        if (hMainWindow->objectName().isEmpty())
            hMainWindow->setObjectName(QString::fromUtf8("hMainWindow"));
        hMainWindow->resize(500, 800);
        hMainWindow->setMinimumSize(QSize(500, 800));
        hMainWindow->setMaximumSize(QSize(500, 800));
        centralwidget = new QWidget(hMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        hMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(hMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 28));
        hMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(hMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        hMainWindow->setStatusBar(statusbar);

        retranslateUi(hMainWindow);

        QMetaObject::connectSlotsByName(hMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *hMainWindow)
    {
        hMainWindow->setWindowTitle(QApplication::translate("hMainWindow", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hMainWindow: public Ui_hMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HMAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'guidemainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUIDEMAINWINDOW_H
#define UI_GUIDEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guideMainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label2;
    QLineEdit *lineEdit2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QPushButton *pushButton2;
    QTextBrowser *textBrowser2;
    QPushButton *pushButton3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *guideMainWindow)
    {
        if (guideMainWindow->objectName().isEmpty())
            guideMainWindow->setObjectName(QString::fromUtf8("guideMainWindow"));
        guideMainWindow->setEnabled(true);
        guideMainWindow->resize(1200, 600);
        guideMainWindow->setMinimumSize(QSize(1200, 600));
        guideMainWindow->setMaximumSize(QSize(1200, 600));
        centralwidget = new QWidget(guideMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(850, 40, 31, 31));
        label2 = new QLabel(centralwidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(850, 100, 31, 16));
        lineEdit2 = new QLineEdit(centralwidget);
        lineEdit2->setObjectName(QString::fromUtf8("lineEdit2"));
        lineEdit2->setGeometry(QRect(910, 100, 91, 20));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(910, 50, 91, 20));
        lineEdit->setContextMenuPolicy(Qt::DefaultContextMenu);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(830, 150, 75, 23));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(910, 150, 256, 201));
        pushButton2 = new QPushButton(centralwidget);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        pushButton2->setGeometry(QRect(830, 390, 75, 23));
        textBrowser2 = new QTextBrowser(centralwidget);
        textBrowser2->setObjectName(QString::fromUtf8("textBrowser2"));
        textBrowser2->setGeometry(QRect(910, 390, 256, 121));
        pushButton3 = new QPushButton(centralwidget);
        pushButton3->setObjectName(QString::fromUtf8("pushButton3"));
        pushButton3->setGeometry(QRect(830, 530, 75, 23));
        guideMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(guideMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        guideMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(guideMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        guideMainWindow->setStatusBar(statusbar);

        retranslateUi(guideMainWindow);

        QMetaObject::connectSlotsByName(guideMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *guideMainWindow)
    {
        guideMainWindow->setWindowTitle(QApplication::translate("guideMainWindow", "Guide", nullptr));
        label->setText(QApplication::translate("guideMainWindow", "\350\265\267\347\202\271", nullptr));
        label2->setText(QApplication::translate("guideMainWindow", "\347\273\210\347\202\271", nullptr));
        pushButton->setText(QApplication::translate("guideMainWindow", "\345\217\257\351\200\211\350\267\257\345\276\204", nullptr));
        pushButton2->setText(QApplication::translate("guideMainWindow", "\346\234\200\347\237\255\350\267\257\345\276\204", nullptr));
        pushButton3->setText(QApplication::translate("guideMainWindow", "\345\214\273\351\231\242\347\256\200\344\273\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class guideMainWindow: public Ui_guideMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUIDEMAINWINDOW_H

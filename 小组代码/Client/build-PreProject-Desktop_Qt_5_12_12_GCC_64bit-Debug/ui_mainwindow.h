/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
<<<<<<< HEAD
        MainWindow->resize(500, 800);
        MainWindow->setMinimumSize(QSize(500, 800));
        MainWindow->setMaximumSize(QSize(500, 800));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 500, 28));
=======
        MainWindow->resize(1010, 610);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1000, 400));
        stackedWidget->setMinimumSize(QSize(1000, 400));
        stackedWidget->setMaximumSize(QSize(1000, 400));
        page_0 = new QWidget();
        page_0->setObjectName(QString::fromUtf8("page_0"));
        label_3 = new QLabel(page_0);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 10, 351, 151));
        return_1 = new QPushButton(page_0);
        return_1->setObjectName(QString::fromUtf8("return_1"));
        return_1->setGeometry(QRect(0, 20, 31, 31));
        stackedWidget->addWidget(page_0);
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        label_4 = new QLabel(page_1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(320, -110, 331, 271));
        QFont font;
        font.setPointSize(27);
        label_4->setFont(font);
        return_2 = new QPushButton(page_1);
        return_2->setObjectName(QString::fromUtf8("return_2"));
        return_2->setGeometry(QRect(0, 20, 31, 31));
        pushButton = new QPushButton(page_1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 160, 101, 61));
        pushButton_2 = new QPushButton(page_1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(40, 260, 101, 61));
        pushButton_3 = new QPushButton(page_1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(40, 370, 101, 61));
        stackedWidget_2 = new QStackedWidget(page_1);
        stackedWidget_2->setObjectName(QString::fromUtf8("stackedWidget_2"));
        stackedWidget_2->setGeometry(QRect(150, 50, 651, 491));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label_7 = new QLabel(page);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(260, 70, 81, 51));
        QFont font1;
        font1.setPointSize(25);
        label_7->setFont(font1);
        checkBox = new QCheckBox(page);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(310, 320, 92, 23));
        QFont font2;
        font2.setPointSize(16);
        checkBox->setFont(font2);
        label_15 = new QLabel(page);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(150, 200, 61, 31));
        label_15->setFont(font2);
        label_16 = new QLabel(page);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(220, 200, 51, 31));
        label_16->setFont(font2);
        label_17 = new QLabel(page);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(280, 200, 61, 31));
        label_17->setFont(font2);
        label_time = new QLabel(page);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(140, 240, 321, 51));
        QFont font3;
        font3.setPointSize(20);
        label_time->setFont(font3);
        label_20 = new QLabel(page);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(340, 200, 67, 31));
        label_20->setFont(font2);
        label_21 = new QLabel(page);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(390, 200, 67, 31));
        label_21->setFont(font2);
        stackedWidget_2->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        label_8 = new QLabel(page_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(200, 10, 181, 31));
        label_8->setFont(font2);
        pushButton_4 = new QPushButton(page_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(420, 460, 89, 25));
        pushButton_5 = new QPushButton(page_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(310, 460, 89, 25));
        label_13 = new QLabel(page_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(70, 250, 60, 23));
        textEdit = new QTextEdit(page_3);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(70, 280, 449, 170));
        layoutWidget = new QWidget(page_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(400, 410, 113, 25));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        labelTitle = new QLabel(layoutWidget);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));

        horizontalLayout_9->addWidget(labelTitle);

        labelCurrentNum = new QLabel(layoutWidget);
        labelCurrentNum->setObjectName(QString::fromUtf8("labelCurrentNum"));

        horizontalLayout_9->addWidget(labelCurrentNum);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_9->addWidget(label_10);

        labelMaxNum = new QLabel(layoutWidget);
        labelMaxNum->setObjectName(QString::fromUtf8("labelMaxNum"));

        horizontalLayout_9->addWidget(labelMaxNum);

        layoutWidget1 = new QWidget(page_3);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(70, 50, 434, 201));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_18 = new QLabel(layoutWidget1);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_11->addWidget(label_18);

        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_11->addWidget(lineEdit);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_19 = new QLabel(layoutWidget1);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_14->addWidget(label_19);

        lineEdit_3 = new QLineEdit(layoutWidget1);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_14->addWidget(lineEdit_3);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_14 = new QLabel(layoutWidget1);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_6->addWidget(label_14);

        lineEdit_2 = new QLineEdit(layoutWidget1);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_6->addWidget(lineEdit_2);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_11 = new QLabel(layoutWidget1);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_7->addWidget(label_11);

        comboBox = new QComboBox(layoutWidget1);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_7->addWidget(comboBox);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_8->addWidget(label_12);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        dateBegin = new QDateTimeEdit(layoutWidget1);
        dateBegin->setObjectName(QString::fromUtf8("dateBegin"));
        dateBegin->setMaximumDateTime(QDateTime(QDate(2024, 12, 31), QTime(23, 59, 59)));
        dateBegin->setMinimumDateTime(QDateTime(QDate(2024, 8, 19), QTime(0, 0, 0)));

        horizontalLayout_10->addWidget(dateBegin);

        dateEnd = new QDateTimeEdit(layoutWidget1);
        dateEnd->setObjectName(QString::fromUtf8("dateEnd"));
        dateEnd->setMaximumDateTime(QDateTime(QDate(2024, 12, 31), QTime(23, 59, 59)));
        dateEnd->setMinimumDateTime(QDateTime(QDate(2024, 8, 19), QTime(8, 0, 0)));

        horizontalLayout_10->addWidget(dateEnd);


        horizontalLayout_8->addLayout(horizontalLayout_10);


        verticalLayout_4->addLayout(horizontalLayout_8);

        stackedWidget_2->addWidget(page_3);
        label_13->raise();
        textEdit->raise();
        label_8->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        pushButton_4->raise();
        pushButton_5->raise();
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        label_9 = new QLabel(page_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(270, 40, 61, 41));
        QFont font4;
        font4.setPointSize(18);
        label_9->setFont(font4);
        tableWidget = new QTableWidget(page_4);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 3)
            tableWidget->setRowCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget->setItem(0, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget->setItem(0, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget->setItem(0, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget->setItem(0, 3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget->setItem(0, 4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tableWidget->setItem(0, 5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(1, 3, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(1, 4, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem20);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 90, 621, 361));
        checkBox_ = new QCheckBox(page_4);
        checkBox_->setObjectName(QString::fromUtf8("checkBox_"));
        checkBox_->setGeometry(QRect(530, 150, 92, 23));
        checkBox_1 = new QCheckBox(page_4);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setGeometry(QRect(530, 120, 92, 23));
        stackedWidget_2->addWidget(page_4);
        stackedWidget->addWidget(page_1);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        return_3 = new QPushButton(page_2);
        return_3->setObjectName(QString::fromUtf8("return_3"));
        return_3->setGeometry(QRect(0, 20, 31, 31));
        label_6 = new QLabel(page_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(270, 150, 171, 111));
        stackedWidget->addWidget(page_2);
        page_last = new QWidget();
        page_last->setObjectName(QString::fromUtf8("page_last"));
        layoutWidget2 = new QWidget(page_last);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 110, 664, 101));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(120, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(layoutWidget2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);

        verticalLayout->addWidget(label);

        PI = new QPushButton(layoutWidget2);
        PI->setObjectName(QString::fromUtf8("PI"));

        verticalLayout->addWidget(PI);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(120, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2, 0, Qt::AlignHCenter);

        WA = new QPushButton(layoutWidget2);
        WA->setObjectName(QString::fromUtf8("WA"));

        verticalLayout_2->addWidget(WA);


        horizontalLayout_2->addLayout(verticalLayout_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(120, 18, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_3->addWidget(label_5);

        INF = new QPushButton(layoutWidget2);
        INF->setObjectName(QString::fromUtf8("INF"));

        verticalLayout_3->addWidget(INF);


        horizontalLayout_4->addLayout(verticalLayout_3);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        stackedWidget->addWidget(page_last);
        layoutWidget3 = new QWidget(centralwidget);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(0, 0, 2, 2));
        horizontalLayout_12 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1010, 22));
>>>>>>> 9e1acf7f4e940ddfee8d6a95eb27ca3d167d77c9
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

<<<<<<< HEAD
=======
        stackedWidget->setCurrentIndex(3);
        stackedWidget_2->setCurrentIndex(0);


>>>>>>> 9e1acf7f4e940ddfee8d6a95eb27ca3d167d77c9
        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

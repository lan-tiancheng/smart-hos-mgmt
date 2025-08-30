#ifndef MYINFOWINDOW_H
#define MYINFOWINDOW_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QTableView;
class QStandardItemModel;

class MyInfoWindow : public QWidget {
    Q_OBJECT

public:
    MyInfoWindow(QWidget *parent = nullptr);

private slots:
    void showBookingWindow();
    void showMyInfoWindow();

private:
    void initializeTable();

    QTableView *infoTableView;
    QStandardItemModel *infoModel;
    QPushButton *bookingButton;
    QPushButton *myInfoButton;
};

#endif // MYINFOWINDOW_H

#ifndef BOOKINGWINDOW_H
#define BOOKINGWINDOW_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QStackedWidget;
class QTableView;
class QStandardItemModel;

class BookingWindow : public QWidget {
    Q_OBJECT

public:
    BookingWindow(QWidget *parent = nullptr);

private slots:
    void showDepartmentWidget();  // Show department selection
    void showMyInfoWidget();  // Show personal information

private:
    QStackedWidget *stackedWidget;
    QWidget *departmentWidget;
    QWidget *myInfoWidget;
    QVBoxLayout *departmentLayout;
    QTableView *appointmentTableView;
    QStandardItemModel *appointmentModel;
    QPushButton *departmentButtons[5];
    QPushButton *bookingButton;
    QPushButton *myInfoButton;
};

#endif // BOOKINGWINDOW_H

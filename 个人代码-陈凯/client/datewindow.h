#ifndef DATEWINDOW_H
#define DATEWINDOW_H

#include <QWidget>

class BookingWindow;

class DateWindow : public QWidget {
    Q_OBJECT

public:
    DateWindow();

private:
    BookingWindow *bookingWindow;
};

#endif // DATEWINDOW_H

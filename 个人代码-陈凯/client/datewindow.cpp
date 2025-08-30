#include "datewindow.h"
#include "bookingwindow.h"

DateWindow::DateWindow() {
    resize(600, 400);

    // Initialize and show BookingWindow
    bookingWindow = new BookingWindow(this);
    bookingWindow->show();

    // Optionally, you can hide or close DateWindow if it's no longer needed
    // close(); // Uncomment if you want to close DateWindow
}

#ifndef PERSONALINFOWINDOW_H
#define PERSONALINFOWINDOW_H

#include <QWidget>

namespace Ui {
class PersonalInfoWindow;
}

class PersonalInfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalInfoWindow(QWidget *parent = nullptr);
    ~PersonalInfoWindow();

private:
    Ui::PersonalInfoWindow *ui;
};

#endif // PERSONALINFOWINDOW_H

#ifndef PMAINWINDOWHOME_H
#define PMAINWINDOWHOME_H

#include <QWidget>

namespace Ui {
class PMainWindowHome;
}

class PMainWindowHome : public QWidget
{
    Q_OBJECT

public:
    explicit PMainWindowHome(QWidget *parent = nullptr);
    ~PMainWindowHome();

private:
    Ui::PMainWindowHome *ui;
};

#endif // PMAINWINDOWHOME_H

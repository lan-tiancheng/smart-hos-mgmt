#ifndef SOUNDREC_H
#define SOUNDREC_H

#include <QWidget>

namespace Ui {
class soundrec;
}

class soundrec : public QWidget
{
    Q_OBJECT

public:
    explicit soundrec(QWidget *parent = nullptr);
    ~soundrec();

private:
    Ui::soundrec *ui;
};

#endif // SOUNDREC_H

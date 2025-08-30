#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QWidget>

namespace Ui {
class httprequest;
}

class httprequest : public QWidget
{
    Q_OBJECT

public:
    explicit httprequest(QWidget *parent = nullptr);
    ~httprequest();

private:
    Ui::httprequest *ui;
};

#endif // HTTPREQUEST_H

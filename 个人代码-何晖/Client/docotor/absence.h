#ifndef ABSENCE_H
#define ABSENCE_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Absence; }
QT_END_NAMESPACE

class Absence : public QDialog
{
    Q_OBJECT

public:
    explicit Absence(QWidget *parent = nullptr);
    ~Absence();

private slots:
    void on_okButton_clicked();

private:
    Ui::Absence *ui;
};

#endif // ABSENCE_H

#ifndef INCHARTX_H
#define INCHARTX_H

#include <QMainWindow>
#include<QtCharts>
#include<QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class InChartX; }
QT_END_NAMESPACE

class InChartX : public QMainWindow
{
    Q_OBJECT

public:
    InChartX(QWidget *parent = nullptr);
    ~InChartX();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::InChartX *ui;
};
#endif // INCHARTX_H

#include "inchartx.h"
#include "ui_inchartx.h"

InChartX::InChartX(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InChartX)
{
    ui->setupUi(this);
    QChart *chart = new QChart();
    chart->setTitle("心率/血压表");
    chart->createDefaultAxes();


    ui->widget->setChart(chart);
    ui->widget->setRenderHint(QPainter::Antialiasing);
}


InChartX::~InChartX()
{
    delete ui;
}


void InChartX::on_pushButton_clicked()
{
    QString input = ui->lineEdit->text();
    QStringList values = input.split(","); // 假设输入是逗号分隔的数字
    QString date = ui->lineEdit_2->text();
    QLineSeries *series = new QLineSeries();

    for (int i = 0; i < values.size(); ++i) {
        bool ok;
        double val = values[i].toDouble(&ok);
        if (ok) {
            series->append(i, val); // 假设x轴是索引
        }
    }
    QChart *chart = ui->widget->chart();
    chart->removeAllSeries(); // 清除旧的数据
    chart->addSeries(series);
    QLegend *mlegend = chart->legend();
    series->setName(date+"及之后心率值(次/分)");
    series->setColor(QColor(255,0,0));
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, values.size());
}


void InChartX::on_pushButton_3_clicked()
{
    QString input1 = ui->lineEdit_3->text();
    QStringList values1 = input1.split(",");
    QString date = ui->lineEdit_2->text();
    QLineSeries *series1 = new QLineSeries();


    for (int i = 0; i < values1.size(); ++i) {
        bool ok;
        double val = values1[i].toDouble(&ok);
        if (ok) {
            series1->append(i, val); // 假设x轴是索引
        }
    }
    QChart *chart = ui->widget->chart();
    chart->removeAllSeries(); // 清除旧的数据
    chart->addSeries(series1);
    QLegend *mlegend = chart->legend();
    series1->setName(date+"及之后血压值(毫米汞柱)");
    series1->setColor(QColor(0,225,225));
    chart->createDefaultAxes();
    chart->axisX()->setRange(0, values1.size());
}


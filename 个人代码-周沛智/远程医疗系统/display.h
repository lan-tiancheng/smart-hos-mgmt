#ifndef DISPLAY_H
#define DISPLAY_H

#include <QDialog>
#include "circularbuf.h"
#include <QFile>
#include <QDebug>
#include "wavescene.h"
#include <QTimer>

namespace Ui {
class Display;
}

class Display : public QDialog
{
    Q_OBJECT
    
public:
    explicit Display(QWidget *parent = 0);
    ~Display();

    void updateData();
    void readData(QString file_name,int which);
    void drawWave();

    void refresh();
    void setIndex(QString string);
    
private:
    Ui::Display *ui;
    QString index;

    QTimer *displayTimer;

    WaveScene *myscene;
    WaveScene *myscene2;
    WaveScene *myscene3;
    WaveScene *myscene4;
    WaveScene *myscene5;
    WaveScene *myscene6;

    CircularBuf* comboAdapter(int comIndex);

    CircularBuf *ecg_data_I;
    CircularBuf *ecg_data_II;
    CircularBuf *ecg_data_III;
    CircularBuf *ecg_data_AVL;
    CircularBuf *ecg_data_AVR;
    CircularBuf *ecg_data_AVF;
    CircularBuf *ecg_data_V1;
    CircularBuf *ecg_data_V2;
    CircularBuf *ecg_data_V3;
    CircularBuf *ecg_data_V4;
    CircularBuf *ecg_data_V5;
    CircularBuf *ecg_data_V6;

private slots:
   void draw();
};

#endif // DISPLAY_H

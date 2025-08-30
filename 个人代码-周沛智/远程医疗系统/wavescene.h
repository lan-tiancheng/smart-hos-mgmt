#ifndef WAVESCENE_H
#define WAVESCENE_H

#include <QGraphicsScene>
#include "circularbuf.h"

class WaveScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit WaveScene(QObject *parent = 0);
    WaveScene(qreal width, qreal height, QObject * parent = 0);

    void setScope(qreal scopeX, qreal scopeY);
    void removeWave();
    void removeScale();
    void createScale(int num_x,int num_y);

private:
    QPen m_scaleLinePen;
    QPen m_waveDataPen;

    QList<QGraphicsItem*> m_waveList;
    QList<QGraphicsItem*> m_scaleLinesList;
    int m_numScaleX;//横向的刻度数
    int m_numScaleY;//纵向的刻度数

    int count;
    QPointF p1;
    QPointF p2;

    void setDefaultScaleLinePen();
    void setDefaultWaveDataPen();
    
signals:
    
public slots:
    void drawing(CircularBuf *ecg,int times,float scale);
    
};

#endif // WAVESCENE_H

#include "wavescene.h"

WaveScene::WaveScene(QObject *parent) :
    QGraphicsScene(parent)
{
    this->setBackgroundBrush(Qt::black);
    setDefaultScaleLinePen();
    setDefaultWaveDataPen();
    count=0;
}
WaveScene::WaveScene(qreal width, qreal height, QObject * parent) :
        QGraphicsScene(0, 0, width, height, parent)
{
    this->setBackgroundBrush(Qt::black);
    setDefaultScaleLinePen();
    setDefaultWaveDataPen();
    count=0;
}
/** 设置默认的刻度线画笔 */
void WaveScene::setDefaultScaleLinePen() {
        m_scaleLinePen.setColor(Qt::red);
        m_scaleLinePen.setStyle(Qt::DashLine);
        m_scaleLinePen.setWidthF(1);
}
/** 设置默认波形画笔 */
void WaveScene::setDefaultWaveDataPen() {
        m_waveDataPen.setColor(Qt::green);
        m_waveDataPen.setStyle(Qt::SolidLine);
        m_waveDataPen.setWidthF(1);
}

/** 移除全部的波形 */
void WaveScene::removeWave() {
        if (m_waveList.isEmpty())
                return;
        foreach(QGraphicsItem *item, m_waveList)
                {
                        this->removeItem(item);
                }
        m_waveList.clear();
}
/** 移除全部的刻度线 */
void WaveScene::removeScale() {
        if (m_scaleLinesList.isEmpty())
                return;
        foreach(QGraphicsItem *item, m_scaleLinesList)
                {
                        this->removeItem(item);
                }
        m_scaleLinesList.clear();
}
/** 画刻度线，并指定横向和纵向的栅格数 */
void WaveScene::createScale(int num_x, int num_y) {

        m_numScaleX = num_x;
        m_numScaleY = num_y;
        QRectF rectf = this->sceneRect();
        QPointF p1;
        QPointF p2;

        //绘制横向刻度线
        for (int i = 1; i < num_x; i++) {
                p1.setX(rectf.x());
                p1.setY(rectf.height() / num_x * i);
                p2.setX(rectf.width());
                p2.setY(rectf.height() / num_x * i);
                m_scaleLinesList.push_back((QGraphicsItem*) this->addLine(
                                QLineF(p1, p2), m_scaleLinePen));
        }
        //绘制纵向刻度线
        for (int i = 1; i < num_y; i++) {
                p1.setX(rectf.width() / num_y * i);
                p1.setY(rectf.y());
                p2.setX(rectf.width() / num_y * i);
                p2.setY(rectf.height());
                m_scaleLinesList.push_back((QGraphicsItem*) this->addLine(
                                QLineF(p1, p2), m_scaleLinePen));
        }
}

/** 绘制波形 */
void WaveScene::drawing(CircularBuf *ecg,int speed,float scale)
{
    QRectF rectf = this->sceneRect();
    //int sum = ecg->getElementCount();
    for(int dataMount=0;dataMount<5;dataMount++)
    {
        p2.setX(count);
        for(int m=0;m<speed;m++)
        {
            p2.setY(rectf.height()/2-(ecg->getElement())*scale*0.01);
            m_waveList.push_back((QGraphicsItem *) this->addLine(QLineF(p1, p2),m_waveDataPen));
        }

        p1 = p2;
        if(count  > rectf.width())
        {
            removeWave();
            p1.setX(0);
            count=0;
        }
        else
        {
            count++;
        }
    }

 }

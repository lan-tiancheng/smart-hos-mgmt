#include "display.h"
#include "ui_display.h"

Display::Display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);
}

Display::~Display()
{
    delete ui;
}

void Display::updateData()
{
    readData(index+"/ecgI.txt",0);
    readData(index+"/ecgII.txt",1);
    readData(index+"/ecgIII.txt",2);
    readData(index+"/ecgAVL.txt",3);
    readData(index+"/ecgAVR.txt",4);
    readData(index+"/ecgAVF.txt",5);
    readData(index+"/ecgV1.txt",6);
    readData(index+"/ecgV2.txt",7);
    readData(index+"/ecgV3.txt",8);
    readData(index+"/ecgV4.txt",9);
    readData(index+"/ecgV5.txt",10);
    readData(index+"/ecgV6.txt",11);
}

void Display::readData(QString file_name,int which)
{
    QFile file(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
       qDebug () << "Could not open the file by reading";
       return;
    }
    QTextStream in(&file);
    QString text;
    text = in.readAll();//这也写可以全部读完
    file.close();//关闭文件

    QStringList d = text.split(" ");
    int len = d.count();

    switch(which)
    {
    case 0:
        ecg_data_I = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_I->putElement(d.at(i).toInt());
        }
        break;
    case 1:
        ecg_data_II = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_II->putElement(d.at(i).toInt());
        }
        break;
    case 2:
        ecg_data_III = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_III->putElement(d.at(i).toInt());
        }
        break;
    case 3:
        ecg_data_AVL = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_AVL->putElement(d.at(i).toInt());
        }
        break;
    case 4:
        ecg_data_AVR = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_AVR->putElement(d.at(i).toInt());
        }
        break;
    case 5:
        ecg_data_AVF = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_AVF->putElement(d.at(i).toInt());
        }
        break;
    case 6:
        ecg_data_V1 = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_V1->putElement(d.at(i).toInt());
        }
        break;
    case 7:
        ecg_data_V2 = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_V2->putElement(d.at(i).toInt());
        }
        break;
    case 8:
        ecg_data_V3 = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_V3->putElement(d.at(i).toInt());
        }
        break;
    case 9:
        ecg_data_V4 = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_V4->putElement(d.at(i).toInt());
        }
        break;
    case 10:
        ecg_data_V5 = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_V5->putElement(d.at(i).toInt());
        }
        break;
    case 11:
        ecg_data_V6 = new CircularBuf(len);
        for(int i=0;i<len;i++)
        {
            ecg_data_V6->putElement(d.at(i).toInt());
        }
        break;
    }
}

void Display::drawWave()
{
    int view_h = ui->graphicsView->height();
    int view_w = ui->graphicsView->width();

    myscene = new WaveScene(view_w-10,view_h-10,this);
    ui->graphicsView->setScene(myscene);
    myscene->removeWave();
    myscene->removeScale();
    myscene->createScale(10,12);

    myscene2 = new WaveScene(view_w-10,view_h-10,this);
    ui->graphicsView_2->setScene(myscene2);
    myscene2->removeWave();
    myscene2->removeScale();
    myscene2->createScale(10,12);

    myscene3 = new WaveScene(view_w-10,view_h-10,this);
    ui->graphicsView_3->setScene(myscene3);
    myscene3->removeWave();
    myscene3->removeScale();
    myscene3->createScale(10,12);

    myscene4 = new WaveScene(view_w-10,view_h-10,this);
    ui->graphicsView_4->setScene(myscene4);
    myscene4->removeWave();
    myscene4->removeScale();
    myscene4->createScale(10,12);

    myscene5 = new WaveScene(view_w-10,view_h-10,this);
    ui->graphicsView_5->setScene(myscene5);
    myscene5->removeWave();
    myscene5->removeScale();
    myscene5->createScale(10,12);

    myscene6 = new WaveScene(view_w-10,view_h-10,this);
    ui->graphicsView_6->setScene(myscene6);
    myscene6->removeWave();
    myscene6->removeScale();
    myscene6->createScale(10,12);

    displayTimer=new QTimer(this);
    connect(displayTimer,SIGNAL(timeout()),this,SLOT(draw()));//timeoutslot()为自定义槽
    displayTimer->start(50);
}

void Display::draw()
{
    myscene->drawing(comboAdapter(ui->comboBox->currentIndex()),1,2);
    myscene2->drawing(comboAdapter(ui->comboBox_2->currentIndex()),1,2);
    myscene3->drawing(comboAdapter(ui->comboBox_3->currentIndex()),1,2);
    myscene4->drawing(comboAdapter(ui->comboBox_4->currentIndex()),1,2);
    myscene5->drawing(comboAdapter(ui->comboBox_5->currentIndex()),1,2);
    myscene6->drawing(comboAdapter(ui->comboBox_6->currentIndex()),1,2);
}

CircularBuf* Display::comboAdapter(int comIndex)
{
    switch(comIndex)
    {
    case 0:
        return ecg_data_I;
        break;
    case 1:
        return ecg_data_II;
        break;
    case 2:
        return ecg_data_III;
        break;
    case 3:
        return ecg_data_AVL;
        break;
    case 4:
        return ecg_data_AVR;
        break;
    case 5:
        return ecg_data_AVF;
        break;
    case 6:
        return ecg_data_V1;
        break;
    case 7:
        return ecg_data_V2;
        break;
    case 8:
        return ecg_data_V3;
        break;
    case 9:
        return ecg_data_V4;
        break;
    case 10:
        return ecg_data_V5;
        break;
    case 11:
        return ecg_data_V6;
        break;
    default:
        return ecg_data_I;
    }
}

void Display::setIndex(QString string)
{
    index = string;
}

void Display::refresh()
{
    updateData();
    drawWave();
    this->show();
}


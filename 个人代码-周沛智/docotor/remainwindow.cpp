#include "remainwindow.h"
#include "ui_remainwindow.h"

#define CUR_FILE_PATH "/home/zpz/work3/2024-BIT-/Client/docotor/historyData/p220130703142759/"
#define CUR_EXCPTION_PATH "/home/zpz/work3/2024-BIT-/Client/docotor/historyException/"

reMainWindow::reMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::reMainWindow)
{
    ui->setupUi(this);

    creatVar();
    openSocket();
    currentUser();
    drawWave();

    connect(this,SIGNAL(savehisexcption()),this,SLOT(saveHistoryException()));

}

reMainWindow::~reMainWindow()
{
    delete ui;
}

void reMainWindow::saveHistoryData()
{
    savehistory(historyDataDir+"/ecgI.txt",secg_data_I,"d");
    savehistory(historyDataDir+"/ecgII.txt",secg_data_II,"d");
    savehistory(historyDataDir+"/ecgIII.txt",secg_data_III,"d");
    savehistory(historyDataDir+"/ecgAVL.txt",secg_data_AVL,"d");
    savehistory(historyDataDir+"/ecgAVR.txt",secg_data_AVR,"d");
    savehistory(historyDataDir+"/ecgAVF.txt",secg_data_AVF,"d");
    savehistory(historyDataDir+"/ecgV1.txt",secg_data_V1,"d");
    savehistory(historyDataDir+"/ecgV2.txt",secg_data_V2,"d");
    savehistory(historyDataDir+"/ecgV3.txt",secg_data_V3,"d");
    savehistory(historyDataDir+"/ecgV4.txt",secg_data_V4,"d");
    savehistory(historyDataDir+"/ecgV5.txt",secg_data_V5,"d");
    savehistory(historyDataDir+"/ecgV6.txt",secg_data_V6,"d");
}

void reMainWindow::saveHistoryException()
{
    savehistory(historyExceptionDir+"/ecgI.txt",secg_data_I,"e");
    savehistory(historyExceptionDir+"/ecgII.txt",secg_data_II,"e");
    savehistory(historyExceptionDir+"/ecgIII.txt",secg_data_III,"e");
    savehistory(historyExceptionDir+"/ecgAVL.txt",secg_data_AVL,"e");
    savehistory(historyExceptionDir+"/ecgAVR.txt",secg_data_AVR,"e");
    savehistory(historyExceptionDir+"/ecgAVF.txt",secg_data_AVF,"e");
    savehistory(historyExceptionDir+"/ecgV1.txt",secg_data_V1,"e");
    savehistory(historyExceptionDir+"/ecgV2.txt",secg_data_V2,"e");
    savehistory(historyExceptionDir+"/ecgV3.txt",secg_data_V3,"e");
    savehistory(historyExceptionDir+"/ecgV4.txt",secg_data_V4,"e");
    savehistory(historyExceptionDir+"/ecgV5.txt",secg_data_V5,"e");
    savehistory(historyExceptionDir+"/ecgV6.txt",secg_data_V6,"e");
}

void reMainWindow::savehistory(QString fileName,CircularBuf *buf,QString dore)
{
    QFile ecgfile(fileName);
    if(!ecgfile.exists())
    {
        ecgfile.open(QIODevice::WriteOnly | QIODevice::Append);
        ecgfile.close();
    }
    if(!ecgfile.open(QFile::WriteOnly | QFile::Text | QIODevice::Append))
    {
       qDebug () << "Could not open the file by reading";
       return;
    }
    QTextStream out(&ecgfile);
    if(dore=="d")
    {
        for(int t=0;t<20*(speedAdapter(ui->comboBox_8->currentIndex()));t++)
        {
            out<<buf->getElementNoIndexChange()<<" ";
        }
    }
    else if(dore=="e")
    {
        for(int t=0;t<1024;t++)
        {
            out<<buf->getElementNoIndexChange()<<" ";
        }
    }

    ecgfile.flush();//将缓冲区的内容输出的文本
    ecgfile.close();//关闭文件
}

void reMainWindow::creatVar()
{
    QTextCursor cursor = ui->textBrowser->textCursor();
    cursor.movePosition(QTextCursor::End);

    client_indoor = new client();
    ecg_data_I = new CircularBuf(1024);
    ecg_data_II = new CircularBuf(1024);
    ecg_data_III = new CircularBuf(1024);
    ecg_data_AVL = new CircularBuf(1024);
    ecg_data_AVR = new CircularBuf(1024);
    ecg_data_AVF = new CircularBuf(1024);
    ecg_data_V1 = new CircularBuf(1024);
    ecg_data_V2 = new CircularBuf(1024);
    ecg_data_V3 = new CircularBuf(1024);
    ecg_data_V4 = new CircularBuf(1024);
    ecg_data_V5 = new CircularBuf(1024);
    ecg_data_V6 = new CircularBuf(1024);
    secg_data_I = new CircularBuf(1024);
    secg_data_II = new CircularBuf(1024);
    secg_data_III = new CircularBuf(1024);
    secg_data_AVL = new CircularBuf(1024);
    secg_data_AVR = new CircularBuf(1024);
    secg_data_AVF = new CircularBuf(1024);
    secg_data_V1 = new CircularBuf(1024);
    secg_data_V2 = new CircularBuf(1024);
    secg_data_V3 = new CircularBuf(1024);
    secg_data_V4 = new CircularBuf(1024);
    secg_data_V5 = new CircularBuf(1024);
    secg_data_V6 = new CircularBuf(1024);

//    for(int c=0;c<900;c++)
//    {
//        ecg_data_I->putElement(ecg_data[c]);
//        ecg_data_II->putElement(ecg_data[c]);
//        ecg_data_III->putElement(0);
//        ecg_data_AVL->putElement((ecg_data[c])/2 );
//        ecg_data_AVR->putElement( -(ecg_data[c]) );
//        ecg_data_AVF->putElement( (ecg_data[c])/2 );
//        ecg_data_V1->putElement(ecg_data[c]);
//        ecg_data_V2->putElement(ecg_data[c]);
//        ecg_data_V3->putElement(ecg_data[c]);
//        ecg_data_V4->putElement(ecg_data[c]);
//        ecg_data_V5->putElement(ecg_data[c]);
//        ecg_data_V6->putElement(ecg_data[c]);
//        secg_data_I->putElement(ecg_data[c]);
//        secg_data_II->putElement(ecg_data[c]);
//        secg_data_III->putElement(0);
//        secg_data_AVL->putElement((ecg_data[c])/2 );
//        secg_data_AVR->putElement( -(ecg_data[c]) );
//        secg_data_AVF->putElement( (ecg_data[c])/2 );
//        secg_data_V1->putElement(ecg_data[c]);
//        secg_data_V2->putElement(ecg_data[c]);
//        secg_data_V3->putElement(ecg_data[c]);
//        secg_data_V4->putElement(ecg_data[c]);
//        secg_data_V5->putElement(ecg_data[c]);
//        secg_data_V6->putElement(ecg_data[c]);
//    }
}

void reMainWindow::openSocket()
{
    tcpserver = new TcpServer(this);
    tcpserver->set_st_client(client_indoor);
    tcpserver->set_st_service(service_indoor);
    connect(tcpserver,SIGNAL(getData()),this,SLOT(getdata()));

    connect(this,SIGNAL(sendQues(QString)),tcpserver,SLOT(revQues(QString)));
    tcpserver->listen(QHostAddress::Any,6666);
}

void reMainWindow::getdata()
{
//    ui->textBrowser->setText(ui->textBrowser->toPlainText()
//                             +QString::number(client_indoor->ecgI)+" "
//                             +QString::number(client_indoor->ecgII)+" "
//                             +QString::number(client_indoor->ecgIII)+" "
//                             +QString::number(client_indoor->ecgAVL)+" "
//                             +QString::number(client_indoor->ecgAVR)+" "
//                             +QString::number(client_indoor->ecgAVF)+" "
//                             +QString::number(client_indoor->ecgV1)+" "
//                             +QString::number(client_indoor->ecgV2)+" "
//                             +QString::number(client_indoor->ecgV3)+" "
//                             +QString::number(client_indoor->ecgV4)+" "
//                             +QString::number(client_indoor->ecgV5)+" "
//                             +QString::number(client_indoor->ecgV6)+" ");
//    ui->textBrowser->setTextCursor(cursor);


    ecg_data_I->putElement(client_indoor->ecgI);
    ecg_data_II->putElement(client_indoor->ecgII);
    ecg_data_III->putElement(client_indoor->ecgIII);
    ecg_data_AVL->putElement(client_indoor->ecgAVL);
    ecg_data_AVR->putElement(client_indoor->ecgAVR);
    ecg_data_AVF->putElement(client_indoor->ecgAVF);
    ecg_data_V1->putElement(client_indoor->ecgV1);
    ecg_data_V2->putElement(client_indoor->ecgV2);
    ecg_data_V3->putElement(client_indoor->ecgV3);
    ecg_data_V4->putElement(client_indoor->ecgV4);
    ecg_data_V5->putElement(client_indoor->ecgV5);
    ecg_data_V6->putElement(client_indoor->ecgV6);
    secg_data_I->putElement(client_indoor->ecgI);
    secg_data_II->putElement(client_indoor->ecgII);
    secg_data_III->putElement(client_indoor->ecgIII);
    secg_data_AVL->putElement(client_indoor->ecgAVL);
    secg_data_AVR->putElement(client_indoor->ecgAVR);
    secg_data_AVF->putElement(client_indoor->ecgAVF);
    secg_data_V1->putElement(client_indoor->ecgV1);
    secg_data_V2->putElement(client_indoor->ecgV2);
    secg_data_V3->putElement(client_indoor->ecgV3);
    secg_data_V4->putElement(client_indoor->ecgV4);
    secg_data_V5->putElement(client_indoor->ecgV5);
    secg_data_V6->putElement(client_indoor->ecgV6);

}

void reMainWindow::currentUser()
{
    userList.clear();
    QString cu = "p2";
    query.exec("select * from patient");
    while(query.next())
    {
        QString userName=query.value(0).toString();
        QString name=query.value(1).toString();
        QString sex=query.value(2).toString();
        QString age=query.value(3).toString();
        QString history=query.value(4).toString();
        QString career=query.value(5).toString();

        if(userName==cu)
        {
            ui->label_21->setText("p2");
            ui->label_22->setText(name);
            ui->label_23->setText(sex);
            ui->label_24->setText(age);
            ui->label_25->setText(history);
            ui->label_26->setText(career);

            onlineList.append(name);

//            cuser->id = cu;
//            cuser->name = name;
//            cuser->age = age;
//            cuser->sex = sex;
//            cuser->career = career;
//            cuser->history = history;
        }

        userList.append(name);
    }

    onlineItemModel = new QStandardItemModel(this);
    int onlineCount = onlineList.size();
    for(int i=0;i<onlineCount;i++)
    {
        QString string = static_cast<QString>(onlineList.at(i));
        QStandardItem *item = new QStandardItem(string);

        onlineItemModel->appendRow(item);
    }
    ui->listView_2->setModel(onlineItemModel);

    userItemModel = new QStandardItemModel(this);
    int userCount = userList.size();
    for(int i=0;i<userCount;i++)
    {
        QString string = static_cast<QString>(userList.at(i));
        QStandardItem *item = new QStandardItem(string);

        userItemModel->appendRow(item);
    }
    ui->listView_3->setModel(userItemModel);

}

void reMainWindow::drawWave()
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

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(draw()));//timeoutslot()为自定义槽
    timer->start(50);
}

void reMainWindow::draw()
{
    myscene->drawing(comboAdapter(ui->comboBox->currentIndex()),
                     speedAdapter(ui->comboBox_8->currentIndex()),
                     scaleAdapter(ui->comboBox_7->currentIndex()));

    myscene2->drawing(comboAdapter(ui->comboBox_2->currentIndex()),
                      speedAdapter(ui->comboBox_8->currentIndex()),
                      scaleAdapter(ui->comboBox_7->currentIndex()));

    myscene3->drawing(comboAdapter(ui->comboBox_3->currentIndex()),
                      speedAdapter(ui->comboBox_8->currentIndex()),
                      scaleAdapter(ui->comboBox_7->currentIndex()));

    myscene4->drawing(comboAdapter(ui->comboBox_4->currentIndex()),
                      speedAdapter(ui->comboBox_8->currentIndex()),
                      scaleAdapter(ui->comboBox_7->currentIndex()));

    myscene5->drawing(comboAdapter(ui->comboBox_5->currentIndex()),
                      speedAdapter(ui->comboBox_8->currentIndex()),
                      scaleAdapter(ui->comboBox_7->currentIndex()));

    myscene6->drawing(comboAdapter(ui->comboBox_6->currentIndex()),
                      speedAdapter(ui->comboBox_8->currentIndex()),
                      scaleAdapter(ui->comboBox_7->currentIndex()));

}

int reMainWindow::scaleAdapter(int index)
{
    switch(index)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 2;
        break;
    case 2:
        return 4;
        break;
    default:
        return 2;
    }
}

int reMainWindow::speedAdapter(int index)
{
    switch(index)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 2;
        break;
    case 2:
        return 4;
        break;
    default:
        return 2;
    }
}

CircularBuf* reMainWindow::comboAdapter(int index)
{
    switch(index)
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

void reMainWindow::on_action_triggered()
{
    r.show();
}

void reMainWindow::on_action_2_triggered()
{
    o.refresh();
}

void reMainWindow::on_pushButton_clicked()
{
    ui->pushButton_2->setText("停止存储");
    QString time = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    historyDataDir = CUR_FILE_PATH +ui->label_21->text()+time;
    QDir *historyDataDirectory = new QDir;
    historyDataDirectory->mkdir(historyDataDir);

    saveTimer=new QTimer(this);
    connect(saveTimer,SIGNAL(timeout()),this,SLOT(saveHistoryData()));
    saveTimer->start(50);
}

void reMainWindow::on_pushButton_2_clicked()
{
    if(ui->pushButton_2->text()=="异常捕获")
    {
        QString time = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
        historyExceptionDir = CUR_EXCPTION_PATH+ui->label_21->text()+time;
        QDir *historyExceptionDirectory = new QDir;
        historyExceptionDirectory->mkdir(historyExceptionDir);
        emit savehisexcption();
    }
    else
    {
        ui->pushButton_2->setText("异常捕获");
        if(saveTimer!=NULL)
            saveTimer->deleteLater();
    }
}

void reMainWindow::on_pushButton_3_clicked()
{
    hd.setDataDirStr(CUR_FILE_PATH);
    hd.refresh();
}

void reMainWindow::on_pushButton_4_clicked()
{
    hd.setDataDirStr(CUR_EXCPTION_PATH);
    hd.refresh();
}

void reMainWindow::on_pushButton_5_clicked()
{
    connect(&q,SIGNAL(sendQ(QString)),this,SLOT(reviceQues(QString)));
    q.show();
}
void reMainWindow::reviceQues(QString i)
{
    emit sendQues(i);
}

void reMainWindow::on_pushButton_6_clicked()
{
    m.show();
}

#include "questionnaire.h"
#include "ui_questionnaire.h"

Questionnaire::Questionnaire(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Questionnaire)
{
    ui->setupUi(this);
    standardItemModel = new QStandardItemModel(this);
    QStringList strList;
    strList.append("临床表现");
    strList.append("严重程度");
    strList.append("持续时间");
    strList.append("症状起因");
    strList.append("前期治疗");
    strList.append("疗后状况");
    strList.append("初步诊断");
    strList.append("治疗方案");
    strList.append("处方");
    strList.append("医嘱");
    int count = strList.size();
    for(int i=0;i<count;i++)
    {
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem *item = new QStandardItem(string);

        standardItemModel->appendRow(item);
    }
    ui->listView->setModel(standardItemModel);
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(itemClicked(QModelIndex)));

}

Questionnaire::~Questionnaire()
{
    delete ui;
}

void Questionnaire::itemClicked(QModelIndex index)
{
    ui->listWidget->addItem(index.data().toString());
}

void Questionnaire::on_pushButton_clicked()
{
    ui->listWidget->takeItem(ui->listWidget->currentRow());
}

void Questionnaire::on_pushButton_2_clicked()
{
    QList <QListWidgetItem *> item1 =
            ui->listWidget->findItems(QString("临床表现"),Qt::MatchWrap  |Qt::MatchWildcard);
    QList <QListWidgetItem *> item2 =
            ui->listWidget->findItems(QString("严重程度"),Qt::MatchWrap  |Qt::MatchWildcard);
    QList <QListWidgetItem *> item3 =
            ui->listWidget->findItems(QString("持续时间"),Qt::MatchWrap  |Qt::MatchWildcard);
    QList <QListWidgetItem *> item4 =
            ui->listWidget->findItems(QString("症状起因"),Qt::MatchWrap  |Qt::MatchWildcard);
    QList <QListWidgetItem *> item5 =
            ui->listWidget->findItems(QString("前期治疗"),Qt::MatchWrap  |Qt::MatchWildcard);
    QList <QListWidgetItem *> item6 =
            ui->listWidget->findItems(QString("疗后状况"),Qt::MatchWrap  |Qt::MatchWildcard);
    QList <QListWidgetItem *> item7 =
            ui->listWidget->findItems(QString("初步诊断"),Qt::MatchWrap  |Qt::MatchWildcard);
    QList <QListWidgetItem *> item8 =
            ui->listWidget->findItems(QString("治疗方案"),Qt::MatchWrap  |Qt::MatchWildcard);
    QList <QListWidgetItem *> item9 =
            ui->listWidget->findItems(QString("处方"),Qt::MatchWrap  |Qt::MatchWildcard);
    QList <QListWidgetItem *> item10 =
            ui->listWidget->findItems(QString("医嘱"),Qt::MatchWrap  |Qt::MatchWildcard);

    if(item7.size()!=0 || item8.size()!=0 || item9.size()!=0 || item10.size()!=0)
        emit sendQ("res");
    if(item4.size()!=0 || item5.size()!=0 || item6.size()!=0)
        emit sendQ("dia");
    if(item1.size()!=0 || item2.size()!=0 || item3.size()!=0)
        emit sendQ("sym");

}

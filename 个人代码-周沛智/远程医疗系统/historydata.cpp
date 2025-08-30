#include "historydata.h"
#include "ui_historydata.h"

HistoryData::HistoryData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryData)
{
    ui->setupUi(this);
    QDir dataDir(dataDirStr);
    if(!dataDir.exists())
    {
        QMessageBox::about(this,"warning","没有存储记录！");
    }
    dataList = dataDir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->listWidget->clear();
    ui->listWidget->addItems(dataList);
    ui->listWidget->sortItems(Qt::AscendingOrder);
}

HistoryData::~HistoryData()
{
    delete ui;
}

void HistoryData::refresh()
{
    QDir dataDir(dataDirStr);
    if(!dataDir.exists())
    {
        QMessageBox::about(this,"warning","没有存储记录！");
    }
    dataList = dataDir.entryList(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->listWidget->clear();
    ui->listWidget->addItems(dataList);
    ui->listWidget->sortItems(Qt::AscendingOrder);
    this->show();
}

void HistoryData::setDataDirStr(QString str)
{
    dataDirStr = str;
}

void HistoryData::on_pushButton_clicked()
{
    QString string = dataDirStr + "/"
            +ui->listWidget->currentIndex().data().toString();
    d.setIndex(string);
    d.refresh();
    d.show();
}

void HistoryData::on_pushButton_2_clicked()
{
    removeDir(dataDirStr + "/"
              +ui->listWidget->currentIndex().data().toString());
    ui->listWidget->takeItem(ui->listWidget->currentRow());
}

void HistoryData::removeDir(const QString& path)
{
  QDir dir(path);
  QFileInfoList info_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::AllDirs);
  foreach(QFileInfo file_info, info_list)
  {
    if (file_info.isDir())
    {
      removeDir(file_info.absoluteFilePath());
    }
    else if (file_info.isFile())
    {
      QFile file(file_info.absoluteFilePath());
      file.remove();
    }
  }
  QDir temp_dir;
  temp_dir.rmdir(path) ;
}


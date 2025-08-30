#ifndef HISTORYDATA_H
#define HISTORYDATA_H

#include <QDialog>
#include <QDir>
#include <QMessageBox>
#include <QStandardItemModel>
#include "display.h"
#include <QFileInfoList>
#include <QFileInfo>

namespace Ui {
class HistoryData;
}

class HistoryData : public QDialog
{
    Q_OBJECT
    
public:
    explicit HistoryData(QWidget *parent = 0);
    ~HistoryData();

    void refresh();
    void removeDir(const QString& path);
    void setDataDirStr(QString str);

    
private:
    Ui::HistoryData *ui;
    Display d;

    QStringList dataList;
    QDir dataDir;
    QString dataDirStr;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // HISTORYDATA_H

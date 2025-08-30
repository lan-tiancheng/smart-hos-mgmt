#ifndef PINF_H
#define PINF_H

#include <QWidget>
#include <QTableView>
#include <QTableWidgetItem>
#include <QPainter>
#include <QStyledItemDelegate>
#include "pbd.h"
#include <QStandardItemModel>
#include <QVector>

namespace Ui {
class pinf;
}

// ButtonDelegate 类声明
class ButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ButtonDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void buttonClicked(const QModelIndex &index);

};

class pinf : public QWidget
{
    Q_OBJECT

public:
    explicit pinf(QWidget *parent = nullptr);
    ~pinf();
    pbd *windowp = nullptr;

    // 设置每个表格的数据的方法
    void setRecordationData(const QVector<QVector<QString>> &data);
    void setUserData(const QVector<QVector<QString>> &data);
    void setGoodsData(const QVector<QVector<QString>> &data);
    void setStatisticsData(const QVector<QVector<QString>> &data);
QVector<QString> patientIds;
QVector<QString> Ids;
signals:
    void goback();


private slots:
    void on_pushButton_clicked();
    void on_tableViewRecordation_2_doubleClicked(const QModelIndex &index);
    void on_tabWidget_tabBarClicked(int index);
    void onButtonClicked(const QModelIndex &index); // 处理按钮点击的槽

    //void on_tabWidget_tabBarClicked(int index);



private:
    Ui::pinf *ui;
    void setupTableViewStyle(QTableView *tableView);

    ButtonDelegate *buttonDelegate; // ButtonDelegate 实例
         // 存储患者编号
};

#endif // PINF_H

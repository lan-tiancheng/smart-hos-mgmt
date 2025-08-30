#ifndef LIVEWINDOW_H
#define LIVEWINDOW_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QSpinBox>

class LiveWindow : public QWidget {
    Q_OBJECT

public:
    LiveWindow();  // 构造函数

private slots:
    void previousPage();
    void nextPage();
    void updateTableData(int page);

private:
    QTableView *tableView;           // 表格视图对象
    QStandardItemModel *model;       // 数据模型
    QVector<QStringList> allData;
    QSpinBox *pageSpinBox;
    void initializeData();           // 初始化数据的方法
};

#endif // LIVEWINDOW_H

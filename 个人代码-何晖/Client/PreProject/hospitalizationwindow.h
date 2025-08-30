#ifndef HOSPITALIZATIONWINDOW_H
#define HOSPITALIZATIONWINDOW_H

#include <QWidget>
#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QHeaderView>
#include <QLabel>
#include <QSizePolicy>

namespace Ui {
class HospitalizationWindow;
}

class HospitalizationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HospitalizationWindow(QWidget *parent = nullptr);
    ~HospitalizationWindow();

private:
    Ui::HospitalizationWindow *ui;

private:
    QTableView *tableView;
    QStandardItemModel *model;
    QPushButton *prevButton;
    QPushButton *nextButton;
    int currentPage;
    int rowsPerPage;
    int totalRows;

    // 虚拟数据
    QVector<QStringList> virtualData;


    void loadPage(int pageNumber);
    void updateNavigationButtons();
    void previousPage();
    void nextPage();
public:
    void initializeVirtualData(int num,QString *indate,QString *roomnum,QString *bednum,QString *yourdoc);

};

#endif // HOSPITALIZATIONWINDOW_H

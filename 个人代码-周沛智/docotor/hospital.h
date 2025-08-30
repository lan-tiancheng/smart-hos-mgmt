#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <QWidget>
#include <QMouseEvent>
#include <QTableWidgetItem>
#include <QMessageBox>

namespace Ui {
class Hospital;
}

class Hospital : public QWidget
{
    Q_OBJECT

public:
    explicit Hospital(QWidget *parent = nullptr);
    ~Hospital();

private slots:
    void on_saveButton_clicked();
    void on_returnButton_clicked();
    void on_closeButton_clicked();

private:
    Ui::Hospital *ui;
    bool isDragging;
    QPoint dragStartPosition;

    bool validateData();
    void showDataInsufficientMessage();
    void saveDataToDatabase(); // 存入数据库

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // HOSPITAL_H

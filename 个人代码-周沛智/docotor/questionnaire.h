#ifndef QUESTIONNAIRE_H
#define QUESTIONNAIRE_H

#include <QDialog>
#include <QStandardItemModel>
#include <QDebug>

namespace Ui {
class Questionnaire;
}

class Questionnaire : public QDialog
{
    Q_OBJECT
    
public:
    explicit Questionnaire(QWidget *parent = 0);
    ~Questionnaire();
    
private:
    Ui::Questionnaire *ui;
    QStandardItemModel *standardItemModel;

signals:
    void sendQ(QString i);

private slots:
    void itemClicked(QModelIndex index);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // QUESTIONNAIRE_H

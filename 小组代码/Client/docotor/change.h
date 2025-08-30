#ifndef CHANGE_H
#define CHANGE_H

#include <QWidget>
#include"global.h"

namespace Ui {
class change;
}

class change : public QWidget
{
    Q_OBJECT

public:
    explicit change(QWidget *parent = nullptr);
    ~change();

    QString getDepartmentName(int num ) const{
        switch (num) {
            case 1: return "儿科";
            case 2: return "内科";
            case 3: return "外科";
            case 4: return "妇科";
            case 5: return "皮肤科";
            default: return "未知科室";
        }
    }

public: signals:
    void dataUpdated();  // 信号：数据更新

private slots:
    void on_pushButtonCommit_clicked();  // 按钮点击事件
    void slot_edit_doctor_selfintr_failed();//传输失败逻辑，跳出失败弹窗
    void slot_updata_success();//传输成功，更新数据和跳出成功弹窗

private:
    Ui::change *ui;
};

#endif // CHANGE_H

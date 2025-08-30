#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include <QDialog>

namespace Ui {
class DiagnosticDialog;
}

class DiagnosticDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DiagnosticDialog(QWidget *parent = nullptr);
    ~DiagnosticDialog();

    static QString paintid;
private slots:
    void on_buttonConfirm_clicked();
    void on_buttonCancel_clicked();

private:
    Ui::DiagnosticDialog *ui;
};

#endif // DIAGNOSTIC_H

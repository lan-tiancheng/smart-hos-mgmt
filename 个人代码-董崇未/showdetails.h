#ifndef SHOWDETAILS_H
#define SHOWDETAILS_H

#include <QDialog>

class QTextEdit;

class ShowDetails : public QDialog {
    Q_OBJECT

public:
    explicit ShowDetails(const QString &details, QWidget *parent = nullptr);

private:
    QTextEdit *detailsEdit;
};

#endif // SHOWDETAILS_H

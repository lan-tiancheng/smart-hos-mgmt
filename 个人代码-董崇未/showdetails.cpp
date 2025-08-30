#include "showdetails.h"
#include <QVBoxLayout>
#include <QTextEdit>

ShowDetails::ShowDetails(const QString &details, QWidget *parent)
    : QDialog(parent) { // Use QDialog instead of QWidget
    QVBoxLayout *layout = new QVBoxLayout(this);

    detailsEdit = new QTextEdit(this);
    detailsEdit->setText(details);
    detailsEdit->setReadOnly(true);

    layout->addWidget(detailsEdit);

    setLayout(layout);
    setWindowTitle("详细信息");

    setMinimumSize(600, 400);
}

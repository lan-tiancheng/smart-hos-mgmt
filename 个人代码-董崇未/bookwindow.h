#ifndef BOOKWINDOW_H
#define BOOKWINDOW_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include "childwd.h"
#include "womanwd.h"
#include "outwd.h"
#include "insidewd.h"
#include "skinwd.h"

namespace Ui {
class BookWindow;
}

class BookWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BookWindow(QWidget *parent = nullptr);
    ~BookWindow();
private slots:
     void onItemClicked(QListWidgetItem*);

private:
    Ui::BookWindow *ui;
    ChildWd childwd;
    WomanWd womanwd;
    OutWd outwd;
    InsideWd insidewd;
    SkinWd skinwd;

};

#endif // BOOKWINDOW_H

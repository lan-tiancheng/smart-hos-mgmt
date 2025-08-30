#ifndef PMAINWINDOW_H
#define PMAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "homewindow.h"
#include "bookwindow.h"
#include "personalwindow.h"
#include "chattingroomwindow.h"
#include "hospitalizationwindow.h"
#include "ownwindow.h"
#include "chatwindow.h"

//#include "chatdialog.h"

void MIsqlite_Init();

QT_BEGIN_NAMESPACE
namespace Ui { class PMainWindow; }
QT_END_NAMESPACE

class PMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PMainWindow(QWidget *parent = nullptr);
    ~PMainWindow();
public slots:
    void infoRecv(int);

private slots:


private:
    Ui::PMainWindow *ui;
    QButtonGroup btnGroup;
    HomeWindow homeWd;
    BookWindow bookWd;
    PersonalWindow personalWd;
    ChattingroomWindow chattingroomWd;
    HospitalizationWindow hospitalizationWd;
    ChatWindow chatWd;
    OwnWindow ownWd;
    bool speakStatus=true;
    Audio *my_audio;
    QTextToSpeech *my_say;
    //ChatDialog chatdialogWd;
};
#endif // PMAINWINDOW_H

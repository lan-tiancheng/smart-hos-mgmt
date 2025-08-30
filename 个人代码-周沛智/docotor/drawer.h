#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>
#include <QToolButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include "widget.h"

class Drawer : public QWidget
{
    Q_OBJECT

public:
    explicit Drawer(QWidget *parent = nullptr);

private slots:
    void showChatWidget1();
    void showChatWidget2();
    void showChatWidget3();
    void showChatWidget4();
    void showChatWidget5();
    void showChatWidget6();
    void showChatWidget7();
    void showChatWidget8();
    void showChatWidget9();

private:
    QToolButton *toolBtn1;
    QToolButton *toolBtn2;
    QToolButton *toolBtn3;
    QToolButton *toolBtn4;
    QToolButton *toolBtn5;
    QToolButton *toolBtn6;
    QToolButton *toolBtn7;
    QToolButton *toolBtn8;
    QToolButton *toolBtn9;

    Widget *chatWidget1;
    Widget *chatWidget2;
    Widget *chatWidget3;
    Widget *chatWidget4;
    Widget *chatWidget5;
    Widget *chatWidget6;
    Widget *chatWidget7;
    Widget *chatWidget8;
    Widget *chatWidget9;

    QScrollArea *scrollArea;
    QWidget *containerWidget;
    QVBoxLayout *buttonLayout;
};

#endif // DRAWER_H

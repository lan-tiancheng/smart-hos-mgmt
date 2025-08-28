#include "PatientHomeWindow.h"
#include <QVBoxLayout>
#include <QLabel>

PatientHomeWindow::PatientHomeWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("患者端 - 首页");
    auto* v = new QVBoxLayout(this);
    v->addWidget(new QLabel("欢迎进入患者首页（待实现：挂号、预约、病例、医嘱、聊天...）"));
}
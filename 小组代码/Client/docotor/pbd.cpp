#include "pbd.h"
#include "ui_pbd.h"
#include "diagnostic.h"
#include "advice.h"
#include "hospital.h"
#include <QPainter>
#include <QStandardItemModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include"pinf.h"
#include"usermgr.h"

pbd::pbd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pbd)
{
    ui->setupUi(this);
    connect(UserMgr::GetInstance().get(),&UserMgr::sig_to_paint_info_detail,this,&pbd::populateData);

}

pbd::~pbd()
{
    delete ui;
}

void pbd::on_pushButton_return_clicked()
{
    emit goback();
}

void pbd::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    QPixmap background(":/images/pictures/患者主界面.jpg");
    painter.drawPixmap(rect(), background);
}

void pbd::on_pushButton_2_clicked()
{
    DiagnosticDialog::paintid=paintid;
    DiagnosticDialog *diagnosticWindow = new DiagnosticDialog(this);
    diagnosticWindow->show();
}

void pbd::on_pushButton_4_clicked()
{
    advice *adviceWindow = new advice(this);
    adviceWindow->show();
}

void pbd::on_pushButton_3_clicked()
{
    Hospital *hospitalWindow = new Hospital(this);
    hospitalWindow->show();
}

void pbd::populateData(const QString &jsonString)
{
    QByteArray jsonData = jsonString.toUtf8();
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isObject()) return;

    QJsonObject obj = doc.object();
    QJsonArray names = obj["names"].toArray();
    QJsonArray accounts = obj["accounts"].toArray();
    QJsonArray times = obj["times"].toArray();
    QJsonArray departments = obj["departments"].toArray();
    QJsonArray phones = obj["phones"].toArray();
    paintid=obj["id"].toString();

    // 填充患者姓名
   /* QStandardItemModel *nameModel = new QStandardItemModel();
    for (const QJsonValue &value : names) {
        QStandardItem *item = new QStandardItem(value.toString());
        nameModel->appendRow(item);
    }
    ui->tableView->setText(nameModel);

    // 填充患者账号
    QStandardItemModel *accountModel = new QStandardItemModel();
    for (const QJsonValue &value : accounts) {
        QStandardItem *item = new QStandardItem(value.toString());
        accountModel->appendRow(item);
    }
    ui->tableView_5->setModel(accountModel);

    // 填充预约时间
    QStandardItemModel *timeModel = new QStandardItemModel();
    for (const QJsonValue &value : times) {
        QStandardItem *item = new QStandardItem(value.toString());
        timeModel->appendRow(item);
    }
    ui->tableView_2->setModel(timeModel);

    // 填充所属科室
    QStandardItemModel *departmentModel = new QStandardItemModel();
    for (const QJsonValue &value : departments) {
        QStandardItem *item = new QStandardItem(value.toString());
        departmentModel->appendRow(item);
    }
    ui->tableView_3->setModel(departmentModel);

    // 填充电话
    QStandardItemModel *phoneModel = new QStandardItemModel();
    for (const QJsonValue &value : phones) {
        QStandardItem *item = new QStandardItem(value.toString());
        phoneModel->appendRow(item);
    }
    ui->tableView_4->setModel(phoneModel);*/
}

//QString jsonString = "{\"names\": [\"张三\"], \"accounts\": [\"123456\"], \"times\": [\"2024-08-28 10:00\"], \"departments\": [\"内科\"], \"phones\": [\"123-456-7890\"]}";
//pbdWidget->populateData(jsonString);

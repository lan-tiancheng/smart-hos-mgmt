#include "hospital.h"
#include "ui_hospital.h"

#include <qjsondocument.h>
#include <qjsonobject.h>
#include <tcpmgr.h>
#include <usermgr.h>

Hospital::Hospital(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hospital),
    isDragging(false)
{
    ui->setupUi(this);

    // 设置表格
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "患者姓名" << "病房号" << "病床号" << "医生姓名" << "入院日期");
    ui->tableWidget->setRowCount(1); // 初始设置一行

    // 允许用户编辑单元格
    ui->tableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);

    // 连接按钮的槽函数
    connect(ui->saveButton, &QPushButton::clicked, this, &Hospital::on_saveButton_clicked);
    connect(ui->returnButton, &QPushButton::clicked, this, &Hospital::on_returnButton_clicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &Hospital::on_closeButton_clicked);

    // 设置窗口标志以允许拖动
    setWindowFlags(Qt::FramelessWindowHint); // 无边框窗口，支持拖动
}

Hospital::~Hospital()
{
    delete ui;
}

bool Hospital::validateData()
{
    int columnCount = ui->tableWidget->columnCount();
    QTableWidgetItem *item;
    for (int j = 0; j < columnCount; ++j) {
        item = ui->tableWidget->item(0, j);
        if (!item || item->text().isEmpty()) {
            return false; // 有未填入的数据
        }
    }
    return true; // 所有数据都已填入
}

void Hospital::saveDataToDatabase()
{
    // 从表格中获取数据
    QString patientName = ui->tableWidget->item(0, 0)->text();
    QString wardNumber = ui->tableWidget->item(0, 1)->text();
    QString bedNumber = ui->tableWidget->item(0, 2)->text();
    QString doctorName = ui->tableWidget->item(0, 3)->text();
    QString admissionDate = ui->tableWidget->item(0, 4)->text();
    QString patientId=UserMgr::GetInstance()->getpainIdep();
    int doctorid=UserMgr::GetInstance()->getUid();
    //QString resultText = ui->textEditResult->toPlainText();
    QJsonObject jsonObj;
    jsonObj["doctor_uid"]=UserMgr::GetInstance()->getUid();
    jsonObj["patient_uid"]=patientId;
    jsonObj["patient_name"]=patientName;
    jsonObj["bed_number"]=bedNumber;
    jsonObj["admission_data"]=admissionDate;
    jsonObj["doctorname"]=doctorName;
    jsonObj["room"]=wardNumber;
    //qDebug()<<jsonObj["doctoruid"].toInt();
    //jsonObj["result"]=resultText;
    //jsonObj["id"]=UserMgr::GetInstance()->getguahaoidEdit();

    QJsonDocument doc(jsonObj);
    QString jsonString = doc.toJson(QJsonDocument::Indented);

    //发送tcp请求给chat server
    emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_hospital, jsonString);



}

void Hospital::on_saveButton_clicked()
{
    if (validateData()) {
        saveDataToDatabase();
        QMessageBox::information(this, tr("确认保存"), tr("数据已保存成功。"), QMessageBox::Ok);
        close(); // 关闭窗口
    } else {
        showDataInsufficientMessage();
    }
}

void Hospital::on_returnButton_clicked()
{
    close(); // 关闭窗口
}

void Hospital::on_closeButton_clicked()
{
    close(); // 关闭窗口
}

void Hospital::showDataInsufficientMessage()
{
    static bool shown = false;
    if (!shown) {
        QMessageBox::warning(this, tr("保存失败"), tr("数据不足，无法保存。"), QMessageBox::Ok);
        shown = true; // 只弹出一次
    }
}

void Hospital::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        dragStartPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void Hospital::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - dragStartPosition);
        event->accept();
    }
}

void Hospital::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isDragging = false;
}

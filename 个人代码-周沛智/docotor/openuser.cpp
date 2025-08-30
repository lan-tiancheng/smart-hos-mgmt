#include "openuser.h"
#include "ui_openuser.h"

OpenUser::OpenUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenUser)
{
    ui->setupUi(this);
    model = new QSqlRelationalTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable("patient");
    model->setRelation(7,QSqlRelation("doctor","id","name"));

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("用户名"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("性别"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("年龄"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("病史"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("职业"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("电话"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("医生"));


    model->select();
    model->setSort(0,Qt::AscendingOrder);
    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    model_2 = new QSqlRelationalTableModel(this);
    model_2->setEditStrategy(QSqlTableModel::OnFieldChange);
    model_2->setTable("doctor");

    model_2->setHeaderData(0,Qt::Horizontal,QObject::tr("用户名"));
    model_2->setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
    model_2->setHeaderData(2,Qt::Horizontal,QObject::tr("医院"));
    model_2->setHeaderData(3,Qt::Horizontal,QObject::tr("电话"));

    model_2->select();
    model_2->setSort(0,Qt::AscendingOrder);
    ui->tableView_2->setModel(model_2);

}

OpenUser::~OpenUser()
{
    delete ui;
}

void OpenUser::refresh()
{
    model->select();
    model_2->select();
    this->show();
}


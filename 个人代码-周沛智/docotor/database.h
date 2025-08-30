#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if(!db.open())
        return false;
    QSqlQuery query;

    query.exec("create table patient (id vchar primary key, name vchar, sex vchar, age int, medicalHistory vchar, career vchar, tel vchar, doctor vchar)");
    query.exec("insert into patient values ('p1','老李','男',54,'心病','律师','132456','d1')");
    query.exec("insert into patient values ('p2','老胡','女',58,'胃病','工人','132457','d3')");
    query.exec("insert into patient values ('p3','老杨','男',76,'脑病','记者','132458','d2')");

    query.exec("create table doctor (id vchar primary key, name vchar, hispital vchar, tel vchar)");
    query.exec("insert into doctor values ('d1','张','北京','1234565')");
    query.exec("insert into doctor values ('d2','李','南京','456789')");
    query.exec("insert into doctor values ('d3','刘','广州','654987')");

    query.exec("create table medicalrecord (time vchar primary key,user vchar, xinlv vchar,huxi vchar,tiwen vchar,xueya vchar,xueyang vchar,xuetang vchar,bingkuang vchar,jieguo vchar, fangan vchar, beizhu vchar)");
    query.exec("insert into medicalrecord values ('20131213','p2','69','21','36','98','97','4.2','头疼，三天一次，严重','高血压','服药，测血压','1111')");
    query.exec("insert into medicalrecord values ('20131315','p2','64','25','34','96','99','4.3','目眩','高血糖','输液','2222')");
    query.exec("insert into medicalrecord values ('20141231','p2','75','27','41','97','98','4.5','发烧','感冒','服药','3333')");

    return true;
}


#endif // DATABASE_H

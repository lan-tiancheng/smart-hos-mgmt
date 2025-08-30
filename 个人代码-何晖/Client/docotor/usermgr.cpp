#include "usermgr.h"

UserMgr::~UserMgr()
{

}

void UserMgr::SetName(QString name)
{
    _name = name;
}

void UserMgr::SetUid(int uid)
{
    _uid = uid;
}

void UserMgr::SetToken(QString token)
{
    _token = token;
}

void UserMgr::SetWorkID(QString workID)
{
    _workID=workID;
}

void UserMgr::setEmail(QString email)
{
    _email=email;
}

void UserMgr::setPhone(QString phone)
{
    _phone=phone;
}

void UserMgr::setSex(int sex)
{
    _sex=sex;
}

void UserMgr::setYear(QString year)
{
    _year=year;
}

void UserMgr::setMonth(QString month)
{
    _month=month;
}

void UserMgr::setDay(QString day)
{
    _day=day;
}

void UserMgr::setIDcard(QString IDcard)
{
    _IDcard=IDcard;
}

void UserMgr::setDepartment_id(int department_id)
{
    _department_id=department_id;
}

void UserMgr::setIntr(QString intr)
{
    _intr=intr;
}

UserMgr::UserMgr()
{

}

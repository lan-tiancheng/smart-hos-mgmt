#ifndef DOCTOR_H
#define DOCTOR_H

#include "user.h"
#include <QDate>
#include <QTime>
//医生属性：部门 工作日期 工作时间

class DoctorWorkingHours {
private:
    QTime startTime;
    QTime endTime;

public:
    DoctorWorkingHours(const QTime &start, const QTime &end)
        : startTime(start), endTime(end) {}

    // 获取工作开始时间
    QTime getStartTime() const ;

    // 获取工作结束时间
    QTime getEndTime() const ;

    // 设置工作开始时间
    void setStartTime(const QTime &start) ;

    // 设置工作结束时间
    void setEndTime(const QTime &end) ;

    // 计算工作时长
    int getWorkingHours() const ;
};


class Doctor : public User
{
public:
    Doctor();

    // 医生特有属性
    QString department() const;
    void setDepartment(const QString &department);

    QDate workDate() const;
    void setWorkDate(const QDate &date);

    DoctorWorkingHours workTime() const;
    void setWorkTime(const DoctorWorkingHours &workHours);
    // 覆盖基类方法以包含新属性
    QJsonObject toJson() const override;
    void fromJson(const QJsonObject &json) override;

private:
    QString m_department;
    QDate m_workDate;
    DoctorWorkingHours m_worktime;
};

#endif // DOCTOR_H

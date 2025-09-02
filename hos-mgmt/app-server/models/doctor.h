#pragma once
#include <QString>
#include <QDate>
#include <QTime>
#include <QJsonObject>
#include "user.h"

class DoctorWorkingHours {
public:
    DoctorWorkingHours(const QTime& start = QTime(9, 0), const QTime& end = QTime(17, 0));
    QTime startTime() const;
    QTime endTime() const;

    void setStartTime(const QTime&);
    void setEndTime(const QTime&);
    int workingHours() const;

private:
    QTime m_startTime;
    QTime m_endTime;
};

class Doctor : public User {
public:
    Doctor();
    QString department() const;
    void setDepartment(const QString&);

    QDate workDate() const;
    void setWorkDate(const QDate&);

    DoctorWorkingHours workTime() const;
    void setWorkTime(const DoctorWorkingHours&);

    QJsonObject toJson() const override;
    void fromJson(const QJsonObject&) override;

    // 可选：数据库兼容 getter/setter
    QString id() const;
    void setId(const QString&);

private:
    QString m_id;
    QString m_department;
    QDate m_workDate;
    DoctorWorkingHours m_worktime;
};

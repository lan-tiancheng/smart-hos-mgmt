#include "doctor.h"

DoctorWorkingHours::DoctorWorkingHours(const QTime& start, const QTime& end)
    : m_startTime(start), m_endTime(end) {}

QTime DoctorWorkingHours::startTime() const { return m_startTime; }
QTime DoctorWorkingHours::endTime() const { return m_endTime; }

void DoctorWorkingHours::setStartTime(const QTime& t) { m_startTime = t; }
void DoctorWorkingHours::setEndTime(const QTime& t) { m_endTime = t; }
int DoctorWorkingHours::workingHours() const { return m_startTime.msecsTo(m_endTime) / 3600000; }

Doctor::Doctor() : User(), m_department(""), m_workDate(QDate::currentDate()), m_worktime(QTime(9,0), QTime(17,0)) {}

QString Doctor::department() const { return m_department; }
void Doctor::setDepartment(const QString& dept) { m_department = dept; }

QDate Doctor::workDate() const { return m_workDate; }
void Doctor::setWorkDate(const QDate& date) { m_workDate = date; }

DoctorWorkingHours Doctor::workTime() const { return m_worktime; }
void Doctor::setWorkTime(const DoctorWorkingHours& w) { m_worktime = w; }

QString Doctor::id() const { return m_id; }
void Doctor::setId(const QString& id) { m_id = id; }

QJsonObject Doctor::toJson() const {
    QJsonObject json = User::toJson();
    json["id"] = m_id;
    json["department"] = m_department;
    json["workDate"] = m_workDate.toString(Qt::ISODate);
    json["workStart"] = m_worktime.startTime().toString("HH:mm");
    json["workEnd"] = m_worktime.endTime().toString("HH:mm");
    return json;
}
void Doctor::fromJson(const QJsonObject& json) {
    User::fromJson(json);
    m_id = json["id"].toString();
    m_department = json["department"].toString();
    m_workDate = QDate::fromString(json["workDate"].toString(), Qt::ISODate);
    QTime start = QTime::fromString(json["workStart"].toString(), "HH:mm");
    QTime end = QTime::fromString(json["workEnd"].toString(), "HH:mm");
    m_worktime = DoctorWorkingHours(start, end);
}

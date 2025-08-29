#include "doctor.h"
#include <QJsonObject>
#include <QDate>
#include <QString>

// ======================= DoctorWorkingHours 类实现 =======================
// 获取工作开始时间
QTime DoctorWorkingHours::getStartTime() const {
    return startTime;
}

// 获取工作结束时间
QTime DoctorWorkingHours::getEndTime() const {
    return endTime;
}

// 设置工作开始时间
void DoctorWorkingHours::setStartTime(const QTime &start) {
    startTime = start;
}

// 设置工作结束时间
void DoctorWorkingHours::setEndTime(const QTime &end) {
    endTime = end;
}

// 计算工作时长（单位：小时）
int DoctorWorkingHours::getWorkingHours() const {
    return startTime.msecsTo(endTime) / 3600000;  // 将毫秒转换为小时
}

// ======================= Doctor 类实现 =======================

Doctor::Doctor()
    : m_department(""), m_workDate(QDate::currentDate()), m_worktime(QTime(9, 0), QTime(17, 0)) {}

// 获取部门
QString Doctor::department() const {
    return m_department;
}

// 设置部门
void Doctor::setDepartment(const QString &department) {
    m_department = department;
}

// 获取工作日期
QDate Doctor::workDate() const {
    return m_workDate;
}

// 设置工作日期
void Doctor::setWorkDate(const QDate &date) {
    m_workDate = date;
}

// 获取工作时间段
DoctorWorkingHours Doctor::workTime() const {
    return m_worktime;
}

// 设置工作时间段
void Doctor::setWorkTime(const DoctorWorkingHours &workHours) {
    m_worktime = workHours;
}

// 将 Doctor 对象转换为 JSON 格式
QJsonObject Doctor::toJson() const {
    QJsonObject jsonObj = User::toJson();  // 调用基类的 toJson() 方法

    // 添加部门、工作日期和工作时间到 JSON 对象
    jsonObj["department"] = m_department;
    jsonObj["workDate"] = m_workDate.toString("yyyy-MM-dd");
    jsonObj["workStart"] = m_worktime.getStartTime().toString("HH:mm");
    jsonObj["workEnd"] = m_worktime.getEndTime().toString("HH:mm");

    return jsonObj;
}

// 从 JSON 格式恢复 Doctor 对象
void Doctor::fromJson(const QJsonObject &json) {
    User::fromJson(json);  // 调用基类的 fromJson() 方法

    // 恢复部门和工作日期
    m_department = json["department"].toString();
    m_workDate = QDate::fromString(json["workDate"].toString(), "yyyy-MM-dd");

    // 恢复工作时间段
    QTime start = QTime::fromString(json["workStart"].toString(), "HH:mm");
    QTime end = QTime::fromString(json["workEnd"].toString(), "HH:mm");
    m_worktime = DoctorWorkingHours(start, end);
}

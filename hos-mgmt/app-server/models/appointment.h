#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <QObject>
#include <QUuid>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>

// appointment实现预约类
class Appointment
{
    Q_GADGET
public:
    enum AppointmentStatus {
        Pending,   // 待确认
        Confirmed, // 已确认
        Canceled,  // 已取消
        Completed  // 已完成
    };
    Q_ENUM(AppointmentStatus)

    Appointment();

    QString id() const;
    void setId(const QString &id);

    QString patientId() const;
    void setPatientId(const QString &patientId);

    QString doctorId() const;
    void setDoctorId(const QString &doctorId);

    QDateTime appointmentDateTime() const;
    void setAppointmentDateTime(const QDateTime &dateTime);

    AppointmentStatus status() const;
    void setStatus(const AppointmentStatus &status);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject &json);

private:
    QString m_id;
    QString m_patientId;
    QString m_doctorId;
    QDateTime m_appointmentDateTime;
    AppointmentStatus m_status;
};

#endif // APPOINTMENT_H

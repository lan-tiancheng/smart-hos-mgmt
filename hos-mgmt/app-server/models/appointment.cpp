#include "models/appointment.h"

Appointment::Appointment()
    : m_id(QUuid::createUuid().toString(QUuid::WithoutBraces))
    , m_status(Pending)
{}

QString Appointment::id() const { return m_id; }
void Appointment::setId(const QString &id) { m_id = id; }

QString Appointment::patientId() const { return m_patientId; }
void Appointment::setPatientId(const QString &patientId) { m_patientId = patientId; }

QString Appointment::doctorId() const { return m_doctorId; }
void Appointment::setDoctorId(const QString &doctorId) { m_doctorId = doctorId; }

QDateTime Appointment::appointmentDateTime() const { return m_appointmentDateTime; }
void Appointment::setAppointmentDateTime(const QDateTime &dateTime) { m_appointmentDateTime = dateTime; }

Appointment::AppointmentStatus Appointment::status() const { return m_status; }
void Appointment::setStatus(const AppointmentStatus &status) { m_status = status; }

QString Appointment::info() const { return m_info; }
void Appointment::setInfo(const QString& info) { m_info = info; }

QJsonObject Appointment::toJson() const
{
    QJsonObject json;
    json["id"] = m_id;
    json["patient_id"] = m_patientId;
    json["doctor_id"] = m_doctorId;
    json["appointment_date_time"] = m_appointmentDateTime.toString(Qt::ISODate);
    json["status"] = (int)m_status;
    return json;
}

void Appointment::fromJson(const QJsonObject &json)
{
    if (json.contains("id")) m_id = json["id"].toString();
    if (json.contains("patient_id")) m_patientId = json["patient_id"].toString();
    if (json.contains("doctor_id")) m_doctorId = json["doctor_id"].toString();
    if (json.contains("appointment_date_time")) m_appointmentDateTime = QDateTime::fromString(json["appointment_date_time"].toString(), Qt::ISODate);
    if (json.contains("status")) m_status = (AppointmentStatus)json["status"].toInt();
}


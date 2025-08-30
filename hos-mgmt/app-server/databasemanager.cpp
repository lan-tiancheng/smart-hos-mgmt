#include "databasemanager.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMap>
#include <map>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    try {
        // 连接到本地的 Redis 服务器，默认端口为 6379
        m_redis = std::make_shared<sw::redis::Redis>("tcp://127.0.0.1:6379");
        qDebug() << "Redis connection successful.";
    } catch (const sw::redis::Error &e) {
        qDebug() << "Redis connection failed:" << e.what();
    }
}

bool DatabaseManager::createAppointment(const Appointment &appointment)
{
    // 在调用 m_redis 方法前，检查指针是否有效
    if (!m_redis) {
        qDebug() << "Redis client is not initialized.";
        return false;
    }

    const std::string appointmentKey = "appointment:" + appointment.id().toStdString();

    // 显式创建 std::map 对象来解决类型推断问题
    std::map<std::string, std::string> fields;
    fields["patient_id"] = appointment.patientId().toStdString();
    fields["doctor_id"] = appointment.doctorId().toStdString();
    fields["date_time"] = appointment.appointmentDateTime().toString(Qt::ISODate).toStdString();
    fields["status"] = QString::number(appointment.status()).toStdString();

    m_redis->hset(appointmentKey, fields.begin(), fields.end());

    // 使用 Redis 列表记录患者和医生的预约ID
    m_redis->lpush("patient:" + appointment.patientId().toStdString() + ":appointments", appointment.id().toStdString());
    m_redis->lpush("doctor:" + appointment.doctorId().toStdString() + ":appointments", appointment.id().toStdString());

    return true;
}

QList<Appointment> DatabaseManager::getAppointmentsByPatientId(const QString &patientId)
{
    QList<Appointment> appointments;
    if (!m_redis) {
        qDebug() << "Redis client is not initialized.";
        return appointments;
    }

    std::string patientAppointmentsKey = "patient:" + patientId.toStdString() + ":appointments";
    std::vector<std::string> appointmentIds;
    m_redis->lrange(patientAppointmentsKey, 0, -1, std::back_inserter(appointmentIds));

    for (const auto &id : appointmentIds) {
        std::map<std::string, std::string> fields;
        m_redis->hgetall("appointment:" + id, std::inserter(fields, fields.begin()));

        if (!fields.empty()) {
            Appointment app;
            app.setId(QString::fromStdString(id));
            app.setPatientId(QString::fromStdString(fields["patient_id"]));
            app.setDoctorId(QString::fromStdString(fields["doctor_id"]));
            app.setAppointmentDateTime(QDateTime::fromString(QString::fromStdString(fields["date_time"]), Qt::ISODate));
            app.setStatus((Appointment::AppointmentStatus)QString::fromStdString(fields["status"]).toInt());
            appointments.append(app);
        }
    }
    return appointments;
}

QList<Appointment> DatabaseManager::getAppointmentsByDoctorId(const QString &doctorId)
{
    QList<Appointment> appointments;
    if (!m_redis) {
        qDebug() << "Redis client is not initialized.";
        return appointments;
    }

    std::string doctorAppointmentsKey = "doctor:" + doctorId.toStdString() + ":appointments";
    std::vector<std::string> appointmentIds;
    m_redis->lrange(doctorAppointmentsKey, 0, -1, std::back_inserter(appointmentIds));

    for (const auto &id : appointmentIds) {
        std::map<std::string, std::string> fields;
        m_redis->hgetall("appointment:" + id, std::inserter(fields, fields.begin()));

        if (!fields.empty()) {
            Appointment app;
            app.setId(QString::fromStdString(id));
            app.setPatientId(QString::fromStdString(fields["patient_id"]));
            app.setDoctorId(QString::fromStdString(fields["doctor_id"]));
            app.setAppointmentDateTime(QDateTime::fromString(QString::fromStdString(fields["date_time"]), Qt::ISODate));
            app.setStatus((Appointment::AppointmentStatus)QString::fromStdString(fields["status"]).toInt());
            appointments.append(app);
        }
    }
    return appointments;
}

bool DatabaseManager::updateAppointmentStatus(const QString &appointmentId, Appointment::AppointmentStatus newStatus)
{
    if (!m_redis) {
        qDebug() << "Redis client is not initialized.";
        return false;
    }

    std::string appointmentKey = "appointment:" + appointmentId.toStdString();

    m_redis->hset(appointmentKey, "status", QString::number(newStatus).toStdString());

    return true;
}

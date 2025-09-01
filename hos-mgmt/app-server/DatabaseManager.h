#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QList>
#include <QVariant>
#include <QSqlDatabase>
#include "models/appointment.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);

    // 预约相关的公共方法
    bool createAppointment(const Appointment &appointment);
    QList<Appointment> getAppointmentsByPatientId(const QString &patientId);
    QList<Appointment> getAppointmentsByDoctorId(const QString &doctorId);
    bool updateAppointmentStatus(const QString &appointmentId, Appointment::AppointmentStatus newStatus);

private:
    QSqlDatabase m_db;
    void initDatabase();
};

#endif // DATABASEMANAGER_H

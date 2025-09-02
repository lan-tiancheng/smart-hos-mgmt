#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("hospital_server.db");
    if (!m_db.open()) {
        qWarning() << "Failed to open SQLite DB:" << m_db.lastError().text();
    }
    initDatabase();
}

void DatabaseManager::initDatabase()
{
    QSqlQuery query(m_db);
    query.exec("CREATE TABLE IF NOT EXISTS appointment ("
               "id TEXT PRIMARY KEY, "
               "patientId TEXT, "
               "doctorId TEXT, "
               "status INTEGER, "
               "info TEXT)");
}

bool DatabaseManager::createAppointment(const Appointment &appointment)
{
    QSqlQuery query(m_db);
    query.prepare("INSERT INTO appointment (id, patientId, doctorId, status, info) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(appointment.id());
    query.addBindValue(appointment.patientId());
    query.addBindValue(appointment.doctorId());
    query.addBindValue(static_cast<int>(appointment.status()));
    query.addBindValue(appointment.info());
    return query.exec();
}

QList<Appointment> DatabaseManager::getAppointmentsByPatientId(const QString &patientId)
{
    QList<Appointment> list;
    QSqlQuery query(m_db);
    query.prepare("SELECT id, doctorId, status, info FROM appointment WHERE patientId=?");
    query.addBindValue(patientId);
    if (query.exec()) {
        while (query.next()) {
            Appointment a;
            a.setId(query.value(0).toString());
            a.setPatientId(patientId);
            a.setDoctorId(query.value(1).toString());
            a.setStatus(static_cast<Appointment::AppointmentStatus>(query.value(2).toInt()));
            a.setInfo(query.value(3).toString());
            list.append(a);
        }
    }
    return list;
}

QList<Appointment> DatabaseManager::getAppointmentsByDoctorId(const QString &doctorId)
{
    QList<Appointment> list;
    QSqlQuery query(m_db);
    query.prepare("SELECT id, patientId, status, info FROM appointment WHERE doctorId=?");
    query.addBindValue(doctorId);
    if (query.exec()) {
        while (query.next()) {
            Appointment a;
            a.setId(query.value(0).toString());
            a.setPatientId(query.value(1).toString());
            a.setDoctorId(doctorId);
            a.setStatus(static_cast<Appointment::AppointmentStatus>(query.value(2).toInt()));
            a.setInfo(query.value(3).toString());
            list.append(a);
        }
    }
    return list;
}

bool DatabaseManager::updateAppointmentStatus(const QString &appointmentId, Appointment::AppointmentStatus newStatus)
{
    QSqlQuery query(m_db);
    query.prepare("UPDATE appointment SET status=? WHERE id=?");
    query.addBindValue(static_cast<int>(newStatus));
    query.addBindValue(appointmentId);
    return query.exec();
}

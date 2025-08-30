#include "databasemanager.h"

#include <QSqlQuery>
// 统一使用小写命名规范
// 数据库构造函数
DatabaseManager::DatabaseManager()
{
    m_mysqlDb = QSqlDatabase::addDatabase("QMYSQL");
    m_mysqlDb.setHostName("localhost"); // 你的数据库主机名
    m_mysqlDb.setDatabaseName("smartmedicaldb"); // 你的数据库名称
    m_mysqlDb.setUserName("root"); // 你的用户名
    m_mysqlDb.setPassword("1234"); // 你的密码

    if (!m_mysqlDb.open()) {
        qDebug() << "Database connection failed:" << m_mysqlDb.lastError().text();
    } else {
        qDebug() << "Database connection successful.";
    }
}

// 管理appiontment类
// ...
bool DatabaseManager::createAppointment(const Appointment &appointment)
{
    QSqlQuery query(m_mysqlDb);
    query.prepare("INSERT INTO appointments (id, patient_id, doctor_id, appointment_date_time, status) "
                  "VALUES (:id, :patient_id, :doctor_id, :appointment_date_time, :status)");
    query.bindValue(":id", appointment.id());
    query.bindValue(":patient_id", appointment.patientId());
    query.bindValue(":doctor_id", appointment.doctorId());
    query.bindValue(":appointment_date_time", appointment.appointmentDateTime());
    query.bindValue(":status", appointment.status());
    return query.exec();
}

QList<Appointment> DatabaseManager::getAppointmentsByPatientId(const QString &patientId)
{
    QList<Appointment> appointments;
    QSqlQuery query(m_mysqlDb);
    query.prepare("SELECT * FROM appointments WHERE patient_id = :patient_id");
    query.bindValue(":patient_id", patientId);

    if (query.exec()) {
        while (query.next()) {
            Appointment app;
            app.setId(query.value("id").toString());
            app.setPatientId(query.value("patient_id").toString());
            app.setDoctorId(query.value("doctor_id").toString());
            app.setAppointmentDateTime(query.value("appointment_date_time").toDateTime());
            app.setStatus((Appointment::AppointmentStatus)query.value("status").toInt());
            appointments.append(app);
        }
    }
    return appointments;
}

// TODO: 实现 getAppointmentsByDoctorId 和 updateAppointmentStatus 方法

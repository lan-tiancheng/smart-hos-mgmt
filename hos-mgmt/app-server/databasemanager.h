#include<models/appointment.h>
#include <QSqlError>
#include <QSqlDatabase>
// ...
class DatabaseManager : public QObject
{
    // ...
public:
    // constructor
    DatabaseManager();
    // ...
    bool createAppointment(const Appointment &appointment);
    QList<Appointment> getAppointmentsByPatientId(const QString &patientId);
    QList<Appointment> getAppointmentsByDoctorId(const QString &doctorId);
    bool updateAppointmentStatus(const QString &appointmentId, Appointment::AppointmentStatus newStatus);
    // ...

private:
    QSqlDatabase m_mysqlDb; // 在这里声明 m_mysqlD
};

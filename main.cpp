#include "DatabaseManager.h"
#include <QCoreApplication>
#include <QDebug>
#include "models/appointment.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 创建一个 DatabaseManager 实例
    DatabaseManager dbManager;

    // 创建一个测试用的预约对象
    Appointment testApp;
    testApp.setPatientId("patient-001");
    testApp.setDoctorId("doctor-A");
    testApp.setAppointmentDateTime(QDateTime::currentDateTime());
    testApp.setStatus(Appointment::Pending);

    // 调用 createAppointment 方法，并检查返回值
    bool success = dbManager.createAppointment(testApp);
    if (success) {
        qDebug() << "Appointment created successfully! ID:" << testApp.id();

        // 尝试通过 patient_id 查询
        QList<Appointment> appsByPatient = dbManager.getAppointmentsByPatientId("patient-001");
        qDebug() << "Found" << appsByPatient.size() << "appointments for patient-001.";

    } else {
        qDebug() << "Failed to create appointment.";
    }

    Server tcpServer;
    // 启动服务器监听
    tcpServer.startServer();

    return a.exec();
}

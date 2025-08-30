#include "databasemanager.h"
#include <QCoreApplication>
#include <QDebug>
#include "models/appointment.h"
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("/usr/lib/x86_64-linux-gnu/qt5/plugins");
    QCoreApplication a(argc, argv);

    // 1. 创建 DatabaseManager 实例，测试数据库连接
    DatabaseManager dbManager;

    // 2. 创建一个测试用的预约对象
    Appointment testAppointment;
    testAppointment.setPatientId("patient-123");
    testAppointment.setDoctorId("doctor-456");
    testAppointment.setAppointmentDateTime(QDateTime::currentDateTime());
    testAppointment.setStatus(Appointment::Pending);

    // 3. 调用 createAppointment 方法，并检查返回值
    bool success = dbManager.createAppointment(testAppointment);
    if (success) {
        qDebug() << "预约创建成功！ID为：" << testAppointment.id();
    } else {
        qDebug() << "预约创建失败！";
    }

    // 4. 调用 getAppointmentsByPatientId 方法进行查询测试
    QList<Appointment> appointments = dbManager.getAppointmentsByPatientId("patient-123");
    if (!appointments.isEmpty()) {
        qDebug() << "成功查找到" << appointments.count() << "个预约。";
    } else {
        qDebug() << "未查找到任何预约。";
    }

    return a.exec();
}

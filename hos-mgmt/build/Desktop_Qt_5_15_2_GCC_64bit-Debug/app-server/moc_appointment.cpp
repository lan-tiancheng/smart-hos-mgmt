/****************************************************************************
** Meta object code from reading C++ file 'appointment.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../app-server/models/appointment.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'appointment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Appointment_t {
    QByteArrayData data[6];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Appointment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Appointment_t qt_meta_stringdata_Appointment = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Appointment"
QT_MOC_LITERAL(1, 12, 17), // "AppointmentStatus"
QT_MOC_LITERAL(2, 30, 7), // "Pending"
QT_MOC_LITERAL(3, 38, 9), // "Confirmed"
QT_MOC_LITERAL(4, 48, 8), // "Canceled"
QT_MOC_LITERAL(5, 57, 9) // "Completed"

    },
    "Appointment\0AppointmentStatus\0Pending\0"
    "Confirmed\0Canceled\0Completed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Appointment[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       4,       // flags
       0,       // signalCount

 // enums: name, alias, flags, count, data
       1,    1, 0x0,    4,   19,

 // enum data: key, value
       2, uint(Appointment::Pending),
       3, uint(Appointment::Confirmed),
       4, uint(Appointment::Canceled),
       5, uint(Appointment::Completed),

       0        // eod
};

QT_INIT_METAOBJECT const QMetaObject Appointment::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_Appointment.data,
    qt_meta_data_Appointment,
    nullptr,
    nullptr,
    nullptr
} };

QT_WARNING_POP
QT_END_MOC_NAMESPACE

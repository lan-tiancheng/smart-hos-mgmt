/****************************************************************************
** Meta object code from reading C++ file 'user.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../models/user.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'user.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_User_t {
    QByteArrayData data[4];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_User_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_User_t qt_meta_stringdata_User = {
    {
QT_MOC_LITERAL(0, 0, 4), // "User"
QT_MOC_LITERAL(1, 5, 8), // "UserType"
QT_MOC_LITERAL(2, 14, 7), // "Patient"
QT_MOC_LITERAL(3, 22, 6) // "Doctor"

    },
    "User\0UserType\0Patient\0Doctor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_User[] = {

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
       1,    1, 0x0,    2,   19,

 // enum data: key, value
       2, uint(User::Patient),
       3, uint(User::Doctor),

       0        // eod
};

QT_INIT_METAOBJECT const QMetaObject User::staticMetaObject = { {
    nullptr,
    qt_meta_stringdata_User.data,
    qt_meta_data_User,
    nullptr,
    nullptr,
    nullptr
} };

QT_WARNING_POP
QT_END_MOC_NAMESPACE

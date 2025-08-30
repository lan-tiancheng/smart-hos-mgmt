/****************************************************************************
** Meta object code from reading C++ file 'logindialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PreProject/logindialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logindialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LoginDialog_t {
    QByteArrayData data[18];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoginDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoginDialog_t qt_meta_stringdata_LoginDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "LoginDialog"
QT_MOC_LITERAL(1, 12, 11), // "switchToReg"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "switchReset"
QT_MOC_LITERAL(4, 37, 15), // "sig_connect_tcp"
QT_MOC_LITERAL(5, 53, 10), // "ServerInfo"
QT_MOC_LITERAL(6, 64, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(7, 88, 15), // "slot_forget_pwd"
QT_MOC_LITERAL(8, 104, 21), // "slot_login_mod_finish"
QT_MOC_LITERAL(9, 126, 5), // "ReqId"
QT_MOC_LITERAL(10, 132, 2), // "id"
QT_MOC_LITERAL(11, 135, 3), // "res"
QT_MOC_LITERAL(12, 139, 9), // "ErrorCode"
QT_MOC_LITERAL(13, 149, 3), // "err"
QT_MOC_LITERAL(14, 153, 19), // "on_loginBtn_clicked"
QT_MOC_LITERAL(15, 173, 19), // "slot_tcp_con_finish"
QT_MOC_LITERAL(16, 193, 8), // "bsuccess"
QT_MOC_LITERAL(17, 202, 17) // "slot_login_failed"

    },
    "LoginDialog\0switchToReg\0\0switchReset\0"
    "sig_connect_tcp\0ServerInfo\0"
    "on_pushButton_2_clicked\0slot_forget_pwd\0"
    "slot_login_mod_finish\0ReqId\0id\0res\0"
    "ErrorCode\0err\0on_loginBtn_clicked\0"
    "slot_tcp_con_finish\0bsuccess\0"
    "slot_login_failed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoginDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    1,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    3,   66,    2, 0x08 /* Private */,
      14,    0,   73,    2, 0x08 /* Private */,
      15,    1,   74,    2, 0x08 /* Private */,
      17,    1,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QString, 0x80000000 | 12,   10,   11,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void LoginDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoginDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->switchToReg(); break;
        case 1: _t->switchReset(); break;
        case 2: _t->sig_connect_tcp((*reinterpret_cast< ServerInfo(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_2_clicked(); break;
        case 4: _t->slot_forget_pwd(); break;
        case 5: _t->slot_login_mod_finish((*reinterpret_cast< ReqId(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< ErrorCode(*)>(_a[3]))); break;
        case 6: _t->on_loginBtn_clicked(); break;
        case 7: _t->slot_tcp_con_finish((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->slot_login_failed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LoginDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::switchToReg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::switchReset)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LoginDialog::*)(ServerInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginDialog::sig_connect_tcp)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LoginDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_LoginDialog.data,
    qt_meta_data_LoginDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LoginDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoginDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LoginDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int LoginDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void LoginDialog::switchToReg()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LoginDialog::switchReset()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LoginDialog::sig_connect_tcp(ServerInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

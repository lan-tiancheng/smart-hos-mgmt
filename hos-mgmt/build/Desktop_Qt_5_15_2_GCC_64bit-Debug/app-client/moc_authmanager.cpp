/****************************************************************************
** Meta object code from reading C++ file 'authmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../app-client/src/authmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'authmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AuthManager_t {
    QByteArrayData data[30];
    char stringdata0[369];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AuthManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AuthManager_t qt_meta_stringdata_AuthManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AuthManager"
QT_MOC_LITERAL(1, 12, 12), // "loginSuccess"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "UserType"
QT_MOC_LITERAL(4, 35, 8), // "userType"
QT_MOC_LITERAL(5, 44, 11), // "loginFailed"
QT_MOC_LITERAL(6, 56, 6), // "reason"
QT_MOC_LITERAL(7, 63, 15), // "registerSuccess"
QT_MOC_LITERAL(8, 79, 14), // "registerFailed"
QT_MOC_LITERAL(9, 94, 22), // "isAuthenticatedChanged"
QT_MOC_LITERAL(10, 117, 24), // "remainingAttemptsChanged"
QT_MOC_LITERAL(11, 142, 11), // "onReadyRead"
QT_MOC_LITERAL(12, 154, 11), // "onConnected"
QT_MOC_LITERAL(13, 166, 15), // "onErrorOccurred"
QT_MOC_LITERAL(14, 182, 23), // "QTcpSocket::SocketError"
QT_MOC_LITERAL(15, 206, 11), // "socketError"
QT_MOC_LITERAL(16, 218, 12), // "requestLogin"
QT_MOC_LITERAL(17, 231, 8), // "username"
QT_MOC_LITERAL(18, 240, 8), // "password"
QT_MOC_LITERAL(19, 249, 15), // "requestRegister"
QT_MOC_LITERAL(20, 265, 5), // "phone"
QT_MOC_LITERAL(21, 271, 7), // "address"
QT_MOC_LITERAL(22, 279, 3), // "age"
QT_MOC_LITERAL(23, 283, 6), // "gender"
QT_MOC_LITERAL(24, 290, 20), // "setRemainingAttempts"
QT_MOC_LITERAL(25, 311, 8), // "attempts"
QT_MOC_LITERAL(26, 320, 15), // "isAuthenticated"
QT_MOC_LITERAL(27, 336, 17), // "remainingAttempts"
QT_MOC_LITERAL(28, 354, 7), // "Patient"
QT_MOC_LITERAL(29, 362, 6) // "Doctor"

    },
    "AuthManager\0loginSuccess\0\0UserType\0"
    "userType\0loginFailed\0reason\0registerSuccess\0"
    "registerFailed\0isAuthenticatedChanged\0"
    "remainingAttemptsChanged\0onReadyRead\0"
    "onConnected\0onErrorOccurred\0"
    "QTcpSocket::SocketError\0socketError\0"
    "requestLogin\0username\0password\0"
    "requestRegister\0phone\0address\0age\0"
    "gender\0setRemainingAttempts\0attempts\0"
    "isAuthenticated\0remainingAttempts\0"
    "Patient\0Doctor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuthManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       2,  116, // properties
       1,  124, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,
       7,    0,   80,    2, 0x06 /* Public */,
       8,    1,   81,    2, 0x06 /* Public */,
       9,    0,   84,    2, 0x06 /* Public */,
      10,    0,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   86,    2, 0x08 /* Private */,
      12,    0,   87,    2, 0x08 /* Private */,
      13,    1,   88,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      16,    3,   91,    2, 0x02 /* Public */,
      19,    7,   98,    2, 0x02 /* Public */,
      24,    1,  113,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,    4,   17,   18,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    4,   17,   18,   20,   21,   22,   23,
    QMetaType::Void, QMetaType::Int,   25,

 // properties: name, type, flags
      26, QMetaType::Bool, 0x00495001,
      27, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       4,
       5,

 // enums: name, alias, flags, count, data
       3,    3, 0x0,    2,  129,

 // enum data: key, value
      28, uint(AuthManager::Patient),
      29, uint(AuthManager::Doctor),

       0        // eod
};

void AuthManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AuthManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginSuccess((*reinterpret_cast< UserType(*)>(_a[1]))); break;
        case 1: _t->loginFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->registerSuccess(); break;
        case 3: _t->registerFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->isAuthenticatedChanged(); break;
        case 5: _t->remainingAttemptsChanged(); break;
        case 6: _t->onReadyRead(); break;
        case 7: _t->onConnected(); break;
        case 8: _t->onErrorOccurred((*reinterpret_cast< QTcpSocket::SocketError(*)>(_a[1]))); break;
        case 9: _t->requestLogin((*reinterpret_cast< UserType(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 10: _t->requestRegister((*reinterpret_cast< UserType(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7]))); break;
        case 11: _t->setRemainingAttempts((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AuthManager::*)(UserType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::loginSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::loginFailed)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::registerSuccess)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::registerFailed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::isAuthenticatedChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::remainingAttemptsChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AuthManager *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isAuthenticated(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->remainingAttempts(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AuthManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AuthManager.data,
    qt_meta_data_AuthManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AuthManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AuthManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AuthManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AuthManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AuthManager::loginSuccess(UserType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AuthManager::loginFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AuthManager::registerSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AuthManager::registerFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AuthManager::isAuthenticatedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void AuthManager::remainingAttemptsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

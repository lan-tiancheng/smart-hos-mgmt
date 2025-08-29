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
    QByteArrayData data[43];
    char stringdata0[509];
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
QT_MOC_LITERAL(3, 26, 6), // "userId"
QT_MOC_LITERAL(4, 33, 8), // "userType"
QT_MOC_LITERAL(5, 42, 8), // "UserType"
QT_MOC_LITERAL(6, 51, 11), // "loginFailed"
QT_MOC_LITERAL(7, 63, 6), // "reason"
QT_MOC_LITERAL(8, 70, 15), // "registerSuccess"
QT_MOC_LITERAL(9, 86, 14), // "registerFailed"
QT_MOC_LITERAL(10, 101, 19), // "healthSubmitSuccess"
QT_MOC_LITERAL(11, 121, 3), // "bmi"
QT_MOC_LITERAL(12, 125, 9), // "lungLevel"
QT_MOC_LITERAL(13, 135, 7), // "bpLevel"
QT_MOC_LITERAL(14, 143, 7), // "overall"
QT_MOC_LITERAL(15, 151, 18), // "healthSubmitFailed"
QT_MOC_LITERAL(16, 170, 22), // "isAuthenticatedChanged"
QT_MOC_LITERAL(17, 193, 24), // "remainingAttemptsChanged"
QT_MOC_LITERAL(18, 218, 11), // "onReadyRead"
QT_MOC_LITERAL(19, 230, 11), // "onConnected"
QT_MOC_LITERAL(20, 242, 15), // "onErrorOccurred"
QT_MOC_LITERAL(21, 258, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(22, 287, 11), // "socketError"
QT_MOC_LITERAL(23, 299, 12), // "requestLogin"
QT_MOC_LITERAL(24, 312, 8), // "username"
QT_MOC_LITERAL(25, 321, 8), // "password"
QT_MOC_LITERAL(26, 330, 15), // "requestRegister"
QT_MOC_LITERAL(27, 346, 5), // "phone"
QT_MOC_LITERAL(28, 352, 7), // "address"
QT_MOC_LITERAL(29, 360, 3), // "age"
QT_MOC_LITERAL(30, 364, 6), // "gender"
QT_MOC_LITERAL(31, 371, 16), // "submitHealthData"
QT_MOC_LITERAL(32, 388, 8), // "heightCm"
QT_MOC_LITERAL(33, 397, 8), // "weightKg"
QT_MOC_LITERAL(34, 406, 6), // "lungMl"
QT_MOC_LITERAL(35, 413, 2), // "bp"
QT_MOC_LITERAL(36, 416, 20), // "setRemainingAttempts"
QT_MOC_LITERAL(37, 437, 8), // "attempts"
QT_MOC_LITERAL(38, 446, 15), // "isAuthenticated"
QT_MOC_LITERAL(39, 462, 17), // "remainingAttempts"
QT_MOC_LITERAL(40, 480, 13), // "currentUserId"
QT_MOC_LITERAL(41, 494, 7), // "Patient"
QT_MOC_LITERAL(42, 502, 6) // "Doctor"

    },
    "AuthManager\0loginSuccess\0\0userId\0"
    "userType\0UserType\0loginFailed\0reason\0"
    "registerSuccess\0registerFailed\0"
    "healthSubmitSuccess\0bmi\0lungLevel\0"
    "bpLevel\0overall\0healthSubmitFailed\0"
    "isAuthenticatedChanged\0remainingAttemptsChanged\0"
    "onReadyRead\0onConnected\0onErrorOccurred\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "requestLogin\0username\0password\0"
    "requestRegister\0phone\0address\0age\0"
    "gender\0submitHealthData\0heightCm\0"
    "weightKg\0lungMl\0bp\0setRemainingAttempts\0"
    "attempts\0isAuthenticated\0remainingAttempts\0"
    "currentUserId\0Patient\0Doctor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuthManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       3,  192, // properties
       1,  204, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  104,    2, 0x06 /* Public */,
       1,    1,  109,    2, 0x06 /* Public */,
       6,    1,  112,    2, 0x06 /* Public */,
       8,    0,  115,    2, 0x06 /* Public */,
       9,    1,  116,    2, 0x06 /* Public */,
      10,    4,  119,    2, 0x06 /* Public */,
      15,    1,  128,    2, 0x06 /* Public */,
      16,    0,  131,    2, 0x06 /* Public */,
      17,    0,  132,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    0,  133,    2, 0x08 /* Private */,
      19,    0,  134,    2, 0x08 /* Private */,
      20,    1,  135,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      23,    3,  138,    2, 0x02 /* Public */,
      26,    7,  145,    2, 0x02 /* Public */,
      23,    2,  160,    2, 0x02 /* Public */,
      26,    7,  165,    2, 0x02 /* Public */,
      31,    4,  180,    2, 0x02 /* Public */,
      36,    1,  189,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, 0x80000000 | 5,    4,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString, QMetaType::QString,    4,   24,   25,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    4,   24,   25,   27,   28,   29,   30,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   24,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    4,   24,   25,   27,   28,   29,   30,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::QString,   32,   33,   34,   35,
    QMetaType::Void, QMetaType::Int,   37,

 // properties: name, type, flags
      38, QMetaType::Bool, 0x00495001,
      39, QMetaType::Int, 0x00495001,
      40, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       7,
       8,
       7,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    2,  209,

 // enum data: key, value
      41, uint(AuthManager::Patient),
      42, uint(AuthManager::Doctor),

       0        // eod
};

void AuthManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AuthManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginSuccess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->loginSuccess((*reinterpret_cast< UserType(*)>(_a[1]))); break;
        case 2: _t->loginFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->registerSuccess(); break;
        case 4: _t->registerFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->healthSubmitSuccess((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 6: _t->healthSubmitFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->isAuthenticatedChanged(); break;
        case 8: _t->remainingAttemptsChanged(); break;
        case 9: _t->onReadyRead(); break;
        case 10: _t->onConnected(); break;
        case 11: _t->onErrorOccurred((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 12: _t->requestLogin((*reinterpret_cast< UserType(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 13: _t->requestRegister((*reinterpret_cast< UserType(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7]))); break;
        case 14: _t->requestLogin((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 15: _t->requestRegister((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7]))); break;
        case 16: _t->submitHealthData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 17: _t->setRemainingAttempts((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AuthManager::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::loginSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(UserType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::loginSuccess)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::loginFailed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::registerSuccess)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::registerFailed)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(double , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::healthSubmitSuccess)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::healthSubmitFailed)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::isAuthenticatedChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::remainingAttemptsChanged)) {
                *result = 8;
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
        case 2: *reinterpret_cast< int*>(_v) = _t->currentUserId(); break;
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
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AuthManager::loginSuccess(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AuthManager::loginSuccess(UserType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AuthManager::loginFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AuthManager::registerSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AuthManager::registerFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AuthManager::healthSubmitSuccess(double _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AuthManager::healthSubmitFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AuthManager::isAuthenticatedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void AuthManager::remainingAttemptsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

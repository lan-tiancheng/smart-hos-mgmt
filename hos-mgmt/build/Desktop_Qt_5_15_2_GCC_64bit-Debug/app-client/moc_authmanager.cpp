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
    QByteArrayData data[54];
    char stringdata0[697];
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
QT_MOC_LITERAL(4, 33, 21), // "AuthManager::UserType"
QT_MOC_LITERAL(5, 55, 8), // "userType"
QT_MOC_LITERAL(6, 64, 11), // "loginFailed"
QT_MOC_LITERAL(7, 76, 6), // "reason"
QT_MOC_LITERAL(8, 83, 15), // "registerSuccess"
QT_MOC_LITERAL(9, 99, 14), // "registerFailed"
QT_MOC_LITERAL(10, 114, 19), // "healthSubmitSuccess"
QT_MOC_LITERAL(11, 134, 3), // "bmi"
QT_MOC_LITERAL(12, 138, 9), // "lungLevel"
QT_MOC_LITERAL(13, 148, 7), // "bpLevel"
QT_MOC_LITERAL(14, 156, 7), // "overall"
QT_MOC_LITERAL(15, 164, 18), // "healthSubmitFailed"
QT_MOC_LITERAL(16, 183, 22), // "isAuthenticatedChanged"
QT_MOC_LITERAL(17, 206, 24), // "remainingAttemptsChanged"
QT_MOC_LITERAL(18, 231, 20), // "currentUserIdChanged"
QT_MOC_LITERAL(19, 252, 22), // "currentUserTypeChanged"
QT_MOC_LITERAL(20, 275, 11), // "onConnected"
QT_MOC_LITERAL(21, 287, 15), // "onErrorOccurred"
QT_MOC_LITERAL(22, 303, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(23, 332, 11), // "socketError"
QT_MOC_LITERAL(24, 344, 11), // "onReadyRead"
QT_MOC_LITERAL(25, 356, 19), // "onHttpLoginFinished"
QT_MOC_LITERAL(26, 376, 14), // "QNetworkReply*"
QT_MOC_LITERAL(27, 391, 5), // "reply"
QT_MOC_LITERAL(28, 397, 22), // "onHttpRegisterFinished"
QT_MOC_LITERAL(29, 420, 26), // "onHttpHealthSubmitFinished"
QT_MOC_LITERAL(30, 447, 10), // "setApiBase"
QT_MOC_LITERAL(31, 458, 3), // "url"
QT_MOC_LITERAL(32, 462, 12), // "requestLogin"
QT_MOC_LITERAL(33, 475, 8), // "username"
QT_MOC_LITERAL(34, 484, 8), // "password"
QT_MOC_LITERAL(35, 493, 15), // "requestRegister"
QT_MOC_LITERAL(36, 509, 5), // "phone"
QT_MOC_LITERAL(37, 515, 7), // "address"
QT_MOC_LITERAL(38, 523, 3), // "age"
QT_MOC_LITERAL(39, 527, 6), // "gender"
QT_MOC_LITERAL(40, 534, 16), // "submitHealthData"
QT_MOC_LITERAL(41, 551, 8), // "heightCm"
QT_MOC_LITERAL(42, 560, 8), // "weightKg"
QT_MOC_LITERAL(43, 569, 6), // "lungMl"
QT_MOC_LITERAL(44, 576, 2), // "bp"
QT_MOC_LITERAL(45, 579, 20), // "setRemainingAttempts"
QT_MOC_LITERAL(46, 600, 8), // "attempts"
QT_MOC_LITERAL(47, 609, 15), // "isAuthenticated"
QT_MOC_LITERAL(48, 625, 17), // "remainingAttempts"
QT_MOC_LITERAL(49, 643, 13), // "currentUserId"
QT_MOC_LITERAL(50, 657, 15), // "currentUserType"
QT_MOC_LITERAL(51, 673, 8), // "UserType"
QT_MOC_LITERAL(52, 682, 7), // "Patient"
QT_MOC_LITERAL(53, 690, 6) // "Doctor"

    },
    "AuthManager\0loginSuccess\0\0userId\0"
    "AuthManager::UserType\0userType\0"
    "loginFailed\0reason\0registerSuccess\0"
    "registerFailed\0healthSubmitSuccess\0"
    "bmi\0lungLevel\0bpLevel\0overall\0"
    "healthSubmitFailed\0isAuthenticatedChanged\0"
    "remainingAttemptsChanged\0currentUserIdChanged\0"
    "currentUserTypeChanged\0onConnected\0"
    "onErrorOccurred\0QAbstractSocket::SocketError\0"
    "socketError\0onReadyRead\0onHttpLoginFinished\0"
    "QNetworkReply*\0reply\0onHttpRegisterFinished\0"
    "onHttpHealthSubmitFinished\0setApiBase\0"
    "url\0requestLogin\0username\0password\0"
    "requestRegister\0phone\0address\0age\0"
    "gender\0submitHealthData\0heightCm\0"
    "weightKg\0lungMl\0bp\0setRemainingAttempts\0"
    "attempts\0isAuthenticated\0remainingAttempts\0"
    "currentUserId\0currentUserType\0UserType\0"
    "Patient\0Doctor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuthManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       4,  196, // properties
       1,  212, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  119,    2, 0x06 /* Public */,
       6,    1,  124,    2, 0x06 /* Public */,
       8,    0,  127,    2, 0x06 /* Public */,
       9,    1,  128,    2, 0x06 /* Public */,
      10,    4,  131,    2, 0x06 /* Public */,
      15,    1,  140,    2, 0x06 /* Public */,
      16,    0,  143,    2, 0x06 /* Public */,
      17,    0,  144,    2, 0x06 /* Public */,
      18,    0,  145,    2, 0x06 /* Public */,
      19,    0,  146,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    0,  147,    2, 0x08 /* Private */,
      21,    1,  148,    2, 0x08 /* Private */,
      24,    0,  151,    2, 0x08 /* Private */,
      25,    1,  152,    2, 0x08 /* Private */,
      28,    1,  155,    2, 0x08 /* Private */,
      29,    1,  158,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      30,    1,  161,    2, 0x02 /* Public */,
      32,    2,  164,    2, 0x02 /* Public */,
      35,    7,  169,    2, 0x02 /* Public */,
      40,    4,  184,    2, 0x02 /* Public */,
      45,    1,  193,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, 0x80000000 | 26,   27,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   31,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   33,   34,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    5,   33,   34,   36,   37,   38,   39,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::QString,   41,   42,   43,   44,
    QMetaType::Void, QMetaType::Int,   46,

 // properties: name, type, flags
      47, QMetaType::Bool, 0x00495001,
      48, QMetaType::Int, 0x00495001,
      49, QMetaType::Int, 0x00495001,
      50, 0x80000000 | 51, 0x00495009,

 // properties: notify_signal_id
       6,
       7,
       8,
       9,

 // enums: name, alias, flags, count, data
      51,   51, 0x0,    2,  217,

 // enum data: key, value
      52, uint(AuthManager::Patient),
      53, uint(AuthManager::Doctor),

       0        // eod
};

void AuthManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AuthManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginSuccess((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< AuthManager::UserType(*)>(_a[2]))); break;
        case 1: _t->loginFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->registerSuccess(); break;
        case 3: _t->registerFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->healthSubmitSuccess((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 5: _t->healthSubmitFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->isAuthenticatedChanged(); break;
        case 7: _t->remainingAttemptsChanged(); break;
        case 8: _t->currentUserIdChanged(); break;
        case 9: _t->currentUserTypeChanged(); break;
        case 10: _t->onConnected(); break;
        case 11: _t->onErrorOccurred((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 12: _t->onReadyRead(); break;
        case 13: _t->onHttpLoginFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 14: _t->onHttpRegisterFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 15: _t->onHttpHealthSubmitFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 16: _t->setApiBase((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 17: _t->requestLogin((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 18: _t->requestRegister((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7]))); break;
        case 19: _t->submitHealthData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 20: _t->setRemainingAttempts((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AuthManager::*)(int , AuthManager::UserType );
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
            using _t = void (AuthManager::*)(double , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::healthSubmitSuccess)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::healthSubmitFailed)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::isAuthenticatedChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::remainingAttemptsChanged)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::currentUserIdChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::currentUserTypeChanged)) {
                *result = 9;
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
        case 3: *reinterpret_cast< UserType*>(_v) = _t->currentUserType(); break;
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
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AuthManager::loginSuccess(int _t1, AuthManager::UserType _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
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
void AuthManager::healthSubmitSuccess(double _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AuthManager::healthSubmitFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AuthManager::isAuthenticatedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void AuthManager::remainingAttemptsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void AuthManager::currentUserIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void AuthManager::currentUserTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

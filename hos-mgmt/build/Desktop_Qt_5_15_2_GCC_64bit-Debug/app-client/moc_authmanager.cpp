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
    QByteArrayData data[52];
    char stringdata0[658];
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
QT_MOC_LITERAL(19, 252, 11), // "onConnected"
QT_MOC_LITERAL(20, 264, 15), // "onErrorOccurred"
QT_MOC_LITERAL(21, 280, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(22, 309, 11), // "socketError"
QT_MOC_LITERAL(23, 321, 11), // "onReadyRead"
QT_MOC_LITERAL(24, 333, 19), // "onHttpLoginFinished"
QT_MOC_LITERAL(25, 353, 14), // "QNetworkReply*"
QT_MOC_LITERAL(26, 368, 5), // "reply"
QT_MOC_LITERAL(27, 374, 22), // "onHttpRegisterFinished"
QT_MOC_LITERAL(28, 397, 26), // "onHttpHealthSubmitFinished"
QT_MOC_LITERAL(29, 424, 10), // "setApiBase"
QT_MOC_LITERAL(30, 435, 3), // "url"
QT_MOC_LITERAL(31, 439, 12), // "requestLogin"
QT_MOC_LITERAL(32, 452, 8), // "username"
QT_MOC_LITERAL(33, 461, 8), // "password"
QT_MOC_LITERAL(34, 470, 15), // "requestRegister"
QT_MOC_LITERAL(35, 486, 5), // "phone"
QT_MOC_LITERAL(36, 492, 7), // "address"
QT_MOC_LITERAL(37, 500, 3), // "age"
QT_MOC_LITERAL(38, 504, 6), // "gender"
QT_MOC_LITERAL(39, 511, 16), // "submitHealthData"
QT_MOC_LITERAL(40, 528, 8), // "heightCm"
QT_MOC_LITERAL(41, 537, 8), // "weightKg"
QT_MOC_LITERAL(42, 546, 6), // "lungMl"
QT_MOC_LITERAL(43, 553, 2), // "bp"
QT_MOC_LITERAL(44, 556, 20), // "setRemainingAttempts"
QT_MOC_LITERAL(45, 577, 8), // "attempts"
QT_MOC_LITERAL(46, 586, 15), // "isAuthenticated"
QT_MOC_LITERAL(47, 602, 17), // "remainingAttempts"
QT_MOC_LITERAL(48, 620, 13), // "currentUserId"
QT_MOC_LITERAL(49, 634, 8), // "UserType"
QT_MOC_LITERAL(50, 643, 7), // "Patient"
QT_MOC_LITERAL(51, 651, 6) // "Doctor"

    },
    "AuthManager\0loginSuccess\0\0userId\0"
    "AuthManager::UserType\0userType\0"
    "loginFailed\0reason\0registerSuccess\0"
    "registerFailed\0healthSubmitSuccess\0"
    "bmi\0lungLevel\0bpLevel\0overall\0"
    "healthSubmitFailed\0isAuthenticatedChanged\0"
    "remainingAttemptsChanged\0currentUserIdChanged\0"
    "onConnected\0onErrorOccurred\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "onReadyRead\0onHttpLoginFinished\0"
    "QNetworkReply*\0reply\0onHttpRegisterFinished\0"
    "onHttpHealthSubmitFinished\0setApiBase\0"
    "url\0requestLogin\0username\0password\0"
    "requestRegister\0phone\0address\0age\0"
    "gender\0submitHealthData\0heightCm\0"
    "weightKg\0lungMl\0bp\0setRemainingAttempts\0"
    "attempts\0isAuthenticated\0remainingAttempts\0"
    "currentUserId\0UserType\0Patient\0Doctor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuthManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       3,  190, // properties
       1,  202, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  114,    2, 0x06 /* Public */,
       6,    1,  119,    2, 0x06 /* Public */,
       8,    0,  122,    2, 0x06 /* Public */,
       9,    1,  123,    2, 0x06 /* Public */,
      10,    4,  126,    2, 0x06 /* Public */,
      15,    1,  135,    2, 0x06 /* Public */,
      16,    0,  138,    2, 0x06 /* Public */,
      17,    0,  139,    2, 0x06 /* Public */,
      18,    0,  140,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    0,  141,    2, 0x08 /* Private */,
      20,    1,  142,    2, 0x08 /* Private */,
      23,    0,  145,    2, 0x08 /* Private */,
      24,    1,  146,    2, 0x08 /* Private */,
      27,    1,  149,    2, 0x08 /* Private */,
      28,    1,  152,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      29,    1,  155,    2, 0x02 /* Public */,
      31,    2,  158,    2, 0x02 /* Public */,
      34,    7,  163,    2, 0x02 /* Public */,
      39,    4,  178,    2, 0x02 /* Public */,
      44,    1,  187,    2, 0x02 /* Public */,

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

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, 0x80000000 | 25,   26,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   32,   33,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    5,   32,   33,   35,   36,   37,   38,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::QString,   40,   41,   42,   43,
    QMetaType::Void, QMetaType::Int,   45,

 // properties: name, type, flags
      46, QMetaType::Bool, 0x00495001,
      47, QMetaType::Int, 0x00495001,
      48, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       6,
       7,
       8,

 // enums: name, alias, flags, count, data
      49,   49, 0x0,    2,  207,

 // enum data: key, value
      50, uint(AuthManager::Patient),
      51, uint(AuthManager::Doctor),

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
        case 9: _t->onConnected(); break;
        case 10: _t->onErrorOccurred((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 11: _t->onReadyRead(); break;
        case 12: _t->onHttpLoginFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 13: _t->onHttpRegisterFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 14: _t->onHttpHealthSubmitFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 15: _t->setApiBase((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->requestLogin((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 17: _t->requestRegister((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7]))); break;
        case 18: _t->submitHealthData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 19: _t->setRemainingAttempts((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
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
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

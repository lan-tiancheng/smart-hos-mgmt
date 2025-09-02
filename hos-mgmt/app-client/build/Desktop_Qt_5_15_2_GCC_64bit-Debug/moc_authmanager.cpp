/****************************************************************************
** Meta object code from reading C++ file 'authmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/authmanager.h"
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
    QByteArrayData data[61];
    char stringdata0[808];
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
QT_MOC_LITERAL(16, 183, 24), // "updatePatientInfoSuccess"
QT_MOC_LITERAL(17, 208, 23), // "updatePatientInfoFailed"
QT_MOC_LITERAL(18, 232, 22), // "isAuthenticatedChanged"
QT_MOC_LITERAL(19, 255, 24), // "remainingAttemptsChanged"
QT_MOC_LITERAL(20, 280, 20), // "currentUserIdChanged"
QT_MOC_LITERAL(21, 301, 22), // "currentUserTypeChanged"
QT_MOC_LITERAL(22, 324, 11), // "onConnected"
QT_MOC_LITERAL(23, 336, 15), // "onErrorOccurred"
QT_MOC_LITERAL(24, 352, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(25, 381, 11), // "socketError"
QT_MOC_LITERAL(26, 393, 11), // "onReadyRead"
QT_MOC_LITERAL(27, 405, 19), // "onHttpLoginFinished"
QT_MOC_LITERAL(28, 425, 14), // "QNetworkReply*"
QT_MOC_LITERAL(29, 440, 5), // "reply"
QT_MOC_LITERAL(30, 446, 22), // "onHttpRegisterFinished"
QT_MOC_LITERAL(31, 469, 26), // "onHttpHealthSubmitFinished"
QT_MOC_LITERAL(32, 496, 10), // "setApiBase"
QT_MOC_LITERAL(33, 507, 3), // "url"
QT_MOC_LITERAL(34, 511, 12), // "requestLogin"
QT_MOC_LITERAL(35, 524, 10), // "profession"
QT_MOC_LITERAL(36, 535, 8), // "username"
QT_MOC_LITERAL(37, 544, 8), // "password"
QT_MOC_LITERAL(38, 553, 15), // "requestRegister"
QT_MOC_LITERAL(39, 569, 5), // "phone"
QT_MOC_LITERAL(40, 575, 7), // "address"
QT_MOC_LITERAL(41, 583, 3), // "age"
QT_MOC_LITERAL(42, 587, 6), // "gender"
QT_MOC_LITERAL(43, 594, 16), // "submitHealthData"
QT_MOC_LITERAL(44, 611, 8), // "heightCm"
QT_MOC_LITERAL(45, 620, 8), // "weightKg"
QT_MOC_LITERAL(46, 629, 6), // "lungMl"
QT_MOC_LITERAL(47, 636, 2), // "bp"
QT_MOC_LITERAL(48, 639, 20), // "setRemainingAttempts"
QT_MOC_LITERAL(49, 660, 8), // "attempts"
QT_MOC_LITERAL(50, 669, 14), // "getPatientInfo"
QT_MOC_LITERAL(51, 684, 8), // "QJSValue"
QT_MOC_LITERAL(52, 693, 8), // "callback"
QT_MOC_LITERAL(53, 702, 17), // "updatePatientInfo"
QT_MOC_LITERAL(54, 720, 15), // "isAuthenticated"
QT_MOC_LITERAL(55, 736, 17), // "remainingAttempts"
QT_MOC_LITERAL(56, 754, 13), // "currentUserId"
QT_MOC_LITERAL(57, 768, 15), // "currentUserType"
QT_MOC_LITERAL(58, 784, 8), // "UserType"
QT_MOC_LITERAL(59, 793, 7), // "Patient"
QT_MOC_LITERAL(60, 801, 6) // "Doctor"

    },
    "AuthManager\0loginSuccess\0\0userId\0"
    "AuthManager::UserType\0userType\0"
    "loginFailed\0reason\0registerSuccess\0"
    "registerFailed\0healthSubmitSuccess\0"
    "bmi\0lungLevel\0bpLevel\0overall\0"
    "healthSubmitFailed\0updatePatientInfoSuccess\0"
    "updatePatientInfoFailed\0isAuthenticatedChanged\0"
    "remainingAttemptsChanged\0currentUserIdChanged\0"
    "currentUserTypeChanged\0onConnected\0"
    "onErrorOccurred\0QAbstractSocket::SocketError\0"
    "socketError\0onReadyRead\0onHttpLoginFinished\0"
    "QNetworkReply*\0reply\0onHttpRegisterFinished\0"
    "onHttpHealthSubmitFinished\0setApiBase\0"
    "url\0requestLogin\0profession\0username\0"
    "password\0requestRegister\0phone\0address\0"
    "age\0gender\0submitHealthData\0heightCm\0"
    "weightKg\0lungMl\0bp\0setRemainingAttempts\0"
    "attempts\0getPatientInfo\0QJSValue\0"
    "callback\0updatePatientInfo\0isAuthenticated\0"
    "remainingAttempts\0currentUserId\0"
    "currentUserType\0UserType\0Patient\0"
    "Doctor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuthManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       4,  238, // properties
       1,  254, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  139,    2, 0x06 /* Public */,
       6,    1,  144,    2, 0x06 /* Public */,
       8,    0,  147,    2, 0x06 /* Public */,
       9,    1,  148,    2, 0x06 /* Public */,
      10,    4,  151,    2, 0x06 /* Public */,
      15,    1,  160,    2, 0x06 /* Public */,
      16,    0,  163,    2, 0x06 /* Public */,
      17,    1,  164,    2, 0x06 /* Public */,
      18,    0,  167,    2, 0x06 /* Public */,
      19,    0,  168,    2, 0x06 /* Public */,
      20,    0,  169,    2, 0x06 /* Public */,
      21,    0,  170,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    0,  171,    2, 0x08 /* Private */,
      23,    1,  172,    2, 0x08 /* Private */,
      26,    0,  175,    2, 0x08 /* Private */,
      27,    1,  176,    2, 0x08 /* Private */,
      30,    1,  179,    2, 0x08 /* Private */,
      31,    1,  182,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      32,    1,  185,    2, 0x02 /* Public */,
      34,    3,  188,    2, 0x02 /* Public */,
      38,    7,  195,    2, 0x02 /* Public */,
      43,    4,  210,    2, 0x02 /* Public */,
      48,    1,  219,    2, 0x02 /* Public */,
      50,    1,  222,    2, 0x02 /* Public */,
      53,    6,  225,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, 0x80000000 | 28,   29,
    QMetaType::Void, 0x80000000 | 28,   29,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   35,   36,   37,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,   35,   36,   37,   39,   40,   41,   42,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::QString,   44,   45,   46,   47,
    QMetaType::Void, QMetaType::Int,   49,
    QMetaType::Void, 0x80000000 | 51,   52,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, 0x80000000 | 51,   36,   39,   40,   41,   42,   52,

 // properties: name, type, flags
      54, QMetaType::Bool, 0x00495001,
      55, QMetaType::Int, 0x00495001,
      56, QMetaType::Int, 0x00495001,
      57, 0x80000000 | 58, 0x00495009,

 // properties: notify_signal_id
       8,
       9,
      10,
      11,

 // enums: name, alias, flags, count, data
      58,   58, 0x0,    2,  259,

 // enum data: key, value
      59, uint(AuthManager::Patient),
      60, uint(AuthManager::Doctor),

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
        case 6: _t->updatePatientInfoSuccess(); break;
        case 7: _t->updatePatientInfoFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->isAuthenticatedChanged(); break;
        case 9: _t->remainingAttemptsChanged(); break;
        case 10: _t->currentUserIdChanged(); break;
        case 11: _t->currentUserTypeChanged(); break;
        case 12: _t->onConnected(); break;
        case 13: _t->onErrorOccurred((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 14: _t->onReadyRead(); break;
        case 15: _t->onHttpLoginFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 16: _t->onHttpRegisterFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 17: _t->onHttpHealthSubmitFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 18: _t->setApiBase((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 19: _t->requestLogin((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 20: _t->requestRegister((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7]))); break;
        case 21: _t->submitHealthData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 22: _t->setRemainingAttempts((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->getPatientInfo((*reinterpret_cast< QJSValue(*)>(_a[1]))); break;
        case 24: _t->updatePatientInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< QJSValue(*)>(_a[6]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QJSValue >(); break;
            }
            break;
        case 24:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 5:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QJSValue >(); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::updatePatientInfoSuccess)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::updatePatientInfoFailed)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::isAuthenticatedChanged)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::remainingAttemptsChanged)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::currentUserIdChanged)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::currentUserTypeChanged)) {
                *result = 11;
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
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
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
void AuthManager::updatePatientInfoSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void AuthManager::updatePatientInfoFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AuthManager::isAuthenticatedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void AuthManager::remainingAttemptsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void AuthManager::currentUserIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void AuthManager::currentUserTypeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

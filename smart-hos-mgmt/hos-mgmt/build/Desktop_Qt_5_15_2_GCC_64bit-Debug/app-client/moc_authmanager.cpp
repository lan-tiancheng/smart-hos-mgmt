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
    QByteArrayData data[74];
    char stringdata0[965];
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
QT_MOC_LITERAL(16, 170, 15), // "messageReceived"
QT_MOC_LITERAL(17, 186, 10), // "fromUserId"
QT_MOC_LITERAL(18, 197, 12), // "fromUsername"
QT_MOC_LITERAL(19, 210, 7), // "message"
QT_MOC_LITERAL(20, 218, 18), // "messageSentSuccess"
QT_MOC_LITERAL(21, 237, 9), // "messageId"
QT_MOC_LITERAL(22, 247, 17), // "messageSentFailed"
QT_MOC_LITERAL(23, 265, 24), // "conversationListReceived"
QT_MOC_LITERAL(24, 290, 13), // "conversations"
QT_MOC_LITERAL(25, 304, 16), // "messagesReceived"
QT_MOC_LITERAL(26, 321, 14), // "conversationId"
QT_MOC_LITERAL(27, 336, 8), // "messages"
QT_MOC_LITERAL(28, 345, 18), // "videoCallRequested"
QT_MOC_LITERAL(29, 364, 6), // "callId"
QT_MOC_LITERAL(30, 371, 17), // "videoCallAccepted"
QT_MOC_LITERAL(31, 389, 17), // "videoCallRejected"
QT_MOC_LITERAL(32, 407, 16), // "videoCallStarted"
QT_MOC_LITERAL(33, 424, 14), // "videoCallEnded"
QT_MOC_LITERAL(34, 439, 14), // "videoCallError"
QT_MOC_LITERAL(35, 454, 22), // "isAuthenticatedChanged"
QT_MOC_LITERAL(36, 477, 24), // "remainingAttemptsChanged"
QT_MOC_LITERAL(37, 502, 20), // "currentUserIdChanged"
QT_MOC_LITERAL(38, 523, 13), // "logoutSuccess"
QT_MOC_LITERAL(39, 537, 11), // "onReadyRead"
QT_MOC_LITERAL(40, 549, 11), // "onConnected"
QT_MOC_LITERAL(41, 561, 15), // "onErrorOccurred"
QT_MOC_LITERAL(42, 577, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(43, 606, 11), // "socketError"
QT_MOC_LITERAL(44, 618, 12), // "requestLogin"
QT_MOC_LITERAL(45, 631, 8), // "username"
QT_MOC_LITERAL(46, 640, 8), // "password"
QT_MOC_LITERAL(47, 649, 15), // "requestRegister"
QT_MOC_LITERAL(48, 665, 5), // "phone"
QT_MOC_LITERAL(49, 671, 7), // "address"
QT_MOC_LITERAL(50, 679, 3), // "age"
QT_MOC_LITERAL(51, 683, 6), // "gender"
QT_MOC_LITERAL(52, 690, 16), // "submitHealthData"
QT_MOC_LITERAL(53, 707, 8), // "heightCm"
QT_MOC_LITERAL(54, 716, 8), // "weightKg"
QT_MOC_LITERAL(55, 725, 6), // "lungMl"
QT_MOC_LITERAL(56, 732, 2), // "bp"
QT_MOC_LITERAL(57, 735, 11), // "sendMessage"
QT_MOC_LITERAL(58, 747, 8), // "toUserId"
QT_MOC_LITERAL(59, 756, 20), // "requestConversations"
QT_MOC_LITERAL(60, 777, 15), // "requestMessages"
QT_MOC_LITERAL(61, 793, 11), // "otherUserId"
QT_MOC_LITERAL(62, 805, 14), // "startVideoCall"
QT_MOC_LITERAL(63, 820, 15), // "acceptVideoCall"
QT_MOC_LITERAL(64, 836, 15), // "rejectVideoCall"
QT_MOC_LITERAL(65, 852, 12), // "endVideoCall"
QT_MOC_LITERAL(66, 865, 20), // "setRemainingAttempts"
QT_MOC_LITERAL(67, 886, 8), // "attempts"
QT_MOC_LITERAL(68, 895, 6), // "logout"
QT_MOC_LITERAL(69, 902, 15), // "isAuthenticated"
QT_MOC_LITERAL(70, 918, 17), // "remainingAttempts"
QT_MOC_LITERAL(71, 936, 13), // "currentUserId"
QT_MOC_LITERAL(72, 950, 7), // "Patient"
QT_MOC_LITERAL(73, 958, 6) // "Doctor"

    },
    "AuthManager\0loginSuccess\0\0userId\0"
    "userType\0UserType\0loginFailed\0reason\0"
    "registerSuccess\0registerFailed\0"
    "healthSubmitSuccess\0bmi\0lungLevel\0"
    "bpLevel\0overall\0healthSubmitFailed\0"
    "messageReceived\0fromUserId\0fromUsername\0"
    "message\0messageSentSuccess\0messageId\0"
    "messageSentFailed\0conversationListReceived\0"
    "conversations\0messagesReceived\0"
    "conversationId\0messages\0videoCallRequested\0"
    "callId\0videoCallAccepted\0videoCallRejected\0"
    "videoCallStarted\0videoCallEnded\0"
    "videoCallError\0isAuthenticatedChanged\0"
    "remainingAttemptsChanged\0currentUserIdChanged\0"
    "logoutSuccess\0onReadyRead\0onConnected\0"
    "onErrorOccurred\0QAbstractSocket::SocketError\0"
    "socketError\0requestLogin\0username\0"
    "password\0requestRegister\0phone\0address\0"
    "age\0gender\0submitHealthData\0heightCm\0"
    "weightKg\0lungMl\0bp\0sendMessage\0toUserId\0"
    "requestConversations\0requestMessages\0"
    "otherUserId\0startVideoCall\0acceptVideoCall\0"
    "rejectVideoCall\0endVideoCall\0"
    "setRemainingAttempts\0attempts\0logout\0"
    "isAuthenticated\0remainingAttempts\0"
    "currentUserId\0Patient\0Doctor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AuthManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      39,   14, // methods
       3,  364, // properties
       1,  376, // enums/sets
       0,    0, // constructors
       0,       // flags
      22,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  209,    2, 0x06 /* Public */,
       1,    1,  214,    2, 0x06 /* Public */,
       6,    1,  217,    2, 0x06 /* Public */,
       8,    0,  220,    2, 0x06 /* Public */,
       9,    1,  221,    2, 0x06 /* Public */,
      10,    4,  224,    2, 0x06 /* Public */,
      15,    1,  233,    2, 0x06 /* Public */,
      16,    3,  236,    2, 0x06 /* Public */,
      20,    1,  243,    2, 0x06 /* Public */,
      22,    1,  246,    2, 0x06 /* Public */,
      23,    1,  249,    2, 0x06 /* Public */,
      25,    2,  252,    2, 0x06 /* Public */,
      28,    3,  257,    2, 0x06 /* Public */,
      30,    1,  264,    2, 0x06 /* Public */,
      31,    1,  267,    2, 0x06 /* Public */,
      32,    1,  270,    2, 0x06 /* Public */,
      33,    1,  273,    2, 0x06 /* Public */,
      34,    1,  276,    2, 0x06 /* Public */,
      35,    0,  279,    2, 0x06 /* Public */,
      36,    0,  280,    2, 0x06 /* Public */,
      37,    0,  281,    2, 0x06 /* Public */,
      38,    0,  282,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      39,    0,  283,    2, 0x08 /* Private */,
      40,    0,  284,    2, 0x08 /* Private */,
      41,    1,  285,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
      44,    3,  288,    2, 0x02 /* Public */,
      44,    2,  295,    2, 0x02 /* Public */,
      47,    7,  300,    2, 0x02 /* Public */,
      47,    7,  315,    2, 0x02 /* Public */,
      52,    4,  330,    2, 0x02 /* Public */,
      57,    2,  339,    2, 0x02 /* Public */,
      59,    0,  344,    2, 0x02 /* Public */,
      60,    1,  345,    2, 0x02 /* Public */,
      62,    1,  348,    2, 0x02 /* Public */,
      63,    1,  351,    2, 0x02 /* Public */,
      64,    1,  354,    2, 0x02 /* Public */,
      65,    1,  357,    2, 0x02 /* Public */,
      66,    1,  360,    2, 0x02 /* Public */,
      68,    0,  363,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, 0x80000000 | 5,    4,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,   14,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,   17,   18,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QJsonArray,   24,
    QMetaType::Void, QMetaType::Int, QMetaType::QJsonArray,   26,   27,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   29,   17,   18,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 42,   43,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString, QMetaType::QString,    4,   45,   46,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   45,   46,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    4,   45,   46,   48,   49,   50,   51,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::QString,    4,   45,   46,   48,   49,   50,   51,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int, QMetaType::QString,   53,   54,   55,   56,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   58,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Void, QMetaType::Int,   61,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, QMetaType::Int,   67,
    QMetaType::Void,

 // properties: name, type, flags
      69, QMetaType::Bool, 0x00495001,
      70, QMetaType::Int, 0x00495001,
      71, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
      18,
      19,
      20,

 // enums: name, alias, flags, count, data
       5,    5, 0x0,    2,  381,

 // enum data: key, value
      72, uint(AuthManager::Patient),
      73, uint(AuthManager::Doctor),

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
        case 7: _t->messageReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 8: _t->messageSentSuccess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->messageSentFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->conversationListReceived((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 11: _t->messagesReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QJsonArray(*)>(_a[2]))); break;
        case 12: _t->videoCallRequested((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 13: _t->videoCallAccepted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->videoCallRejected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->videoCallStarted((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->videoCallEnded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->videoCallError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->isAuthenticatedChanged(); break;
        case 19: _t->remainingAttemptsChanged(); break;
        case 20: _t->currentUserIdChanged(); break;
        case 21: _t->logoutSuccess(); break;
        case 22: _t->onReadyRead(); break;
        case 23: _t->onConnected(); break;
        case 24: _t->onErrorOccurred((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 25: _t->requestLogin((*reinterpret_cast< UserType(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 26: _t->requestLogin((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 27: _t->requestRegister((*reinterpret_cast< UserType(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7]))); break;
        case 28: _t->requestRegister((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7]))); break;
        case 29: _t->submitHealthData((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 30: _t->sendMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 31: _t->requestConversations(); break;
        case 32: _t->requestMessages((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->startVideoCall((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->acceptVideoCall((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->rejectVideoCall((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->endVideoCall((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->setRemainingAttempts((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->logout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 24:
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
            using _t = void (AuthManager::*)(int , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::messageReceived)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::messageSentSuccess)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::messageSentFailed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::conversationListReceived)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(int , const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::messagesReceived)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(int , int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::videoCallRequested)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::videoCallAccepted)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::videoCallRejected)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::videoCallStarted)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::videoCallEnded)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::videoCallError)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::isAuthenticatedChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::remainingAttemptsChanged)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::currentUserIdChanged)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (AuthManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AuthManager::logoutSuccess)) {
                *result = 21;
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
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 39)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 39;
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
void AuthManager::messageReceived(int _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AuthManager::messageSentSuccess(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AuthManager::messageSentFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void AuthManager::conversationListReceived(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void AuthManager::messagesReceived(int _t1, const QJsonArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void AuthManager::videoCallRequested(int _t1, int _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void AuthManager::videoCallAccepted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void AuthManager::videoCallRejected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void AuthManager::videoCallStarted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void AuthManager::videoCallEnded(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void AuthManager::videoCallError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void AuthManager::isAuthenticatedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void AuthManager::remainingAttemptsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void AuthManager::currentUserIdChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void AuthManager::logoutSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 21, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

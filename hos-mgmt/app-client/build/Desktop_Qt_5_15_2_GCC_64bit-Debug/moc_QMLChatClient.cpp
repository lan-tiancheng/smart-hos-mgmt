/****************************************************************************
** Meta object code from reading C++ file 'QMLChatClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../桌面/xht/smart-hos-mgmt/hos-mgmt/app-client/src/chat/QMLChatClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QMLChatClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QMLChatClient_t {
    QByteArrayData data[33];
    char stringdata0[386];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QMLChatClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QMLChatClient_t qt_meta_stringdata_QMLChatClient = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QMLChatClient"
QT_MOC_LITERAL(1, 14, 16), // "connectedChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "connected"
QT_MOC_LITERAL(4, 42, 13), // "errorOccurred"
QT_MOC_LITERAL(5, 56, 3), // "msg"
QT_MOC_LITERAL(6, 60, 17), // "conversationReady"
QT_MOC_LITERAL(7, 78, 4), // "conv"
QT_MOC_LITERAL(8, 83, 19), // "conversationsLoaded"
QT_MOC_LITERAL(9, 103, 4), // "list"
QT_MOC_LITERAL(10, 108, 14), // "messagesLoaded"
QT_MOC_LITERAL(11, 123, 11), // "messageSent"
QT_MOC_LITERAL(12, 135, 15), // "messageReceived"
QT_MOC_LITERAL(13, 151, 19), // "readReceiptReceived"
QT_MOC_LITERAL(14, 171, 7), // "receipt"
QT_MOC_LITERAL(15, 179, 9), // "configure"
QT_MOC_LITERAL(16, 189, 7), // "baseUrl"
QT_MOC_LITERAL(17, 197, 6), // "userId"
QT_MOC_LITERAL(18, 204, 4), // "role"
QT_MOC_LITERAL(19, 209, 16), // "connectWebSocket"
QT_MOC_LITERAL(20, 226, 19), // "disconnectWebSocket"
QT_MOC_LITERAL(21, 246, 18), // "createConversation"
QT_MOC_LITERAL(22, 265, 8), // "doctorId"
QT_MOC_LITERAL(23, 274, 9), // "patientId"
QT_MOC_LITERAL(24, 284, 19), // "listMyConversations"
QT_MOC_LITERAL(25, 304, 12), // "listMessages"
QT_MOC_LITERAL(26, 317, 14), // "conversationId"
QT_MOC_LITERAL(27, 332, 8), // "beforeId"
QT_MOC_LITERAL(28, 341, 5), // "limit"
QT_MOC_LITERAL(29, 347, 11), // "sendMessage"
QT_MOC_LITERAL(30, 359, 7), // "content"
QT_MOC_LITERAL(31, 367, 8), // "markRead"
QT_MOC_LITERAL(32, 376, 9) // "messageId"

    },
    "QMLChatClient\0connectedChanged\0\0"
    "connected\0errorOccurred\0msg\0"
    "conversationReady\0conv\0conversationsLoaded\0"
    "list\0messagesLoaded\0messageSent\0"
    "messageReceived\0readReceiptReceived\0"
    "receipt\0configure\0baseUrl\0userId\0role\0"
    "connectWebSocket\0disconnectWebSocket\0"
    "createConversation\0doctorId\0patientId\0"
    "listMyConversations\0listMessages\0"
    "conversationId\0beforeId\0limit\0sendMessage\0"
    "content\0markRead\0messageId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QMLChatClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       1,  166, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,
       4,    1,  107,    2, 0x06 /* Public */,
       6,    1,  110,    2, 0x06 /* Public */,
       8,    1,  113,    2, 0x06 /* Public */,
      10,    1,  116,    2, 0x06 /* Public */,
      11,    1,  119,    2, 0x06 /* Public */,
      12,    1,  122,    2, 0x06 /* Public */,
      13,    1,  125,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      15,    3,  128,    2, 0x02 /* Public */,
      19,    0,  135,    2, 0x02 /* Public */,
      20,    0,  136,    2, 0x02 /* Public */,
      21,    2,  137,    2, 0x02 /* Public */,
      24,    0,  142,    2, 0x02 /* Public */,
      25,    3,  143,    2, 0x02 /* Public */,
      25,    2,  150,    2, 0x22 /* Public | MethodCloned */,
      25,    1,  155,    2, 0x22 /* Public | MethodCloned */,
      29,    2,  158,    2, 0x02 /* Public */,
      31,    1,  163,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QVariant,    7,
    QMetaType::Void, QMetaType::QVariant,    9,
    QMetaType::Void, QMetaType::QVariant,    9,
    QMetaType::Void, QMetaType::QVariant,    5,
    QMetaType::Void, QMetaType::QVariant,    5,
    QMetaType::Void, QMetaType::QVariant,   14,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::LongLong, QMetaType::QString,   16,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   22,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, QMetaType::Int,   26,   27,   28,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   26,   27,
    QMetaType::Void, QMetaType::LongLong,   26,
    QMetaType::Void, QMetaType::LongLong, QMetaType::QString,   26,   30,
    QMetaType::Void, QMetaType::LongLong,   32,

 // properties: name, type, flags
       3, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,

       0        // eod
};

void QMLChatClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QMLChatClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->conversationReady((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 3: _t->conversationsLoaded((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 4: _t->messagesLoaded((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 5: _t->messageSent((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 6: _t->messageReceived((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 7: _t->readReceiptReceived((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 8: _t->configure((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 9: _t->connectWebSocket(); break;
        case 10: _t->disconnectWebSocket(); break;
        case 11: _t->createConversation((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 12: _t->listMyConversations(); break;
        case 13: _t->listMessages((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 14: _t->listMessages((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 15: _t->listMessages((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 16: _t->sendMessage((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 17: _t->markRead((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QMLChatClient::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMLChatClient::connectedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QMLChatClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMLChatClient::errorOccurred)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QMLChatClient::*)(const QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMLChatClient::conversationReady)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QMLChatClient::*)(const QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMLChatClient::conversationsLoaded)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QMLChatClient::*)(const QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMLChatClient::messagesLoaded)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QMLChatClient::*)(const QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMLChatClient::messageSent)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QMLChatClient::*)(const QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMLChatClient::messageReceived)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QMLChatClient::*)(const QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QMLChatClient::readReceiptReceived)) {
                *result = 7;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<QMLChatClient *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isConnected(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject QMLChatClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QMLChatClient.data,
    qt_meta_data_QMLChatClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QMLChatClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QMLChatClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QMLChatClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QMLChatClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QMLChatClient::connectedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QMLChatClient::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QMLChatClient::conversationReady(const QVariant & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QMLChatClient::conversationsLoaded(const QVariant & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QMLChatClient::messagesLoaded(const QVariant & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QMLChatClient::messageSent(const QVariant & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QMLChatClient::messageReceived(const QVariant & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QMLChatClient::readReceiptReceived(const QVariant & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

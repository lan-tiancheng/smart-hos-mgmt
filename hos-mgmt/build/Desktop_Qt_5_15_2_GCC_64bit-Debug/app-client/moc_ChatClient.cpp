/****************************************************************************
** Meta object code from reading C++ file 'ChatClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../app-client/src/chat/ChatClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatClient_t {
    QByteArrayData data[23];
    char stringdata0[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatClient_t qt_meta_stringdata_ChatClient = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatClient"
QT_MOC_LITERAL(1, 11, 16), // "connectedChanged"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 9), // "connected"
QT_MOC_LITERAL(4, 39, 13), // "errorOccurred"
QT_MOC_LITERAL(5, 53, 3), // "msg"
QT_MOC_LITERAL(6, 57, 17), // "conversationReady"
QT_MOC_LITERAL(7, 75, 4), // "conv"
QT_MOC_LITERAL(8, 80, 19), // "conversationsLoaded"
QT_MOC_LITERAL(9, 100, 4), // "list"
QT_MOC_LITERAL(10, 105, 14), // "messagesLoaded"
QT_MOC_LITERAL(11, 120, 11), // "messageSent"
QT_MOC_LITERAL(12, 132, 15), // "messageReceived"
QT_MOC_LITERAL(13, 148, 19), // "readReceiptReceived"
QT_MOC_LITERAL(14, 168, 7), // "receipt"
QT_MOC_LITERAL(15, 176, 13), // "onWsConnected"
QT_MOC_LITERAL(16, 190, 16), // "onWsDisconnected"
QT_MOC_LITERAL(17, 207, 15), // "onWsTextMessage"
QT_MOC_LITERAL(18, 223, 4), // "text"
QT_MOC_LITERAL(19, 228, 9), // "onWsError"
QT_MOC_LITERAL(20, 238, 4), // "Role"
QT_MOC_LITERAL(21, 243, 6), // "Doctor"
QT_MOC_LITERAL(22, 250, 7) // "Patient"

    },
    "ChatClient\0connectedChanged\0\0connected\0"
    "errorOccurred\0msg\0conversationReady\0"
    "conv\0conversationsLoaded\0list\0"
    "messagesLoaded\0messageSent\0messageReceived\0"
    "readReceiptReceived\0receipt\0onWsConnected\0"
    "onWsDisconnected\0onWsTextMessage\0text\0"
    "onWsError\0Role\0Doctor\0Patient"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       1,  104, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       6,    1,   80,    2, 0x06 /* Public */,
       8,    1,   83,    2, 0x06 /* Public */,
      10,    1,   86,    2, 0x06 /* Public */,
      11,    1,   89,    2, 0x06 /* Public */,
      12,    1,   92,    2, 0x06 /* Public */,
      13,    1,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   98,    2, 0x08 /* Private */,
      16,    0,   99,    2, 0x08 /* Private */,
      17,    1,  100,    2, 0x08 /* Private */,
      19,    0,  103,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QJsonObject,    7,
    QMetaType::Void, QMetaType::QJsonArray,    9,
    QMetaType::Void, QMetaType::QJsonArray,    9,
    QMetaType::Void, QMetaType::QJsonObject,    5,
    QMetaType::Void, QMetaType::QJsonObject,    5,
    QMetaType::Void, QMetaType::QJsonObject,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
      20,   20, 0x2,    2,  109,

 // enum data: key, value
      21, uint(ChatClient::Role::Doctor),
      22, uint(ChatClient::Role::Patient),

       0        // eod
};

void ChatClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->conversationReady((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 3: _t->conversationsLoaded((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 4: _t->messagesLoaded((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 5: _t->messageSent((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 6: _t->messageReceived((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 7: _t->readReceiptReceived((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 8: _t->onWsConnected(); break;
        case 9: _t->onWsDisconnected(); break;
        case 10: _t->onWsTextMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->onWsError(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatClient::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::connectedChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::errorOccurred)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::conversationReady)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::conversationsLoaded)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QJsonArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::messagesLoaded)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::messageSent)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::messageReceived)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatClient::readReceiptReceived)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChatClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ChatClient.data,
    qt_meta_data_ChatClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChatClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ChatClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
    return _id;
}

// SIGNAL 0
void ChatClient::connectedChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChatClient::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ChatClient::conversationReady(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ChatClient::conversationsLoaded(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ChatClient::messagesLoaded(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ChatClient::messageSent(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ChatClient::messageReceived(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ChatClient::readReceiptReceived(const QJsonObject & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

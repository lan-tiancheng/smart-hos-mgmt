/****************************************************************************
** Meta object code from reading C++ file 'ChatWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../桌面/xht/smart-hos-mgmt/hos-mgmt/app-client/src/ui/ChatWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatWindow_t {
    QByteArrayData data[15];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatWindow_t qt_meta_stringdata_ChatWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatWindow"
QT_MOC_LITERAL(1, 11, 18), // "onConnectedChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 2), // "ok"
QT_MOC_LITERAL(4, 34, 21), // "onConversationsLoaded"
QT_MOC_LITERAL(5, 56, 4), // "list"
QT_MOC_LITERAL(6, 61, 16), // "onMessagesLoaded"
QT_MOC_LITERAL(7, 78, 17), // "onMessageReceived"
QT_MOC_LITERAL(8, 96, 3), // "msg"
QT_MOC_LITERAL(9, 100, 13), // "onMessageSent"
QT_MOC_LITERAL(10, 114, 13), // "onReadReceipt"
QT_MOC_LITERAL(11, 128, 3), // "rec"
QT_MOC_LITERAL(12, 132, 20), // "onSelectConversation"
QT_MOC_LITERAL(13, 153, 6), // "onSend"
QT_MOC_LITERAL(14, 160, 11) // "onConnectWs"

    },
    "ChatWindow\0onConnectedChanged\0\0ok\0"
    "onConversationsLoaded\0list\0onMessagesLoaded\0"
    "onMessageReceived\0msg\0onMessageSent\0"
    "onReadReceipt\0rec\0onSelectConversation\0"
    "onSend\0onConnectWs"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       4,    1,   62,    2, 0x08 /* Private */,
       6,    1,   65,    2, 0x08 /* Private */,
       7,    1,   68,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      10,    1,   74,    2, 0x08 /* Private */,
      12,    0,   77,    2, 0x08 /* Private */,
      13,    0,   78,    2, 0x08 /* Private */,
      14,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::QJsonArray,    5,
    QMetaType::Void, QMetaType::QJsonArray,    5,
    QMetaType::Void, QMetaType::QJsonObject,    8,
    QMetaType::Void, QMetaType::QJsonObject,    8,
    QMetaType::Void, QMetaType::QJsonObject,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ChatWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onConnectedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onConversationsLoaded((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 2: _t->onMessagesLoaded((*reinterpret_cast< const QJsonArray(*)>(_a[1]))); break;
        case 3: _t->onMessageReceived((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 4: _t->onMessageSent((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 5: _t->onReadReceipt((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 6: _t->onSelectConversation(); break;
        case 7: _t->onSend(); break;
        case 8: _t->onConnectWs(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChatWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ChatWindow.data,
    qt_meta_data_ChatWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChatWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChatWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE

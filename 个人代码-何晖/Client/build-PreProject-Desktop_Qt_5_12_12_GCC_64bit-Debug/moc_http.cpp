/****************************************************************************
** Meta object code from reading C++ file 'http.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PreProject/http.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'http.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Http_t {
    QByteArrayData data[9];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Http_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Http_t qt_meta_stringdata_Http = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Http"
QT_MOC_LITERAL(1, 5, 15), // "http_postRequst"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 3), // "Url"
QT_MOC_LITERAL(4, 26, 21), // "QMap<QString,QString>"
QT_MOC_LITERAL(5, 48, 6), // "header"
QT_MOC_LITERAL(6, 55, 11), // "QByteArray&"
QT_MOC_LITERAL(7, 67, 11), // "requestData"
QT_MOC_LITERAL(8, 79, 9) // "replyData"

    },
    "Http\0http_postRequst\0\0Url\0"
    "QMap<QString,QString>\0header\0QByteArray&\0"
    "requestData\0replyData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Http[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    4,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, 0x80000000 | 4, 0x80000000 | 6, 0x80000000 | 6,    3,    5,    7,    8,

       0        // eod
};

void Http::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Http *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->http_postRequst((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QMap<QString,QString>(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3])),(*reinterpret_cast< QByteArray(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Http::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Http.data,
    qt_meta_data_Http,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Http::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Http::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Http.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Http::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

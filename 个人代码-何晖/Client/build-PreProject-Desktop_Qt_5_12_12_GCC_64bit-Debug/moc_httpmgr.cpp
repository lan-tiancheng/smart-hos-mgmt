/****************************************************************************
** Meta object code from reading C++ file 'httpmgr.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PreProject/httpmgr.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpmgr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HttpMgr_t {
    QByteArrayData data[15];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HttpMgr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HttpMgr_t qt_meta_stringdata_HttpMgr = {
    {
QT_MOC_LITERAL(0, 0, 7), // "HttpMgr"
QT_MOC_LITERAL(1, 8, 13), // "sigHttpFinish"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "ReqId"
QT_MOC_LITERAL(4, 29, 2), // "id"
QT_MOC_LITERAL(5, 32, 3), // "res"
QT_MOC_LITERAL(6, 36, 9), // "ErrorCode"
QT_MOC_LITERAL(7, 46, 3), // "err"
QT_MOC_LITERAL(8, 50, 7), // "Moudles"
QT_MOC_LITERAL(9, 58, 3), // "mod"
QT_MOC_LITERAL(10, 62, 15), // "sigRegModFinish"
QT_MOC_LITERAL(11, 78, 20), // "sig_reset_mod_finish"
QT_MOC_LITERAL(12, 99, 20), // "sig_login_mod_finish"
QT_MOC_LITERAL(13, 120, 30), // "sig_updata_info_reg_mod_finish"
QT_MOC_LITERAL(14, 151, 14) // "slotHttpFinish"

    },
    "HttpMgr\0sigHttpFinish\0\0ReqId\0id\0res\0"
    "ErrorCode\0err\0Moudles\0mod\0sigRegModFinish\0"
    "sig_reset_mod_finish\0sig_login_mod_finish\0"
    "sig_updata_info_reg_mod_finish\0"
    "slotHttpFinish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HttpMgr[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   44,    2, 0x06 /* Public */,
      10,    3,   53,    2, 0x06 /* Public */,
      11,    3,   60,    2, 0x06 /* Public */,
      12,    3,   67,    2, 0x06 /* Public */,
      13,    3,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    4,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 6, 0x80000000 | 8,    4,    5,    7,    9,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 6,    4,    5,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 6,    4,    5,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 6,    4,    5,    7,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 6,    4,    5,    7,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 6, 0x80000000 | 8,    4,    5,    7,    9,

       0        // eod
};

void HttpMgr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HttpMgr *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigHttpFinish((*reinterpret_cast< ReqId(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< ErrorCode(*)>(_a[3])),(*reinterpret_cast< Moudles(*)>(_a[4]))); break;
        case 1: _t->sigRegModFinish((*reinterpret_cast< ReqId(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< ErrorCode(*)>(_a[3]))); break;
        case 2: _t->sig_reset_mod_finish((*reinterpret_cast< ReqId(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< ErrorCode(*)>(_a[3]))); break;
        case 3: _t->sig_login_mod_finish((*reinterpret_cast< ReqId(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< ErrorCode(*)>(_a[3]))); break;
        case 4: _t->sig_updata_info_reg_mod_finish((*reinterpret_cast< ReqId(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< ErrorCode(*)>(_a[3]))); break;
        case 5: _t->slotHttpFinish((*reinterpret_cast< ReqId(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< ErrorCode(*)>(_a[3])),(*reinterpret_cast< Moudles(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HttpMgr::*)(ReqId , QString , ErrorCode , Moudles );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpMgr::sigHttpFinish)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HttpMgr::*)(ReqId , QString , ErrorCode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpMgr::sigRegModFinish)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HttpMgr::*)(ReqId , QString , ErrorCode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpMgr::sig_reset_mod_finish)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (HttpMgr::*)(ReqId , QString , ErrorCode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpMgr::sig_login_mod_finish)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (HttpMgr::*)(ReqId , QString , ErrorCode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpMgr::sig_updata_info_reg_mod_finish)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HttpMgr::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_HttpMgr.data,
    qt_meta_data_HttpMgr,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HttpMgr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HttpMgr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HttpMgr.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Singleton<HttpMgr>"))
        return static_cast< Singleton<HttpMgr>*>(this);
    if (!strcmp(_clname, "std::enable_shared_from_this<HttpMgr>"))
        return static_cast< std::enable_shared_from_this<HttpMgr>*>(this);
    return QObject::qt_metacast(_clname);
}

int HttpMgr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void HttpMgr::sigHttpFinish(ReqId _t1, QString _t2, ErrorCode _t3, Moudles _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HttpMgr::sigRegModFinish(ReqId _t1, QString _t2, ErrorCode _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HttpMgr::sig_reset_mod_finish(ReqId _t1, QString _t2, ErrorCode _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void HttpMgr::sig_login_mod_finish(ReqId _t1, QString _t2, ErrorCode _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void HttpMgr::sig_updata_info_reg_mod_finish(ReqId _t1, QString _t2, ErrorCode _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

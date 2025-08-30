/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PreProject/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
<<<<<<< HEAD
    QByteArrayData data[7];
    char stringdata0[90];
=======
    QByteArrayData data[13];
    char stringdata0[209];
>>>>>>> 9e1acf7f4e940ddfee8d6a95eb27ca3d167d77c9
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
<<<<<<< HEAD
QT_MOC_LITERAL(1, 11, 13), // "slotSwitchRrg"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "slotSwitchLogin"
QT_MOC_LITERAL(4, 42, 15), // "slotSwitchReset"
QT_MOC_LITERAL(5, 58, 16), // "SlotSwitchLogin2"
QT_MOC_LITERAL(6, 75, 14) // "SlotSwitchMain"

    },
    "MainWindow\0slotSwitchRrg\0\0slotSwitchLogin\0"
    "slotSwitchReset\0SlotSwitchLogin2\0"
    "SlotSwitchMain"
=======
QT_MOC_LITERAL(1, 11, 21), // "sig_patient_mesg_need"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 19), // "sig_make_first_list"
QT_MOC_LITERAL(4, 54, 8), // "showTime"
QT_MOC_LITERAL(5, 63, 16), // "slot_handleInput"
QT_MOC_LITERAL(6, 80, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(7, 104, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(8, 128, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(9, 148, 13), // "on_PI_clicked"
QT_MOC_LITERAL(10, 162, 14), // "on_INF_clicked"
QT_MOC_LITERAL(11, 177, 26), // "on_checkBox_1_stateChanged"
QT_MOC_LITERAL(12, 204, 4) // "arg1"

    },
    "MainWindow\0sig_patient_mesg_need\0\0"
    "sig_make_first_list\0showTime\0"
    "slot_handleInput\0on_pushButton_4_clicked\0"
    "on_pushButton_5_clicked\0on_checkBox_clicked\0"
    "on_PI_clicked\0on_INF_clicked\0"
    "on_checkBox_1_stateChanged\0arg1"
>>>>>>> 9e1acf7f4e940ddfee8d6a95eb27ca3d167d77c9
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
<<<<<<< HEAD
       5,   14, // methods
=======
      10,   14, // methods
>>>>>>> 9e1acf7f4e940ddfee8d6a95eb27ca3d167d77c9
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
<<<<<<< HEAD
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,
=======
       4,    0,   66,    2, 0x09 /* Protected */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    1,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
>>>>>>> 9e1acf7f4e940ddfee8d6a95eb27ca3d167d77c9

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
<<<<<<< HEAD
=======
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
>>>>>>> 9e1acf7f4e940ddfee8d6a95eb27ca3d167d77c9

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
<<<<<<< HEAD
        case 0: _t->slotSwitchRrg(); break;
        case 1: _t->slotSwitchLogin(); break;
        case 2: _t->slotSwitchReset(); break;
        case 3: _t->SlotSwitchLogin2(); break;
        case 4: _t->SlotSwitchMain(); break;
=======
        case 0: _t->sig_patient_mesg_need(); break;
        case 1: _t->sig_make_first_list(); break;
        case 2: _t->showTime(); break;
        case 3: _t->slot_handleInput(); break;
        case 4: _t->on_pushButton_4_clicked(); break;
        case 5: _t->on_pushButton_5_clicked(); break;
        case 6: _t->on_checkBox_clicked(); break;
        case 7: _t->on_PI_clicked(); break;
        case 8: _t->on_INF_clicked(); break;
        case 9: _t->on_checkBox_1_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
>>>>>>> 9e1acf7f4e940ddfee8d6a95eb27ca3d167d77c9
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sig_patient_mesg_need)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sig_make_first_list)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
<<<<<<< HEAD
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
=======
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
>>>>>>> 9e1acf7f4e940ddfee8d6a95eb27ca3d167d77c9
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sig_patient_mesg_need()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::sig_make_first_list()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

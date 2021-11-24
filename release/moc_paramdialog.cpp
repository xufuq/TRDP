/****************************************************************************
** Meta object code from reading C++ file 'paramdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../paramdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paramdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParamDialog_t {
    QByteArrayData data[16];
    char stringdata0[246];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParamDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParamDialog_t qt_meta_stringdata_ParamDialog = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ParamDialog"
QT_MOC_LITERAL(1, 12, 21), // "get104ParamFromDialog"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 6), // "ETB104"
QT_MOC_LITERAL(4, 42, 5), // "etbid"
QT_MOC_LITERAL(5, 48, 21), // "get106ParamFromDialog"
QT_MOC_LITERAL(6, 70, 7), // "uint8_t"
QT_MOC_LITERAL(7, 78, 21), // "get110ParamFromDialog"
QT_MOC_LITERAL(8, 100, 21), // "get130ParamFromDialog"
QT_MOC_LITERAL(9, 122, 6), // "ETB130"
QT_MOC_LITERAL(10, 129, 6), // "etb130"
QT_MOC_LITERAL(11, 136, 21), // "on_Confirm104_clicked"
QT_MOC_LITERAL(12, 158, 21), // "on_Confirm106_clicked"
QT_MOC_LITERAL(13, 180, 21), // "on_Confirm110_clicked"
QT_MOC_LITERAL(14, 202, 21), // "on_Confirm130_clicked"
QT_MOC_LITERAL(15, 224, 21) // "on_pushButton_clicked"

    },
    "ParamDialog\0get104ParamFromDialog\0\0"
    "ETB104\0etbid\0get106ParamFromDialog\0"
    "uint8_t\0get110ParamFromDialog\0"
    "get130ParamFromDialog\0ETB130\0etb130\0"
    "on_Confirm104_clicked\0on_Confirm106_clicked\0"
    "on_Confirm110_clicked\0on_Confirm130_clicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParamDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       7,    1,   65,    2, 0x06 /* Public */,
       8,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   71,    2, 0x08 /* Private */,
      12,    0,   72,    2, 0x08 /* Private */,
      13,    0,   73,    2, 0x08 /* Private */,
      14,    0,   74,    2, 0x08 /* Private */,
      15,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 9,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ParamDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ParamDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->get104ParamFromDialog((*reinterpret_cast< ETB104(*)>(_a[1]))); break;
        case 1: _t->get106ParamFromDialog((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 2: _t->get110ParamFromDialog((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 3: _t->get130ParamFromDialog((*reinterpret_cast< ETB130(*)>(_a[1]))); break;
        case 4: _t->on_Confirm104_clicked(); break;
        case 5: _t->on_Confirm106_clicked(); break;
        case 6: _t->on_Confirm110_clicked(); break;
        case 7: _t->on_Confirm130_clicked(); break;
        case 8: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ParamDialog::*)(ETB104 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParamDialog::get104ParamFromDialog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ParamDialog::*)(uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParamDialog::get106ParamFromDialog)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ParamDialog::*)(uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParamDialog::get110ParamFromDialog)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ParamDialog::*)(ETB130 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ParamDialog::get130ParamFromDialog)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ParamDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_ParamDialog.data,
    qt_meta_data_ParamDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ParamDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParamDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ParamDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ParamDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ParamDialog::get104ParamFromDialog(ETB104 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ParamDialog::get106ParamFromDialog(uint8_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ParamDialog::get110ParamFromDialog(uint8_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ParamDialog::get130ParamFromDialog(ETB130 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

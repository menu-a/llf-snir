/****************************************************************************
** Meta object code from reading C++ file 'qvariometer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QamFlightInstruments-0.4/qvariometer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qvariometer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QamVariometer_t {
    QByteArrayData data[5];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QamVariometer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QamVariometer_t qt_meta_stringdata_QamVariometer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QamVariometer"
QT_MOC_LITERAL(1, 14, 13), // "selectPressed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "num"
QT_MOC_LITERAL(4, 33, 8) // "longClic"

    },
    "QamVariometer\0selectPressed\0\0num\0"
    "longClic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QamVariometer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x08 /* Private */,
       1,    1,   29,    2, 0x28 /* Private | MethodCloned */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void QamVariometer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QamVariometer *_t = static_cast<QamVariometer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->selectPressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->selectPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QamVariometer::staticMetaObject = {
    { &QamFlightInstrument::staticMetaObject, qt_meta_stringdata_QamVariometer.data,
      qt_meta_data_QamVariometer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QamVariometer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QamVariometer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QamVariometer.stringdata0))
        return static_cast<void*>(const_cast< QamVariometer*>(this));
    return QamFlightInstrument::qt_metacast(_clname);
}

int QamVariometer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QamFlightInstrument::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'qamtcpclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Modbus/ModbusTCPWorker/qamtcpclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qamtcpclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QamTcpClient_t {
    QByteArrayData data[13];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QamTcpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QamTcpClient_t qt_meta_stringdata_QamTcpClient = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QamTcpClient"
QT_MOC_LITERAL(1, 13, 12), // "sockReceived"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "sockInfo"
QT_MOC_LITERAL(4, 36, 9), // "sockClose"
QT_MOC_LITERAL(5, 46, 9), // "sockWrite"
QT_MOC_LITERAL(6, 56, 4), // "data"
QT_MOC_LITERAL(7, 61, 8), // "sockRead"
QT_MOC_LITERAL(8, 70, 9), // "sockError"
QT_MOC_LITERAL(9, 80, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(10, 109, 5), // "error"
QT_MOC_LITERAL(11, 115, 13), // "sockConnected"
QT_MOC_LITERAL(12, 129, 16) // "sockDisconnected"

    },
    "QamTcpClient\0sockReceived\0\0sockInfo\0"
    "sockClose\0sockWrite\0data\0sockRead\0"
    "sockError\0QAbstractSocket::SocketError\0"
    "error\0sockConnected\0sockDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QamTcpClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   60,    2, 0x0a /* Public */,
       5,    1,   61,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    1,   65,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QamTcpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QamTcpClient *_t = static_cast<QamTcpClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sockReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->sockInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sockClose(); break;
        case 3: _t->sockWrite((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 4: _t->sockRead(); break;
        case 5: _t->sockError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->sockConnected(); break;
        case 7: _t->sockDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QamTcpClient::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamTcpClient::sockReceived)) {
                *result = 0;
            }
        }
        {
            typedef void (QamTcpClient::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamTcpClient::sockInfo)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject QamTcpClient::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_QamTcpClient.data,
      qt_meta_data_QamTcpClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QamTcpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QamTcpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QamTcpClient.stringdata0))
        return static_cast<void*>(const_cast< QamTcpClient*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int QamTcpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QamTcpClient::sockReceived(const QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QamTcpClient::sockInfo(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'serverquery.h'
**
** Created: Sat Nov 8 21:35:40 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serverquery.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverquery.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ServerQuery[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      18,   13,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ServerQuery[] = {
    "ServerQuery\0\0node\0responseRecieved(XmlNode*)\0"
};

const QMetaObject ServerQuery::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerQuery,
      qt_meta_data_ServerQuery, 0 }
};

const QMetaObject *ServerQuery::metaObject() const
{
    return &staticMetaObject;
}

void *ServerQuery::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServerQuery))
        return static_cast<void*>(const_cast< ServerQuery*>(this));
    return QObject::qt_metacast(_clname);
}

int ServerQuery::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: responseRecieved((*reinterpret_cast< XmlNode*(*)>(_a[1]))); break;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ServerQuery::responseRecieved(XmlNode * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

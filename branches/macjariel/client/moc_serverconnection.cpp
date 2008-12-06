/****************************************************************************
** Meta object code from reading C++ file 'serverconnection.h'
**
** Created: Sat Nov 8 21:35:39 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serverconnection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serverconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ServerConnection[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      68,   18,   17,   17, 0x05,
     120,  112,   17,   17, 0x05,
     140,  112,   17,   17, 0x05,
     189,  161,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     252,  230,   17,   17, 0x0a,
     281,   17,   17,   17, 0x0a,
     338,  304,   17,   17, 0x0a,
     373,   17,   17,   17, 0x0a,
     385,  112,   17,   17, 0x0a,
     410,   17,   17,   17, 0x08,
     422,   17,   17,   17, 0x08,
     437,   17,   17,   17, 0x08,
     453,  448,   17,   17, 0x08,
     482,  448,   17,   17, 0x08,
     514,  448,   17,   17, 0x08,
     547,  448,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ServerConnection[] = {
    "ServerConnection\0\0"
    "connected,serverHost,serverName,serverDescription\0"
    "statusChanged(bool,QString,QString,QString)\0"
    "message\0logMessage(QString)\0"
    "incomingXml(QString)\0senderId,senderName,message\0"
    "incomingChatMessage(int,QString,QString)\0"
    "serverHost,serverPort\0"
    "connectToServer(QString,int)\0"
    "disconnectFromServer()\0"
    "gameId,gameName,spectate,password\0"
    "joinGame(int,QString,bool,QString)\0"
    "leaveGame()\0sendChatMessage(QString)\0"
    "connected()\0disconnected()\0readData()\0"
    "node\0recievedServerInfo(XmlNode*)\0"
    "recievedEventJoinGame(XmlNode*)\0"
    "recievedEventLeaveGame(XmlNode*)\0"
    "recievedEventChatMessage(XmlNode*)\0"
};

const QMetaObject ServerConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerConnection,
      qt_meta_data_ServerConnection, 0 }
};

const QMetaObject *ServerConnection::metaObject() const
{
    return &staticMetaObject;
}

void *ServerConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServerConnection))
        return static_cast<void*>(const_cast< ServerConnection*>(this));
    return QObject::qt_metacast(_clname);
}

int ServerConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: statusChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: logMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: incomingXml((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: incomingChatMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 4: connectToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: disconnectFromServer(); break;
        case 6: joinGame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 7: leaveGame(); break;
        case 8: sendChatMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: connected(); break;
        case 10: disconnected(); break;
        case 11: readData(); break;
        case 12: recievedServerInfo((*reinterpret_cast< XmlNode*(*)>(_a[1]))); break;
        case 13: recievedEventJoinGame((*reinterpret_cast< XmlNode*(*)>(_a[1]))); break;
        case 14: recievedEventLeaveGame((*reinterpret_cast< XmlNode*(*)>(_a[1]))); break;
        case 15: recievedEventChatMessage((*reinterpret_cast< XmlNode*(*)>(_a[1]))); break;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ServerConnection::statusChanged(bool _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ServerConnection::logMessage(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ServerConnection::incomingXml(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ServerConnection::incomingChatMessage(int _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE

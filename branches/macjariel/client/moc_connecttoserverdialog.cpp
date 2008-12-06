/****************************************************************************
** Meta object code from reading C++ file 'connecttoserverdialog.h'
**
** Created: Sat Nov 8 21:35:37 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "connecttoserverdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connecttoserverdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConnectToServerDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      57,   23,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      94,   22,   22,   22, 0x08,
     141,  129,   22,   22, 0x08,
     194,  129,   22,   22, 0x08,
     253,   22,   22,   22, 0x08,
     283,   22,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ConnectToServerDialog[] = {
    "ConnectToServerDialog\0\0"
    "serverAddress,serverPort,nickname\0"
    "connectToServer(QString,int,QString)\0"
    "on_mp_buttonSaveFavorite_clicked()\0"
    "item,column\0"
    "on_mp_favoriteList_itemClicked(QTreeWidgetItem*,int)\0"
    "on_mp_favoriteList_itemDoubleClicked(QTreeWidgetItem*,int)\0"
    "on_mp_connectButton_clicked()\0"
    "setConnectButtonStatus()\0"
};

const QMetaObject ConnectToServerDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConnectToServerDialog,
      qt_meta_data_ConnectToServerDialog, 0 }
};

const QMetaObject *ConnectToServerDialog::metaObject() const
{
    return &staticMetaObject;
}

void *ConnectToServerDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectToServerDialog))
        return static_cast<void*>(const_cast< ConnectToServerDialog*>(this));
    if (!strcmp(_clname, "Ui::ConnectToServerDialog"))
        return static_cast< Ui::ConnectToServerDialog*>(const_cast< ConnectToServerDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ConnectToServerDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connectToServer((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: on_mp_buttonSaveFavorite_clicked(); break;
        case 2: on_mp_favoriteList_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: on_mp_favoriteList_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: on_mp_connectButton_clicked(); break;
        case 5: setConnectButtonStatus(); break;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ConnectToServerDialog::connectToServer(QString _t1, int _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

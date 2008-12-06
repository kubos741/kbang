/****************************************************************************
** Meta object code from reading C++ file 'joingamedialog.h'
**
** Created: Sat Nov 8 21:35:41 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "joingamedialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'joingamedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_JoinGameDialog[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      50,   16,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
      85,   15,   15,   15, 0x0a,
     110,  103,   15,   15, 0x0a,
     131,   15,   15,   15, 0x0a,
     158,   15,   15,   15, 0x0a,
     200,  188,   15,   15, 0x0a,
     253,   15,   15,   15, 0x0a,
     280,   15,   15,   15, 0x0a,
     311,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_JoinGameDialog[] = {
    "JoinGameDialog\0\0gameId,gameName,spectate,password\0"
    "joinGame(int,QString,bool,QString)\0"
    "refreshGameList()\0gameId\0loadGameDetails(int)\0"
    "recievedGameList(XmlNode*)\0"
    "recievedGameDetails(XmlNode*)\0item,column\0"
    "on_mp_gameListView_itemClicked(QTreeWidgetItem*,int)\0"
    "on_mp_playButton_clicked()\0"
    "on_mp_spectateButton_clicked()\0"
    "doButtons()\0"
};

const QMetaObject JoinGameDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_JoinGameDialog,
      qt_meta_data_JoinGameDialog, 0 }
};

const QMetaObject *JoinGameDialog::metaObject() const
{
    return &staticMetaObject;
}

void *JoinGameDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_JoinGameDialog))
        return static_cast<void*>(const_cast< JoinGameDialog*>(this));
    if (!strcmp(_clname, "Ui::JoinGameDialog"))
        return static_cast< Ui::JoinGameDialog*>(const_cast< JoinGameDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int JoinGameDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: joinGame((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: refreshGameList(); break;
        case 2: loadGameDetails((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: recievedGameList((*reinterpret_cast< XmlNode*(*)>(_a[1]))); break;
        case 4: recievedGameDetails((*reinterpret_cast< XmlNode*(*)>(_a[1]))); break;
        case 5: on_mp_gameListView_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: on_mp_playButton_clicked(); break;
        case 7: on_mp_spectateButton_clicked(); break;
        case 8: doButtons(); break;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void JoinGameDialog::joinGame(int _t1, QString _t2, bool _t3, QString _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

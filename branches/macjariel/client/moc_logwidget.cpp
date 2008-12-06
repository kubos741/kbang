/****************************************************************************
** Meta object code from reading C++ file 'logwidget.h'
**
** Created: Sat Nov 8 21:35:42 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "logwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LogWidget[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      19,   11,   10,   10, 0x0a,
      45,   11,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_LogWidget[] = {
    "LogWidget\0\0message\0appendLogMessage(QString)\0"
    "appendIncomingXml(QString)\0"
};

const QMetaObject LogWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LogWidget,
      qt_meta_data_LogWidget, 0 }
};

const QMetaObject *LogWidget::metaObject() const
{
    return &staticMetaObject;
}

void *LogWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LogWidget))
        return static_cast<void*>(const_cast< LogWidget*>(this));
    if (!strcmp(_clname, "Ui::LogWidget"))
        return static_cast< Ui::LogWidget*>(const_cast< LogWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int LogWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: appendLogMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: appendIncomingXml((*reinterpret_cast< QString(*)>(_a[1]))); break;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'log_player_tool_bar.h'
**
** Created: Sun Oct 4 21:58:05 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "log_player_tool_bar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'log_player_tool_bar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LogPlayerToolBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   17,   17,   17, 0x08,
      49,   17,   17,   17, 0x08,
      63,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LogPlayerToolBar[] = {
    "LogPlayerToolBar\0\0cycle\0cycleChanged(int)\0"
    "stop()\0playForward()\0playBack()\0"
};

void LogPlayerToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LogPlayerToolBar *_t = static_cast<LogPlayerToolBar *>(_o);
        switch (_id) {
        case 0: _t->cycleChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->stop(); break;
        case 2: _t->playForward(); break;
        case 3: _t->playBack(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LogPlayerToolBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LogPlayerToolBar::staticMetaObject = {
    { &QToolBar::staticMetaObject, qt_meta_stringdata_LogPlayerToolBar,
      qt_meta_data_LogPlayerToolBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LogPlayerToolBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LogPlayerToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LogPlayerToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LogPlayerToolBar))
        return static_cast<void*>(const_cast< LogPlayerToolBar*>(this));
    return QToolBar::qt_metacast(_clname);
}

int LogPlayerToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void LogPlayerToolBar::cycleChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

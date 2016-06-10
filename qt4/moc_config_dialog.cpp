/****************************************************************************
** Meta object code from reading C++ file 'config_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "config_dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'config_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ConfigDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      32,   27,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   13,   13,   13, 0x08,
      71,   65,   13,   13, 0x08,
      92,   13,   13,   13, 0x08,
     124,  116,   13,   13, 0x08,
     148,  116,   13,   13, 0x08,
     173,   65,   13,   13, 0x08,
     197,  192,   13,   13, 0x08,
     219,  116,   13,   13, 0x08,
     249,  243,   13,   13, 0x08,
     271,   13,   13,   13, 0x0a,
     290,   13,   13,   13, 0x0a,
     299,   13,   13,   13, 0x0a,
     309,   13,   13,   13, 0x0a,
     318,   13,   13,   13, 0x0a,
     336,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ConfigDialog[] = {
    "ConfigDialog\0\0configured()\0size\0"
    "canvasResized(QSize)\0updateAll()\0value\0"
    "slideFieldScale(int)\0editFieldScale(QString)\0"
    "checked\0clickShowDrawInfo(bool)\0"
    "clickShowGridCoord(bool)\0slideGridStep(int)\0"
    "text\0editGridStep(QString)\0"
    "clickAntiAliasing(bool)\0point\0"
    "setFocusPoint(QPoint)\0updateFieldScale()\0"
    "zoomIn()\0zoomOut()\0unzoom()\0"
    "applyCanvasSize()\0toggleShowDrawInfo()\0"
};

void ConfigDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ConfigDialog *_t = static_cast<ConfigDialog *>(_o);
        switch (_id) {
        case 0: _t->configured(); break;
        case 1: _t->canvasResized((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 2: _t->updateAll(); break;
        case 3: _t->slideFieldScale((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->editFieldScale((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->clickShowDrawInfo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->clickShowGridCoord((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->slideGridStep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->editGridStep((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->clickAntiAliasing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setFocusPoint((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 11: _t->updateFieldScale(); break;
        case 12: _t->zoomIn(); break;
        case 13: _t->zoomOut(); break;
        case 14: _t->unzoom(); break;
        case 15: _t->applyCanvasSize(); break;
        case 16: _t->toggleShowDrawInfo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ConfigDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ConfigDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ConfigDialog,
      qt_meta_data_ConfigDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ConfigDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigDialog))
        return static_cast<void*>(const_cast< ConfigDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ConfigDialog::configured()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ConfigDialog::canvasResized(const QSize & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

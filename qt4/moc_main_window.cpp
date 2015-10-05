/****************************************************************************
** Meta object code from reading C++ file 'main_window.h'
**
** Created: Sun Oct 4 21:48:03 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "main_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      26,   11,   11,   11, 0x08,
      36,   11,   11,   11, 0x08,
      52,   11,   11,   11, 0x08,
      68,   11,   11,   11, 0x08,
      86,   11,   11,   11, 0x08,
     106,   11,   11,   11, 0x08,
     133,  125,   11,   11, 0x08,
     151,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     178,   11,   11,   11, 0x08,
     203,  198,   11,   11, 0x08,
     229,  223,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0viewUpdated()\0openRCG()\0"
    "toggleMenuBar()\0toggleToolBar()\0"
    "toggleStatusBar()\0toggleFieldCanvas()\0"
    "toggleFullScreen()\0checked\0changeStyle(bool)\0"
    "showConfigDialog()\0about()\0"
    "printShortcutKeys()\0size\0resizeCanvas(QSize)\0"
    "point\0updatePositionLabel(QPoint)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->viewUpdated(); break;
        case 1: _t->openRCG(); break;
        case 2: _t->toggleMenuBar(); break;
        case 3: _t->toggleToolBar(); break;
        case 4: _t->toggleStatusBar(); break;
        case 5: _t->toggleFieldCanvas(); break;
        case 6: _t->toggleFullScreen(); break;
        case 7: _t->changeStyle((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->showConfigDialog(); break;
        case 9: _t->about(); break;
        case 10: _t->printShortcutKeys(); break;
        case 11: _t->resizeCanvas((*reinterpret_cast< const QSize(*)>(_a[1]))); break;
        case 12: _t->updatePositionLabel((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::viewUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE

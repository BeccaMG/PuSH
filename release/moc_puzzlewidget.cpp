/****************************************************************************
** Meta object code from reading C++ file 'puzzlewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../puzzlewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'puzzlewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PuzzleWidget_t {
    QByteArrayData data[6];
    char stringdata[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PuzzleWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PuzzleWidget_t qt_meta_stringdata_PuzzleWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "PuzzleWidget"
QT_MOC_LITERAL(1, 13, 20), // "contextMenuRequested"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "point"
QT_MOC_LITERAL(4, 41, 13), // "deletePieceAt"
QT_MOC_LITERAL(5, 55, 17) // "changeTextPieceAt"

    },
    "PuzzleWidget\0contextMenuRequested\0\0"
    "point\0deletePieceAt\0changeTextPieceAt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PuzzleWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PuzzleWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PuzzleWidget *_t = static_cast<PuzzleWidget *>(_o);
        switch (_id) {
        case 0: _t->contextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->deletePieceAt(); break;
        case 2: _t->changeTextPieceAt(); break;
        default: ;
        }
    }
}

const QMetaObject PuzzleWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PuzzleWidget.data,
      qt_meta_data_PuzzleWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PuzzleWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PuzzleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PuzzleWidget.stringdata))
        return static_cast<void*>(const_cast< PuzzleWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PuzzleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

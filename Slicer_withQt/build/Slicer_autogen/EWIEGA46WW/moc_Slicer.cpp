/****************************************************************************
** Meta object code from reading C++ file 'Slicer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Slicer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Slicer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Slicer_t {
    QByteArrayData data[9];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Slicer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Slicer_t qt_meta_stringdata_Slicer = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Slicer"
QT_MOC_LITERAL(1, 7, 15), // "getGeometryData"
QT_MOC_LITERAL(2, 23, 22), // "Qt3DRender::QGeometry*"
QT_MOC_LITERAL(3, 46, 0), // ""
QT_MOC_LITERAL(4, 47, 10), // "exeSlicing"
QT_MOC_LITERAL(5, 58, 19), // "changeGeometryColor"
QT_MOC_LITERAL(6, 78, 19), // "getGeometryRenderer"
QT_MOC_LITERAL(7, 98, 30), // "Qt3DRender::QGeometryRenderer*"
QT_MOC_LITERAL(8, 129, 31) // "Qt3DRender::QPickTriangleEvent*"

    },
    "Slicer\0getGeometryData\0Qt3DRender::QGeometry*\0"
    "\0exeSlicing\0changeGeometryColor\0"
    "getGeometryRenderer\0Qt3DRender::QGeometryRenderer*\0"
    "Qt3DRender::QPickTriangleEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Slicer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   34,    3, 0x02 /* Public */,
       4,    1,   37,    3, 0x02 /* Public */,
       5,    1,   40,    3, 0x02 /* Public */,
       6,    2,   43,    3, 0x02 /* Public */,

 // methods: parameters
    0x80000000 | 2, 0x80000000 | 2,    3,
    0x80000000 | 2, 0x80000000 | 2,    3,
    0x80000000 | 2, 0x80000000 | 2,    3,
    0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 8,    3,    3,

       0        // eod
};

void Slicer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Slicer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { Qt3DRender::QGeometry* _r = _t->getGeometryData((*reinterpret_cast< Qt3DRender::QGeometry*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Qt3DRender::QGeometry**>(_a[0]) = std::move(_r); }  break;
        case 1: { Qt3DRender::QGeometry* _r = _t->exeSlicing((*reinterpret_cast< Qt3DRender::QGeometry*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Qt3DRender::QGeometry**>(_a[0]) = std::move(_r); }  break;
        case 2: { Qt3DRender::QGeometry* _r = _t->changeGeometryColor((*reinterpret_cast< Qt3DRender::QGeometry*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Qt3DRender::QGeometry**>(_a[0]) = std::move(_r); }  break;
        case 3: { Qt3DRender::QGeometryRenderer* _r = _t->getGeometryRenderer((*reinterpret_cast< Qt3DRender::QGeometryRenderer*(*)>(_a[1])),(*reinterpret_cast< Qt3DRender::QPickTriangleEvent*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< Qt3DRender::QGeometryRenderer**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Qt3DRender::QGeometry* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Qt3DRender::QGeometry* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Qt3DRender::QGeometry* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Qt3DRender::QGeometryRenderer* >(); break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Qt3DRender::QPickTriangleEvent* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Slicer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Slicer.data,
    qt_meta_data_Slicer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Slicer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Slicer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Slicer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Slicer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

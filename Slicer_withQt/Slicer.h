/*
 *qmlとスライサの兼ね合い関連
*/
#include <QDateTime>
#include <QObject>
#include <QString>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QGeometry>
#include <QGeometryRenderer>
#include <QVector>
#include <QList>
#include <QUrl>

#include <QPickTriangleEvent>
#include "slice_data.h"
#include "Slicing.h"


class Slicer : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE Qt3DRender::QGeometry* getGeometryData(Qt3DRender::QGeometry *);
    Q_INVOKABLE Qt3DRender::QGeometry* exeSlicing(Qt3DRender::QGeometry *);
    Q_INVOKABLE Qt3DRender::QGeometry* changeGeometryColor(Qt3DRender::QGeometry *);
    Q_INVOKABLE Qt3DRender::QGeometryRenderer* getGeometryRenderer(Qt3DRender::QGeometryRenderer *, Qt3DRender::QPickTriangleEvent *);
private:
    Slicing slicing;
};
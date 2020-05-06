#include <Qt3DQuickExtras/qt3dquickwindow.h>
#include <QQuickView>
#include <QGuiApplication>
#include <QQmlContext>
#include <QSurfaceFormat>
#include "Slicer.h"
#include "slice_data.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;
    Slicer slicer;
    
    QSurfaceFormat format;
    format.setVersion(3,3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    view.setFormat(format);

    view.rootContext()->setContextProperty("slicer", &slicer);
    view.resize(500, 500);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("../main.qml"));
    view.show();

    return app.exec();
}
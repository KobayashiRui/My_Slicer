import Qt3D.Core 2.0
import Qt3D.Render 2.14
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import QtQuick 2.0 as QQ2
import QtQuick.Scene3D 2.0



Entity {
    property alias pathData : path_geometry_renderer
    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 50.0, 50.0, 80.0 )
        upVector: Qt.vector3d( 0.0, 0.0, 1.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    SOrbitCameraController {
        id: cameraController
        camera: camera
        linearSpeed : 150
        zoomLimit : 80
    }

    Layer {
        id: topLayer
        recursive: true
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "transparent"
            }
            pickingSettings.pickMethod: PickingSettings.TrianglePicking
            pickingSettings.pickResultMode: PickingSettings.AllPicks
            pickingSettings.faceOrientationPickingMode: PickingSettings.FrontAndBackFace

        },
        InputSettings { }
    ]


    GeometryRenderer{
        id:path_geometry_renderer
        primitiveType : GeometryRenderer.LineStrip

    }

    Transform {
        id: path_transform
        scale3D: Qt.vector3d(0.5, 0.5, 0.5)
        rotation: fromAxisAndAngle(Qt.vector3d(1.0, 0, 0), 0.0)
    }

    PhongMaterial {
        id: path_material
        //ambient : Qt.rgba(0.5,0.5,0.5,0.7)
    }

    Entity {
        id: stlEntity
        components: [ path_geometry_renderer, path_material, path_transform]
    }

    TestMaterial{ 
        id:testMaterial
    }
    PlaneMesh{
        id:planeMesh
        height:150
        width:150
    }
    Transform {
        id: planeTransform
        rotation: fromAxisAndAngle(Qt.vector3d(1.0, 0.0, 0), 90.0)
    }
    Entity {
        id: planeEntity
        components: [ planeMesh, testMaterial, planeTransform]
    }

}
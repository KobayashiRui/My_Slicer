import Qt3D.Core 2.0
import Qt3D.Render 2.14
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import QtQuick 2.0 as QQ2
import QtQuick.Scene3D 2.0



Entity {
    property alias stlData : stlEntity
    property alias stlMeshData : stlMesh
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

    TransformGizmo {
        id: tg
        layer: topLayer
        cameraController: cameraController
        camera: camera
        scene3d_data: scene3d
        size: 0.125 * absolutePosition.minus(camera.position).length()
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

    PhongMaterial {
        id: material
        ambient : Qt.rgba(0.5,0.5,0.5,0.7)
    }

    PerVertexColorMaterial{
        id : vertexmaterial
    }


    TorusMesh {
        id: torusMesh
        radius: 5
        minorRadius: 1
        rings: 100
        slices: 20
    }

    Transform {
        id: torusTransform
        scale3D: Qt.vector3d(1.5, 1, 0.5)
        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 45)
    }

    Transform {
        id: stlTransform
        scale3D: Qt.vector3d(0.5, 0.5, 0.5)
        rotation: fromAxisAndAngle(Qt.vector3d(1.0, 0, 0), 0.0)
    }

    Entity {
        id: stlEntity
        components: [ geomeTest, vertexmaterial, stlTransform, geomePicker]
        //ObjectPicker:{
        //}
    }

    ObjectPicker{
        id:geomePicker
       onClicked:{
         //tg.attachTo(stlEntity)
         console.log("width:"+scene3d.width)
         console.log("height:"+scene3d.height)
         console.log("Pressed at: " + pick.worldIntersection)
         console.log("Triangle index: " + pick.triangleIndex)
         console.log("vertex index1: " + pick.vertex1Index)
         console.log("vertex index2: " + pick.vertex2Index)
         console.log("point index: " + pick.pointIndex )
         let geometry  = pick.entity.components[0].geometry
         console.log(geometry.maxExtent)
         console.log(geometry.attributes)
         console.log("maxExtent: " + geometry.maxExtent)
         console.log("minExtent: " + geometry.minExtent)
         //let geor = application.getGeometryRenderer(pick.entity.components[0])
         //let geom_ = application.getGeometryData(geometry)
         //let geom = application.changeGeometryColor(geometry)
         let geom = slicer.getGeometryRenderer(pick.entity.components[0], pick)
         console.log("end")
         //pick.entity.component[0] = geor
         //pick.entity.components[0] = geom
         //sphereMesh.geometry = geometry

       }
    }


    SphereMesh {
        id: sphereMesh
        //primitiveType :GeometryRenderer.Points
        radius: 3
    }
    GeometryRenderer{
        id: geomeTest
        geometry:stlMesh.geometry
        //primitiveType :GeometryRenderer.Lines
        //Component.onCompleted: {
        //    console.log("complete!!")
        //}
    }

    Mesh{
        id: stlMesh
        source:""
    }

    //OriginMesh{
    //    id:testMesh
    //    source:"3DBenchy.stl"
    //}
    TestMaterial{ 
        id:testMaterial
    }
    PlaneMesh{
        id:planeMesh
        height:150
        width:150
        //primitiveType :GeometryRenderer.Lines
    }
    Transform {
        id: planeTransform
        rotation: fromAxisAndAngle(Qt.vector3d(1.0, 0.0, 0), 90.0)
    }
    ObjectPicker{ 
        id:testPicker
        onPressed: {
            console.log("pic")
        }
    }


    Entity {
        id: planeEntity
        components: [ planeMesh, testMaterial, planeTransform, testPicker]
    }

}
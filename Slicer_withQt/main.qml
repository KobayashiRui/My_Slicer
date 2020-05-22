import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Scene3D 2.0
import QtQuick.Dialogs 1.0
import Qt3D.Render 2.10

Item {
    id:root
    SlicerMeshScene {}

    FileDialog {
        id: fileDialog
        //visible: fileDialogVisible.checked
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls[0])
            root3d.stlMeshData.source = fileDialog.fileUrls[0];
            //meshdata.source = fileDialog.fileUrls[0];
            if(root3d.stlMeshData.status == Mesh.Ready){
                console.log("read sucess")
            }else{
                console.log(root3d.stlMeshData.status)
                console.log("not read")
                root3d.stlMeshData.statusChanged.connect(()=>{
                    if(root3d.stlMeshData.status == Mesh.Ready){
                        console.log("read sucess"); 
                        slicer.changeGeometryColor(root3d.stlMeshData.geometry)
                    }
                    })
            }
            console.log("end")
            
        }
        onRejected: {
            console.log("Canceled")
            //Qt.quit()
        }
    }
    Row{

    Column{
        id:control_buttons
        Button {
            text:"Get Mesh"
            onClicked: {
                console.log("get Mesh");
                fileDialog.open()
                //application.testfunc()
                //application.getMeshData(root3d.animatedMesh)
            }
        }
        Button {
            text:"Slice"
            onClicked: {
                //console.log("change color");
                root3d_2.pathData.geometry = slicer.exeSlicing(root3d.stlMeshData.geometry)
                //slicer.exeSlicing(root3d.stlMeshData.geometry)
                //application.changeGeometryColor(root3d.stlData.components[0].geometry)
                //application.testfunc()
                //application.getMeshData(root3d.animatedMesh)
            }
        }
        Button {
            text:"Mesh"
            onClicked: {
                scene.visible = true;
                scene_2.visible = false;
            }
        }
        Button {
            text:"Path"
            onClicked: {
                console.log("path");
                //console.log(root3d_2.pathData.geometry.attributes.length())
                scene.visible = false;
                scene_2.visible = true;
                
            }
        }
        Switch{
            id: arc_mode
            text:"Arc Mode"
            onClicked:{
                console.log("Switch")
                console.log(arc_mode.checked)
                console.log(root.height)
                console.log(root.width)
            }
        }
    }

    Rectangle {
        id: scene
        //anchors.fill: parent
        //anchors.margins: 50
        color: "White"
        width:root.width-control_buttons.width
        height:root.height

        transform: Rotation {
            id: sceneRotation
            axis.x: 1
            axis.y: 0
            axis.z: 0
            origin.x: scene.width / 2
            origin.y: scene.height / 2
        }

        Scene3D {
            id: scene3d
            //width:300
            //height:300
            anchors.fill: parent
            anchors.margins: 10
            focus: true
            aspects: ["render","input", "logic"]
            hoverEnabled: true // needed for ObjectPickers to handle hover events

            cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

            SlicerMeshScene {
                id:root3d
            }
        }
    }

    Rectangle {
        id: scene_2
        visible : false
        //anchors.fill: parent
        //anchors.margins: 50
        color: "White"
        width:root.width-control_buttons.width
        height:root.height

        transform: Rotation {
            id: sceneRotation_2
            axis.x: 1
            axis.y: 0
            axis.z: 0
            origin.x: scene.width / 2
            origin.y: scene.height / 2
        }

        Scene3D {
            id: scene3d_2
            //width:300
            //height:300
            anchors.fill: parent
            anchors.margins: 10
            focus: true
            aspects: ["render","input", "logic"]
            hoverEnabled: true // needed for ObjectPickers to handle hover events

            cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

            SlicerPathScene  {
                id:root3d_2
            }
        }
    }
    }

}
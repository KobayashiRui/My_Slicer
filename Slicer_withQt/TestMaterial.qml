import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0


Material {
    id:root

    parameters: [
        Parameter { name: "lightPosition"; value: Qt.vector4d(1.0, 1.0, 0.0, 1.0) },
        Parameter { name: "lightIntensity"; value: Qt.vector3d(1.0, 1.0, 1.0) }
    ]

    ShaderProgram {
        id: gl3PerVertexColorShader
        vertexShaderCode: loadSource("qrc:/testvertexcolor.vert")
        fragmentShaderCode: loadSource("qrc:/testvertexcolor.frag")
    }

    effect: Effect {
        techniques: [
            // GL 3 Technique
            Technique {
                filterKeys: [ FilterKey { name: "renderingStyle"; value: "forward" } ]
                graphicsApiFilter  {
                api: GraphicsApiFilter.OpenGL
                profile: GraphicsApiFilter.CoreProfile
                    majorVersion: 3
                    minorVersion: 1
                }
                renderPasses: RenderPass {
                    shaderProgram: gl3PerVertexColorShader
                }
            }
        ]
    }
}
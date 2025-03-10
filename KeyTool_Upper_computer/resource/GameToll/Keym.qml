import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources
    PrincipledMaterial {
        id: ___material
        objectName: "材质"
        baseColor: "#ff7487ff"
    }

    // Nodes:
    Node {
        id: keym_obj
        objectName: "keym.obj"
        Model {
            id: __
            objectName: "平面"
            source: "meshes/___mesh.mesh"
            materials: [
                ___material
            ]
        }
    }

    // Animations:
}

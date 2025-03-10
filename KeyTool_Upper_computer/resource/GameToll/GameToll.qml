import QtQuick
import QtQuick3D

Node {
    id: node

    // Resources

    // Nodes:
    Node {
        id: gameToll_obj
        objectName: "GameToll.obj"
        Model {
            id: defaultobject
            objectName: "defaultobject"
            source: "meshes/defaultobject_mesh.mesh"
            materials: [
                mtl1_material,
                mtl2_material,
                mtl3_material,
                mtl4_material,
                mtl5_material,
                mtl6_material,
                mtl1_material,
                mtl2_material,
                mtl3_material,
                mtl4_material,
                mtl5_material,
                mtl6_material,
                mtl1_material,
                mtl2_material,
                mtl3_material,
                mtl4_material,
                mtl5_material,
                mtl6_material,
                mtl7_material,
                mtl8_material,
                mtl9_material,
                mtl5_material,
                mtl7_material,
                mtl8_material,
                mtl9_material,
                mtl5_material,
                mtl10_material,
                mtl11_material,
                mtl12_material,
                mtl13_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl4_material,
                mtl1_material,
                mtl2_material,
                mtl4_material,
                mtl1_material,
                mtl2_material,
                mtl15_material,
                mtl16_material,
                mtl5_material,
                mtl17_material,
                mtl15_material,
                mtl18_material,
                mtl19_material,
                mtl20_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl9_material,
                mtl17_material,
                mtl21_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl15_material,
                mtl25_material,
                mtl5_material,
                mtl17_material,
                mtl9_material,
                mtl7_material,
                mtl26_material,
                mtl5_material,
                mtl27_material,
                mtl28_material,
                mtl13_material,
                mtl29_material,
                mtl30_material,
                mtl31_material,
                mtl1_material,
                mtl32_material,
                mtl5_material,
                mtl33_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl14_material,
                mtl4_material,
                mtl5_material,
                mtl15_material,
                mtl25_material,
                mtl5_material,
                mtl17_material,
                mtl15_material,
                mtl25_material,
                mtl5_material,
                mtl17_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl22_material,
                mtl2_material,
                mtl1_material,
                mtl23_material,
                mtl24_material,
                mtl34_material,
                mtl35_material,
                mtl36_material,
                mtl37_material,
                mtl36_material,
                mtl37_material,
                mtl36_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl37_material,
                mtl36_material,
                mtl37_material,
                mtl35_material,
                mtl34_material
            ]
        }
    }

    Node {
        id: __materialLibrary__

        PrincipledMaterial {
            id: mtl1_material
            objectName: "mtl1"
            baseColor: "#ff404040"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl2_material
            objectName: "mtl2"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl3_material
            objectName: "mtl3"
            baseColor: "#ffffff00"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl4_material
            objectName: "mtl4"
            baseColor: "#ffd9d9d9"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl5_material
            objectName: "mtl5"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl6_material
            objectName: "mtl6"
            baseColor: "#ff00abff"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl7_material
            objectName: "mtl7"
            baseColor: "#ffababab"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl8_material
            objectName: "mtl8"
            baseColor: "#ffb3b3b3"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl9_material
            objectName: "mtl9"
            baseColor: "#ff363636"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl10_material
            objectName: "mtl10"
            baseColor: "#ffd9d9d9"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl11_material
            objectName: "mtl11"
            baseColor: "#ff2e2e2e"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl12_material
            objectName: "mtl12"
            baseColor: "#fff2c22e"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl13_material
            objectName: "mtl13"
            baseColor: "#ff383838"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl14_material
            objectName: "mtl14"
            baseColor: "#ff967500"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl15_material
            objectName: "mtl15"
            baseColor: "#ff404040"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl16_material
            objectName: "mtl16"
            baseColor: "#ffa1a1a1"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl17_material
            objectName: "mtl17"
            baseColor: "#ffc4c4c4"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl18_material
            objectName: "mtl18"
            baseColor: "#ffd9d9d9"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl19_material
            objectName: "mtl19"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl20_material
            objectName: "mtl20"
            baseColor: "#ff383838"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl21_material
            objectName: "mtl21"
            baseColor: "#ff57d669"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl22_material
            objectName: "mtl22"
            baseColor: "#ff804000"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl23_material
            objectName: "mtl23"
            baseColor: "#ffbfbfbf"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl24_material
            objectName: "mtl24"
            baseColor: "#ff000000"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl25_material
            objectName: "mtl25"
            baseColor: "#ff736e6b"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl26_material
            objectName: "mtl26"
            baseColor: "#ffd4ab21"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl27_material
            objectName: "mtl27"
            baseColor: "#ff40424f"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl28_material
            objectName: "mtl28"
            baseColor: "#ffe3e3e3"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl29_material
            objectName: "mtl29"
            baseColor: "#ffa69e96"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl30_material
            objectName: "mtl30"
            baseColor: "#fff7e099"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl31_material
            objectName: "mtl31"
            baseColor: "#ff8282a1"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl32_material
            objectName: "mtl32"
            baseColor: "#ffd9d9d9"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl33_material
            objectName: "mtl33"
            baseColor: "#ffe6c7b0"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl34_material
            objectName: "mtl34"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl35_material
            objectName: "mtl35"
            baseColor: "#ff0054a6"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl36_material
            objectName: "mtl36"
            baseColor: "#ff9e9e5c"
            indexOfRefraction: 1
        }

        PrincipledMaterial {
            id: mtl37_material
            objectName: "mtl37"
            baseColor: "#ff00265c"
            indexOfRefraction: 1
        }
    }

    // Animations:
}

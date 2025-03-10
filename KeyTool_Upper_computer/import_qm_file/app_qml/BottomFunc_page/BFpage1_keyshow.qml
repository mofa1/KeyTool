import QtQuick
import QtQuick.Controls

Rectangle {
    property var key_list: []
    onKey_listChanged: {
        if (key_list.length > 0 && key_list[0] !== undefined) {
            // 通过映射表查找对应字母，找不到时显示空格
            page1label.text = keytables.conversionTables[key_list[0]] || " ";
        } else {
            page1label.text = " ";
        }
    }
    width: 100
    height: 100
    border { color: "#541e24"; width: 3 }
    radius: 10
    Label {
        id: page1label
        text: " "
        font.pixelSize: 56
        anchors.centerIn: parent
    }
    ConversionTable {
        id: keytables
    }
}


import QtQuick
import QtQuick.Layouts

/*这是主页*/

Item {
    property var bfpage1list: []
    onBfpage1listChanged: {
        // 截取索引 0-1 的子数组（不包含索引2）
        keyshow1.key_list = bfpage1list.slice(0, 2);
        // 截取索引 2-3 的子数组
        keyshow2.key_list = bfpage1list.slice(2, 4);
        // 截取索引 4-5 的子数组
        keyshow3.key_list = bfpage1list.slice(4, 6);
    }

    RowLayout {
        anchors.fill: parent
        spacing: 80
        /*主页三个按键*/
        Item {
            Layout.fillWidth: true
        }
        BFpage1_keyshow {
            id: keyshow1
        }
        BFpage1_keyshow {
            id: keyshow2
        }
        BFpage1_keyshow {
            id: keyshow3
        }
        Item {
            Layout.fillWidth: true
        }
    }
}

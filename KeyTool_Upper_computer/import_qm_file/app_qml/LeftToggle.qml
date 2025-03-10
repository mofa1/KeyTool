import QtQuick
import QtQuick.Controls.Basic

Item {
    id: left_tool_root
    signal butidChanged(int num);
    property int selectedButtonId: 0 // 用于跟踪选中的按钮ID

    Rectangle {
        id: leftline
        color: "#3f9cd6"
        width: 5; height: parent.width
        anchors.left: parent.left
        z: 1
    }

    Rectangle {
        id: rootrect
        anchors.fill: parent
        color: "#5e5f60"

        Button {
            id: setbut
            width: rootrect.width;height:rootrect.width
            icon.color: "transparent"
            icon.source: {
                if (left_tool_root.selectedButtonId === 2) {
                    return "qrc:/icon/resource/image/icon/设置.svg" // 选中状态
                } else if (setbut.hovered) {
                    return "qrc:/icon/resource/image/icon/设置.svg" // 悬停状态
                } else {
                    return "qrc:/icon/resource/image/icon/设置_灰.svg" // 默认状态
                }
            }
            anchors {
                bottom: parent.bottom
                bottomMargin: 20
            }
            onClicked: {
                leftline.y = setbut.y;
                left_tool_root.selectedButtonId = 2;
                butidChanged(2);
            }

            background: Rectangle {
                color: "transparent"   // 背景完全透明[1,2](@ref)
                border.width: 0        // 移除默认边框[2](@ref)
            }
        }
    }

    ObjectModel {
        id: objectmodel
        Button {
            id: but_home
            width: rootrect.width;height:rootrect.width
            icon.color: "transparent"
            icon.source: {
                if (left_tool_root.selectedButtonId === 0) {
                    return "qrc:/icon/resource/image/icon/主页.svg" // 选中状态
                } else if (but_home.hovered) {
                    return "qrc:/icon/resource/image/icon/主页.svg" // 悬停状态
                } else {
                    return "qrc:/icon/resource/image/icon/主页_灰.svg" // 默认状态
                }
            }
            onClicked: {
                butidChanged(0); // 发送信号
                leftline.y = but_home.y;
                left_tool_root.selectedButtonId = 0;
            }
            background: Rectangle {
                color: "transparent"   // 背景完全透明[1,2](@ref)
                border.width: 0        // 移除默认边框[2](@ref)
            }
        }
        Button {
            id: but_key
            hoverEnabled: true // 开启悬停
            width: rootrect.width;height:rootrect.width
            // text: "按键"
            icon.color: "transparent"
            icon.source: {
                if (left_tool_root.selectedButtonId === 1) {
                    return "qrc:/icon/resource/image/icon/键盘.svg" // 选中状态
                } else if (but_key.hovered) {
                    return "qrc:/icon/resource/image/icon/键盘.svg" // 悬停状态
                } else {
                    return "qrc:/icon/resource/image/icon/键盘_灰.svg" // 默认状态
                }
            }
            onClicked: {
                butidChanged(1);
                leftline.y = but_key.y;
                left_tool_root.selectedButtonId = 1;
            }
            background: Rectangle {
                color: "transparent"   // 背景完全透明[1,2](@ref)
                border.width: 0        // 移除默认边框[2](@ref)
            }
        }
    }

    ListView {
        id: rectview
        width: rootrect.width;height:rootrect.height-setbut.height
        model: objectmodel
        interactive: false // 禁用列表滚动
    }
}

import QtQuick
import QtQuick.Controls.Basic

Item {
    id: titleBar
    property int but_width: titleBar.height + 20
    property string title_color: "#f1f3f9"

    function adjustWindowContentMarginsWhenMaximized(left_margin,right_margin,top_margin,bottom_margin) {
        anchors.leftMargin = left_margin
        anchors.rightMargin = right_margin
        anchors.topMargin = top_margin
        anchors.bottomMargin = bottom_margin
    }

    Rectangle {
        id: rect1
        width: titleBar.width; height: titleBar.height
        color: title_color
        /*鼠标拖动标题栏*/
        MouseArea {
            anchors.fill: parent
            DragHandler {
                onActiveChanged: {
                    if (active) {
                        win.startSystemMove();
                    }
                }
            }
            onDoubleClicked: {
                if (win.visibility === Window.Maximized) {
                    win.showNormal();
                } else {
                    win.showMaximized();
                }
            }
        }

        /*最小化按钮*/
        Button {
            property string bt_min_icon: "qrc:/icon/resource/image/icon/mini.svg"
            id: bt_min
            width: but_width
            height: titleBar.height
            anchors.right: parent.right
            anchors.rightMargin: but_width*2
            icon.color: "transparent"
            icon.source: bt_min_icon

            onClicked: {
                win.showMinimized();
            }

            // 按钮触发状态 悬停 按下 松开
            background: Rectangle {
                id: color_min
                opacity: enabled ? 1 : 0.3
                color: title_color
                states: [
                    State {
                        name: "dowm"
                        when: bt_min.down
                        PropertyChanges {
                            target: color_min
                            color: "#ebedf3"
                        }
                    },
                    State {
                        name: "hovered"
                        when: bt_min.hovered
                        PropertyChanges {
                            target: color_min
                            color: "#e9e9e9"
                        }
                    }
                ]

            }
        }

        /*缩放按钮*/
        Button {
            property string bt_max_icon: "qrc:/icon/resource/image/icon/max.svg" // 缩放按钮
            property string bt_normal_icon: "qrc:/icon/resource/image/icon/nor.svg" // 缩放按钮
            id: bt_max_nor
            width: but_width;height: titleBar.height
            anchors.right: parent.right
            anchors.rightMargin: but_width*1
            icon.color: "transparent"
            icon.source: {
                if (win.visibility === Window.Maximized){
                    return bt_normal_icon;
                }else{
                    return bt_max_icon;
                }
            }

            onClicked: {
                if (win.visibility === Window.Maximized) {
                    win.showNormal();
                } else {
                    win.showMaximized();
                }
            }

            // 按钮触发状态 悬停 按下 松开
            background: Rectangle {
                id: color_max_nor
                opacity: enabled ? 1 : 0.3
                color: title_color
                states: [
                    State {
                        name: "dowm"
                        when: bt_max_nor.down
                        PropertyChanges {
                            target: color_max_nor
                            color: "#ebedf3"
                        }
                    },
                    State {
                        name: "hovered"
                        when: bt_max_nor.hovered
                        PropertyChanges {
                            target: color_max_nor
                            color: "#e9e9e9"
                        }
                    }
                ]
            }
        }

        /*关闭按钮*/
        Button {
            property string defaultIcon: "qrc:/icon/resource/image/icon/close_black.svg"
            property string hoverIcon: "qrc:/icon/resource/image/icon/close_white.svg"
            property string pressedIcon: "qrc:/icon/resource/image/icon/close_white.svg"
            id: bt_close
            width: but_width
            height: titleBar.height
            anchors.right: parent.right
            icon.color: "transparent"
            icon.source: {
                if (bt_close.down) {
                    return pressedIcon;
                } else if (bt_close.hovered) {
                    return hoverIcon;
                } else {
                    return defaultIcon;
                }
            }
            onClicked: {
                win.close();
            }
            background: Rectangle {
                id: color_close
                opacity: enabled ? 1 : 0.3
                color: title_color // 默认颜色
                states: [
                    State {
                        name: "down"
                        when: bt_close.down
                        PropertyChanges {
                            target: color_close
                            color: "#c84031" // 按下时的背景颜色
                        }
                    },
                    State {
                        name: "hovered"
                        when: bt_close.hovered
                        PropertyChanges {
                            target: color_close
                            color: "#c42b1c"// 悬停时的背景颜色
                        }
                    }
                ]
            }
        }
    }
}



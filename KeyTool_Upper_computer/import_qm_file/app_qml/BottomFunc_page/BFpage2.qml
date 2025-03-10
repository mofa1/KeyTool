import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: item
            property color color_send: "#3f9cd6"
    property var needdata: new Array(6).fill(null) // 初始化为6个null的数组
    property bool connect_state0: false
    property bool sixdata: false
    signal sendtocpp
    signal needdatasix(var needdatas) // 存在6个数据发送的信号

    onNeeddataChanged: {
        // 检查所有元素是否非空且长度为6
        const isValid = needdata.length === 6 && needdata.every(item => item !== null);
        sixdata = isValid;
        button_send.enabled = connect_state0 && isValid;
        if (isValid) needdatasix(needdata);
    }
    onConnect_state0Changed: {
        if (connect_state0&&sixdata){
            button_send.enabled = true;
        }else{
            button_send.enabled = false;
        }
    }

    Button {
        id: button_send
        width: 80; height: 50
        z:1
        anchors {
            right: item.right
            verticalCenter: item.verticalCenter
            rightMargin: 50
        }
        contentItem: Text {
            text: "发送"
            color: "white"
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        enabled: false
        onClicked: {
            sendtocpp();
        }
        background: Rectangle {
            id: button_send_rect
            opacity: enabled ? 1 : 0.3
            color: color_send
            border.width: 2
            border.color: "blue"
            states: [
                State {
                    name: "down"
                    when: button_send.down
                    PropertyChanges {
                        target: button_send_rect
                        color: "#026ec1" // 按下时的背景颜色
                    }
                },
                State {
                    name: "hovered"
                    when: button_send.hovered
                    PropertyChanges {
                        target: button_send_rect
                        color: "#026ec1"// 悬停时的背景颜色
                    }
                }
            ]
        }
    }

    Rectangle {
        anchors.fill: parent
        border{
            color: "#541e24";
            width: 3
        }
        RowLayout {
            anchors {
                horizontalCenter: parent.horizontalCenter // 父级水平居中
                verticalCenter:   parent.verticalCenter
            }
            spacing: 85
            BFpage2_keyset {
                id :bf1
                width: item.width/1.8;height: item.height/2
                Layout.alignment: Qt.AlignLeft    // 添加水平左
                onKeydataChanged: (keydata)=>{

                    needdata.splice(0, 2, keydata[0],keydata[1]);
                                      needdata = [...needdata]; // 强制更新
                    console.log(needdata);
                }
            }
            BFpage2_keyset {
                id :bf2
                width: item.width/1.8;height: item.height/2
                Layout.alignment: Qt.AlignHCenter // 添加水平居中
                onKeydataChanged: (keydata)=>{
                                      needdata.splice(2, 2, keydata[0],keydata[1]);
                                      needdata = [...needdata]; // 强制更新
                                      console.log(needdata);
                }
            }
            BFpage2_keyset {
                id :bf3
                width: item.width/1.8;height: item.height/2
                Layout.alignment: Qt.AlignRight    // 添加水平右
                onKeydataChanged: (keydata)=>{
                                      needdata.splice(4, 2, keydata[0],keydata[1]);
                                      needdata = [...needdata]; // 强制更新
                                      console.log(needdata);
                }
            }
        }

    }
}

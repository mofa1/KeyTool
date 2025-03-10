import QtQuick
import QtQuick.Controls

/*这是显示设备是否连接的指示*/
Item {
    property bool connectInd: false // 判断设备是否连接

    Rectangle{
        id: statein
        width: 20;height: 20
        color: "red"
        radius: 30
        anchors{
            right: deviceState.left
            rightMargin: 10
            verticalCenter: parent.verticalCenter
        }
    }
    Label {
        id: deviceState
        text: "设备未连接"
        font.pixelSize: 18
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 20
        }
    }
    onConnectIndChanged: {
        if (connectInd) {
            statein.color = "green"
            deviceState.text = "设备已连接"
        } else {
            statein.color = "red"
            deviceState.text = "设备未连接"
        }
    }

}

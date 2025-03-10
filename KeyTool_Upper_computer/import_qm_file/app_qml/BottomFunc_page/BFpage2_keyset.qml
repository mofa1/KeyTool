import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

Item {
    property int new_releaseTime: 0   // 新的按键释放时间
    property int last_releaseTime: 0   // 上一次按键释放时间
    property string keystext: ""       // 键盘字符串表达式
    property string keystextnew: ""    // 用于更新Label值
    property int keysvalue: 0          // 按键的QT枚举值
    property bool keycontentflag: false // 按键识别区域是否有内容
    signal keydataChanged(var keydata) // 将识别框内数据发送
    onKeystextnewChanged: {
        label1.visible = false;
        keycontentflag = true;
    }

    /*
    键盘输入
    1.单次点击两次释放间隔在50ms以上
    2.长按后触发的释放释放时间在30ms左右,小于50ms
    键盘输入规则 [1,2]
    [1]第一位数据
    1. 键盘的键值
    [2]第二位数据
    1. 0x00 短按
    2. 0x01 长按
    */
    focus: true
    Keys.onPressed: (event)=> {
                        // console.log(holdtimer);
                        let key = event.text || event.key;
                        if (/[a-zA-Z]/.test(key)) {// 检查 key 是否是一个字母
                            let upperCaseKey = key.toUpperCase();// 将字母转换为大写
                            keystext = upperCaseKey;
                        }else{
                            keystext = event.key;  // 不是字母的直接显示键值
                        }
                        keysvalue = event.key;
                    }
    Keys.onReleased: {
        var keydata = [];
        new_releaseTime = Date.now(); // 记录释放时间
        let interval = new_releaseTime - last_releaseTime;
        if (interval<80){
            // console.log(`长按`);
            keystextnew = `${keystext}`;
            lab1.text = "键盘长按";
            keydata = [keysvalue,0x01];
        }else{
            // console.log(`短按`);
            keystextnew = `${keystext}`;
            lab1.text = "键盘短按";
            keydata = [keysvalue,0x00];
        }
        keydataChanged(keydata);          // 发送信号
        last_releaseTime = new_releaseTime
        new_releaseTime = 0;
    }

    /*鼠标输入规则 与嵌入式设备对应[1,2]
    [1]第一位数据
    1. 0x01 左键
    2. 0x02 右键
    [2]第二位数据
    1. 0x02 左键短按
    2. 0x03 左键长按
    3. 0x04 右键短按
    4. 0x05 右键长按
    */
    Rectangle {
        id: rectkeyset1
        anchors.fill: parent
        border {color: "skyblue";width: 3}
        Rectangle {
            id: rectkeyset2
            anchors {
                top: rectkeyset1.top
                horizontalCenter: rectkeyset1.horizontalCenter
                topMargin: -rectkeyset2.height/2
            }
            width: 0;height: 50
            z:1
            Label {
                id: lab1
                anchors.fill: parent
                font.pixelSize: 16
                visible: false
                text: "正在识别"
                color: "green"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        /*动画*/
        SequentialAnimation {
            id: testanima
            running: false
            loops: 1
            NumberAnimation {
                id: testanima_1
                target: rectkeyset2
                property: "width"
                duration: 50;
                to: 70;
                easing.type: Easing.InQuad
            }
            onFinished: {
                if (testanima_1.to === 70){
                    lab1.visible = true;
                }else{

                }
                // 你可以在这里执行其他操作，例如重置动画或改变状态
            }
        }
        MouseArea {
            anchors.fill: parent
            hoverEnabled: true  // 启用悬停事件
            acceptedButtons: Qt.LeftButton | Qt.RightButton // 添加这行
            onClicked: (mouse)=> {
                           var mousevalue = [];
                           if (mouse.button === Qt.LeftButton) {
                               keystextnew = "🖱"
                               lab1.text = "左键短按";
                               mousevalue = [0x01,0x02]
                           } else if (mouse.button === Qt.RightButton) {
                               keystextnew = "🖱"
                               lab1.text = "右键短按";
                               mousevalue = [0x02,0x03]
                           }
                           keydataChanged(mousevalue);
                       }
            onPressAndHold:(mouse)=> {
                               var mousevalue_hold = [];
                               if (mouse.button === Qt.LeftButton) {
                                   keystextnew = "🖱"
                                   lab1.text = "左键长按";
                                   mousevalue_hold = [0x01,0x04];
                               } else if (mouse.button === Qt.RightButton) {
                                   keystextnew = "🖱"
                                   lab1.text = "右键长按";
                                   mousevalue_hold = [0x02,0x05];
                               }
                               keydataChanged(mousevalue_hold);
                           }
            onEntered: {
                parent.focus = true;
                // console.log("获得焦点")
                testanima_1.to = 70;
                testanima.running = true;
            }
            onExited: {
                parent.focus = false;
                if (!keycontentflag){
                    lab1.visible = false;
                    rectkeyset2.width = 0;
                }
            }
        }

        Label { // 识别区域
            id: label1
            anchors.fill: parent
            font.pixelSize: 26
            text: "识别区域"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        /*[3] 识别区域*/
        Label { // 识别区域
            id: label2
            anchors.fill: parent
            font.pixelSize: 42
            text: keystextnew
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

    }
}

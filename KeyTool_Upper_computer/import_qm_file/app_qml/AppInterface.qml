import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import GameTool
/*应用界面
    [0] 需要实例化的界面
    [1] 左侧切换栏   leftToggle
    [2] 模型展示区域  modelShow
    [3] 底部功能栏   bottomFunc
*/
Item {
    // [0] 需要实例化的界面
    property bool connectstate: false
    property int page_id: 0

    MySerial {
        id: mySerial
    }
    Connections { // 接受c++信号
        target: mySerial
        function onConnectflageChanged(connect_state) {
            if (connect_state)
            {
                modelShow.statedef = 1;
                mySerial.read_key_data();
                if (page_id === 1){
                    modelShow.statedef = 2;
                }
            }else{
                modelShow.statedef = 0;
                bottomFunc.keylist = [];
                console.log("清空",bottomFunc.keylist);
            }
            connectstate = connect_state;
            connectIndications.connectInd = connect_state;
            bottomFunc.connect_state1 = connect_state;     // 传给第二页面
        }

        function onKeydataChanged(keydata) {
            let hexStr = keydata; // 接收的十六进制字符串 "040006010600"
            let result = [];

            // 步骤1：每2字符分割为字节（如 "04", "00", "06", ...）
            for (let i = 0; i < hexStr.length; i += 2) {
                let byteStr = hexStr.substr(i, 2);
                // console.log("line 20",byteStr);
                let byteValue = parseInt(byteStr, 16); // 转为十进制（如 "04" → 4）
                // console.log("line 22",byteValue);
                // 步骤3：右移1位（根据协议映射）
                result.push(byteValue); // 0x0 → 0
            }
            bottomFunc.keylist = result; // 填入数据
            console.log("触发"); // 输出 [0,2,0,2,0,2]
            console.log("转换结果:", result); // 输出 [0,2,0,2,0,2]
        }
    }

    Connections { // 连接按钮信号
        target: leftToggle
        function onButidChanged(but_id)
        {
            page_id = but_id;
            switch (but_id){
            case 0: // 主页
                bottomFunc.pagenum = 0;
                set_region.visible = false;
                if (connectstate)
                {
                    modelShow.statedef = 1;
                    mySerial.read_key_data();
                }
                break;
            case 1: // 设置
                bottomFunc.pagenum = 1;
                set_region.visible = false;
                if (connectstate)
                {
                    modelShow.statedef = 2;
                }
                break;
            case 2:
                set_region.visible = true;
                // set_region.z = 99;
                break;
            }
        }
    }
    // [0] END

    // [1] 左侧切换栏
    LeftToggle {
        id: leftToggle
        anchors.left: parent.left
        width: 58; height: parent.height
    }
    // [1] END

    ColumnLayout {
        id: function_region
        width: parent.width-leftToggle.width;height: parent.height
        anchors.left: leftToggle.right
        // [2] 模型展示区域
        ModelShow {
            id: modelShow
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height*0.7
            ConnectIndications {
                id: connectIndications
                width: 100;height: 50;
                anchors {
                    top: parent.top
                    topMargin: 10
                    right: parent.right
                    rightMargin: 10
                }
                connectInd:false
            }
        }
        // [2] END

        // [3] 底部功能栏
        BottomFunc {
            id: bottomFunc
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height*0.3
            pagenum: 0  // 页面
            onNeeddataTop:(keylist)=> // 顶层数据
                          {
                            mySerial.input_data(keylist);
                          }
        }
        // [3] END
    }

    // [] 设置区域
    SetPage {
        id: set_region
        width: function_region.width;height: function_region.height
        anchors {
            left: function_region.left
            top: parent.top
        }
        visible: false

    }
    // [] END
}

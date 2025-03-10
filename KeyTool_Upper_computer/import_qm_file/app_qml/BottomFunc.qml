import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "BottomFunc_page"

Rectangle {
    property int pagenum: 0   // 页面索引
    property bool connect_state1: false
    property var datalist: [] // 定义列表
    property var keylist: []  // 接收顶层数据
    signal needdataTop(var keydata)        // 传递到顶层的信号
    border{
        color: "#541e24";
        width: 3
    }

    onKeylistChanged: {
        page0.bfpage1list = keylist;
    }

    onConnect_state1Changed: {
        page1.connect_state0 = connect_state1
        console.log("接收信号",connect_state1);
    }
    StackLayout {
        id: stackLayout
        anchors.fill: parent
        currentIndex: pagenum           // 索引
        onCurrentIndexChanged: {        // 索引变化信号
            // console.log(`页面${pagenum}`);  // 模板字符串
        }
        // 01 主页
        BFpage1{
            id: page0
            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitWidth: 200      // 默认宽度
            implicitHeight: 200     // 默认高度
        }
        // 01 END

        // 02 页面1
        BFpage2{
            id: page1
            Layout.fillWidth: true
            Layout.fillHeight: true
            implicitWidth: 200      // 默认宽度
            implicitHeight: 200     // 默认高度
            onNeeddatasix: (keylist) => {
                               datalist = keylist;
                           }
            onSendtocpp:{
                needdataTop(datalist);
            }
        }
        // 02 END
    }
}

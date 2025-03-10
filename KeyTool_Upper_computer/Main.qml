import QtQuick
import QtQuick.Controls
import GameTool

import "import_qm_file/window_qml"
import "import_qm_file/app_qml"

/* 程序分为三个整体
  [1] 启动画面 startShow
  [2] 主窗口   rootWin
  [3] 应用界面 AppInterface
  */
QtObject {
    // [2] 主窗口
    property var rootWin: CustomizeTitle {  // 顶级窗口
        id: win
        width: 1024;height: 720
        visible: true
        minimumWidth: 1024*0.8; minimumHeight: 720*0.8

        /*{0}函数以及变量*/
        //程序启动在居中显示函数
        function screenCenter(mag)
        {
            win.width = win.width*mag
            win.height = win.height*mag
            var screen = Qt.application.screens[0]; // 获取主屏幕
            var screenWidth = screen.width;
            var screenHeight = screen.height;

            // 计算窗口居中的 x 和 y 坐标
            var x = (screenWidth - win.width) / 2;
            var y = (screenHeight - win.height) / 2;

            // 设置窗口的位置
            win.x = x;
            win.y = y;
        }
        Component.onCompleted: {
            screenCenter(1);
        }
        /*{0}END*/

        /*{1}标题栏*/
        TitleBar {
            id: titlebar
            width: win.width; height: 33
            anchors.top: win.top
        }
        /*{1}END*/
        onWindowStateChanged: {    // 窗口状态变化
            // 直接在 win 上调用
        }
        onWidthChanged: {     // 窗口宽度变化
            // 直接在 win 上调用
        }
        onHeightChanged: {     // 窗口高度变化
            // 直接在 win 上调用
        }
        // [2]END

        // [3] 应用界面
        AppInterface {
            id: appInterface
            width: win.width;height: win.height-titlebar.height
            anchors.top: titlebar.bottom
        }
        // [3] END
    }
}

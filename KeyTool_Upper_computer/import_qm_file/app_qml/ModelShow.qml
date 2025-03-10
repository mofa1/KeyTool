 import QtQuick
import QtQuick.Controls
import QtQuick3D
import QtQuick3D.Helpers

import "../../resource/GameToll"
import QtQml.StateMachine as DSM
Item {
    /*定义变量*/
    property int statedef: 0
    /*END*/

    /*
    [0]模型动作状态机
    1.未连接状态 STATE_NONE
    2.连接状态  STATE_CONNECT
    3.设置状态  STATE_SET
    */
    DSM.StateMachine {
        id: stateMachine
        initialState:  state_none// 初始状态
        running: true

        DSM.State {
            id: state_none         // 设备未连接状态
            DSM.SignalTransition {
                targetState: state_connect
                signal: onStatedefChanged
                guard: statedef === 1;
            }
            onEntered:
            {
                // console.log("进入0");
                animation_scale.running = false;
                animation_euler.running = false;
                view3D.scale = 0.8;
                gameToll.eulerRotation.x = 0;
                gameToll.eulerRotation.y = 0;
            }
            onExited:
            {
                animation_scale.running = false;
                animation_euler.running = false;
                // console.log("离开0");
            }
        }

        DSM.State {             // 设备连接后状态
            id: state_connect
            DSM.SignalTransition {
                targetState: state_none
                signal: onStatedefChanged
                guard: statedef === 0;
            }
            DSM.SignalTransition {
                targetState: state_set
                signal: onStatedefChanged
                guard: statedef === 2;
            }
            onEntered:
            {
                animation1.to = 1;
                animation3.to = -10;
                animation4.to = -10;
                animation_scale.running = true;
                animation_euler.running = true;
                // console.log("进入1");
            }
            onExited:
            {
                animation_scale.running = false;
                animation_euler.running = false;
                // console.log("离开1");
            }
        }

        DSM.State {
            id: state_set        // 设备设置状态
            DSM.SignalTransition {
                targetState: state_none
                signal: onStatedefChanged
                guard: statedef === 0;
            }
            DSM.SignalTransition {
                targetState: state_connect
                signal: onStatedefChanged
                guard: statedef === 1;
            }
            onEntered:
            {
                animation1.to = 1.5;
                animation3.to = 0;
                animation4.to = -60;
                animation_scale.running = true;
                animation_euler.running = true;

                testanima.running = true;
                // console.log("进入2");
            }
            onExited:
            {
                animation_scale.running = false;
                animation_euler.running = false;
                testanima.running = false;
            }
        }
    }
    /*[0] END*/

    /*
    [1]基本动画
    */
    /*顺序运行动画 缩放*/
    SequentialAnimation {
        id: animation_scale
        running: false
        PropertyAnimation {
            id :animation1
            target: view3D
            property: "scale"
            to: 1
            duration: 800
            easing.type: Easing.InOutQuad
        }
    }

    /*同时运行动画 欧拉角*/
    ParallelAnimation {
        id: animation_euler
        running: false
        PropertyAnimation {
            id :animation3
            target: gameToll
            property: "eulerRotation.y"
            to: -10
            duration: 1000
            easing.type: Easing.InOutQuad
        }
        PropertyAnimation {
            id :animation4
            target: gameToll
            property: "eulerRotation.x"
            to: -10
            duration: 1000
            easing.type: Easing.InOutQuad
        }
    }

    // 键帽按下动画
    SequentialAnimation {
        id: testanima
        running: false
        loops: Animation.Infinite
        NumberAnimation {
            id: testanima_1
            property: "z"
            duration: 200;
            to: 20;
            easing.type: Easing.InQuad

        }
        NumberAnimation {
            id: testanima_2
            property: "z"
            duration: 200;
            to: 10;
            easing.type: Easing.InQuad
        }
    }
    /*[1] END*/

    /*
    [2]模型组合
    1.设备模型
    2.键帽模型
    */
    Rectangle{
        id: modelshow
        // border{color: "red";width:3}
        anchors.fill: parent
        View3D {
            id: view3D
            visible: true
            anchors.fill: parent
            z: 100
            scale: 0.8
            rotation: 0
            environment: sceneEnvironment
            SceneEnvironment {
                id: sceneEnvironment
                antialiasingQuality: SceneEnvironment.VeryHigh
                antialiasingMode: SceneEnvironment.SSAA
            }

            Node {
                id: scene
                DirectionalLight {
                    id: directionalLight
                    visible: true
                }

                PerspectiveCamera {
                    id: sceneCamera
                    z: 100
                }

                GameToll {
                    id: gameToll
                    position: Qt.vector3d(0,0,0)
                    eulerRotation.x: 0
                    z: 0
                    pivot: Qt.vector3d(40, -35, 0)
                    Keym {
                        id: keym1
                        parent: gameToll // 声明父子关系
                        position: Qt.vector3d(18, -54, 7) // 相对位置
                        eulerRotation.x: 90
                        scale.z: 9
                        scale.y: 9
                        scale.x: 9
                    }
                    Keym {
                        id: keym2
                        parent: gameToll // 声明父子关系
                        position: Qt.vector3d(40, -54, 7) // 相对位置
                        eulerRotation.x: 90
                        scale.z: 9
                        scale.y: 9
                        scale.x: 9
                    }
                    Keym {
                        id: keym3
                        parent: gameToll // 声明父子关系
                        position: Qt.vector3d(62, -54, 7) // 相对位置
                        eulerRotation.x: 90
                        scale.z: 9
                        scale.y: 9
                        scale.x: 9
                    }
                }
                // AxisHelper {}
            }
        }
    }
    /*[2] END*/
}


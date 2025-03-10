#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <QObject>
#include <QQmlEngine>
#include <QSerialPort>
#include <QTimer>
#include <QEventLoop>
#include <QStringList>
#include <QVariant>
#include <QByteArray>
#include <QMap>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QDebug>

#include "winmsg.h"

class MySerial : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool connectflage READ connectflage WRITE setConnectflage NOTIFY connectflageChanged FINAL)
    QML_ELEMENT

public:
    explicit MySerial();
    ~MySerial();
    bool connectflage() const; // 返回连接状态
    void setConnectflage(bool newConnectflage);   // 接收qml数据
    Q_INVOKABLE void input_data(const QVariantList &inputdata);
    Q_INVOKABLE void read_key_data();
signals:
    void connectflageChanged(bool connect_state);
    void keydataChanged(QString hexStr);
private slots:  // 槽函数
    void readData();  // 串口接收到数据
    void get_error(QSerialPort::SerialPortError error); // 接收到串口设备错误
    void task_send_finished();  // 线程执行完毕信号

private:
    // 使用智能指针实例化类
    std::unique_ptr<QSerialPort> m_serial;
    std::unique_ptr<MyMSGEventFilter> m_eventFilter;
    QFutureWatcher<void> m_watcher; // [3](@ref)
    QFutureWatcher<void> m_watcher2; // [3](@ref)
    void open_serial(QString serial_name);      // 打开串口
    void close_serial();                        // 关闭串口
    void check_device();                        // 检查设备
    void write_data(const QByteArray &data);    // 发送数据
    void found_keyvalue(int value,int index);   // 查找key的映射
    void found_hidvalue(int value,int index);   // 查找hid的映射

    // 定义变量
    QByteArray check_data;      // 检查设备存在的数据
    QByteArray handle_data;     // 接收到的数据头
    QByteArray handle_hid_data; // 接收到HID的数据头
    QByteArray read_data;       // 接收到的数据
    QByteArray qml_data;        // 从qml传送到c++经过键值查找后的数据
    QMutex qml_data_mutex;      // 线程锁
    QByteArray data_qml;        // 从c++传送到qml经过键值查找后的数据
    QString hex_str;
    QMutex data_qml_mutex;      // 线程锁
    int check_num;              // 校验位数量
    bool m_connectflage;
};

#endif // MYSERIAL_H

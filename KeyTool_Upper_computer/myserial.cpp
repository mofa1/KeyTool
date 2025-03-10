#include "myserial.h"
#include "keymapping.h"
#include <QGuiApplication>
#include <QSerialPortInfo>

MySerial::MySerial()
    :m_serial(std::make_unique<QSerialPort>())
    ,m_eventFilter(std::make_unique<MyMSGEventFilter>())
{
    /*绑定信号和槽*/
    qApp->installNativeEventFilter(m_eventFilter.get());
    connect(m_eventFilter.get(),&MyMSGEventFilter::add_sub_serial,this,&MySerial::check_device);    // 检测串口变化
    connect(m_serial.get(),&QSerialPort::readyRead,this,&MySerial::readData/*,Qt::DirectConnection*/); // 绑定收到消息信号
    connect(m_serial.get(),&QSerialPort::errorOccurred,this,&MySerial::get_error); // 绑定收到消息信号
    /*END*/
    check_data = QByteArray::fromHex("2626"); // 设备需要返回的认证消息
    //check_data = QByteArray::fromHex("0827"); // 设备需要返回的认证消息
    handle_data = QByteArray::fromHex("2525");
    handle_hid_data = QByteArray::fromHex("3333");
    check_num = 2;                            // 校验位长度
    // 使用 QTimer 延迟执行
    QTimer::singleShot(50, this, [this]() {
        check_device();
    });
}

// 析构函数
MySerial::~MySerial()
{
    m_watcher.cancel();
    m_watcher.waitForFinished();
    close_serial();
}

void MySerial::open_serial(QString serial_name)
{
    m_serial->setPortName(serial_name);                        // 串口名称
    m_serial->setBaudRate(QSerialPort::Baud115200);         // 波特率
    m_serial->setDataBits(QSerialPort::Data8);              // 数据位
    m_serial->setParity(QSerialPort::NoParity);             // 校验位
    m_serial->setStopBits(QSerialPort::OneStop);            // 停止位
    m_serial->setFlowControl(QSerialPort::NoFlowControl);   // 流控制
    if(m_serial->open(QIODevice::ReadWrite))                // 打开串口,读取与写入模式
    {
        qDebug() << "串口已打开";
    }else{
        qDebug() << "串口打开失败";
    }
}

void MySerial::close_serial()
{
    if (m_serial->isOpen()) m_serial->close();  // 打开串口的情况下才可以关闭串口
    qDebug() << "关闭串口";
}

void MySerial::check_device()
{
    QByteArray data;
    data.append(0x08);
    data.append(0x27);
    /*轮询串口*/
    const auto infos = QSerialPortInfo::availablePorts();  // 获取当前串口
    for(const QSerialPortInfo &info : infos){
        open_serial(info.portName());   // 打开串口
        QEventLoop loop;                // 使用QEventLoop等待readData完成
        QTimer::singleShot(100, &loop, &QEventLoop::quit);            // 这里可以设置一个超时时间，防止无限等待
        write_data(data);               // 发送数据
        // 在 write_data(data) 后添加信号连接
        connect(m_serial.get(), &QSerialPort::readyRead, &loop, &QEventLoop::quit, Qt::QueuedConnection);
        // 等待收到认证消息跳出事件循环 超时100ms
        loop.exec();// 进入局部事件循环，直到readData中设置xx为true或超时
        if (read_data.toHex() == check_data.toHex()){
            m_connectflage = true;      // 连接了
            emit connectflageChanged(m_connectflage);
            break;
        }
        else{
            close_serial();
        }
    }
}

void MySerial::write_data(const QByteArray &data)
{
    m_serial->write(data);
    qDebug() << "发送数据";
}

bool MySerial::connectflage() const
{
    return m_connectflage;
}

void MySerial::setConnectflage(bool newConnectflage)
{
    // if (m_connectflage == newConnectflage)
    //     return;
    // m_connectflage = newConnectflage;
    // emit connectflageChanged();
}

/*[qml->c++] 将数据写入hid设备*/
void MySerial::found_keyvalue(int value,int index)
{
    // 判断是否在映射中
    if (KEY_HID_MAP.contains(value))
    {
        QMutexLocker locker(&qml_data_mutex); // 加锁
        if (index >= qml_data.size()-check_num)
        {
            qml_data.resize(index+1+check_num); // 确保足够大
        }
        qml_data[index+check_num] = KEY_HID_MAP[value];
    }else{
        qDebug() << "not found value";
    }
}
void MySerial::input_data(const QVariantList &inputdata)
{
    qml_data.clear();       // 使用前清空
    qml_data.append(0x25);  // 开始的校验位
    qml_data.append(0x25);
    // 1.加入1 3 5的数据
    for (int index_const:{1,3,5}){
        if (index_const < inputdata.size()){
            int value_const = inputdata[index_const].toInt();
            if (index_const >= qml_data.size()-check_num)
            {
                qml_data.resize(index_const+1+check_num); // 确保足够大
                qml_data[index_const+check_num] = static_cast<char>(value_const);
            }
        }
    }
    // 2.用0,2,4数据查找键值对
    QList<QFuture<void>> futures;
    for (int index:{0,2,4}){
        if (index < inputdata.size()){
            int value = inputdata[index].toInt();
            futures.append(QtConcurrent::run([this,value,index]() {
                this->found_keyvalue(value,index);
            }));
        }
    }
    // 创建组合监控任务
    QFuture<void> monitorFuture = QtConcurrent::run([futures]() mutable { // 关键修改：添加mutable
        for (auto& future : futures) {
            future.waitForFinished();
        }
    });
    // 连接信号到监控任务
    disconnect(&m_watcher, 0, 0, 0); // 先断开原有连接
    connect(&m_watcher, &QFutureWatcher<void>::finished, // 正确信号语法
            this, &MySerial::task_send_finished);
    m_watcher.setFuture(monitorFuture);
}
void MySerial::task_send_finished()
{
    qml_data.append(0x06);  // 添加在末尾的未触发位
    qDebug() << "line 186" << qml_data.toInt();
    write_data(qml_data);
}
/*[qml->c++] END*/

/*[c++->QML] 从HID读取数据到qml*/
void MySerial::read_key_data()
{
    data_qml.clear();  // 使用前清空
    QEventLoop loop;                // 使用QEventLoop等待readData完成
    QTimer::singleShot(100, &loop, &QEventLoop::quit);            // 这里可以设置一个超时时间，防止无限等待
    write_data(handle_hid_data);               // 发送数据
    connect(m_serial.get(), &QSerialPort::readyRead, &loop, &QEventLoop::quit, Qt::QueuedConnection);
    // read_data = QByteArray::fromHex("333304000601280009"); // 测试数据
    loop.exec();// 进入局部事件循环，直到readData中设置xx为true或超时
    if (read_data.size() < 2) {
        return;
    }
    QByteArray firstTwoBytes = read_data.mid(0, 2);
    if (firstTwoBytes == handle_hid_data){
        data_qml = read_data.mid(2, read_data.size() - 3);
        hex_str = QString::fromUtf8(data_qml.toHex());
        emit keydataChanged(hex_str);
    }
}
/*[c++->QML] END*/

void MySerial::readData()
{
    read_data = m_serial->readAll();
    qDebug() << "收到的消息为:" << read_data.toStdString();
}

void MySerial::get_error(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::PermissionError) {
        qDebug() << "设备在打开串口后拔出";
        m_connectflage = false; // 断开连接了
        emit connectflageChanged(m_connectflage);
        close_serial();      // 关闭串口
    }
}



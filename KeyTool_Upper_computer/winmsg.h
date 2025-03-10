#ifndef WINMSG_H
#define WINMSG_H

#include <QObject>
#include <QQmlEngine>
#include <QAbstractNativeEventFilter>
#include <windows.h>
#include <dbt.h>

class MyMSGEventFilter : public QObject,public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *) override
    {
        if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG") {
            MSG *msg = static_cast<MSG *>(message);
            if (msg->message == WM_DEVICECHANGE){
                switch (msg->wParam) {
                case DBT_DEVICEARRIVAL:
                    qDebug() << "插入串口";
                    emit add_sub_serial();
                    break;
                case DBT_DEVICEREMOVECOMPLETE:
                    qDebug() << "拔出串口";
                    emit add_sub_serial();
                    break;
                default:
                    break;
                }
            }
        }
        return false;
    }
signals:
    void add_sub_serial();
};

#endif // WINMSG_H


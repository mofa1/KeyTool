#ifndef CUSTOMIZETITLE_H
#define CUSTOMIZETITLE_H

#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWindow>

/*继承自QQuickWindow*/
class CustomizeTitle : public QQuickWindow
{
    Q_OBJECT
    QML_ELEMENT
public:
    CustomizeTitle(QWindow *parent = nullptr);
    ~CustomizeTitle() override = default;

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;

private:
    void setWindowStyle();
    int adjustResizeWindow(HWND hwnd,const QPoint& mouse_pos);
    void adjustWindowContentMarginsWhenMaximized(bool is_maxmized);
    bool event(QEvent *event) override;
};

#endif // CUSTOMIZETITLE_H

#include "customizetitle.h"

#include <QQuickWindow>
#include <dwmapi.h>
#include <windows.h>
#include <windowsx.h>

#define RESIZE_EDGE_THRESHOLD 5

CustomizeTitle::CustomizeTitle(QWindow *parent)
    :QQuickWindow(parent)
{
    this->setFlags(flags()
                   | Qt::WindowType :: Window
                   | Qt::WindowType :: FramelessWindowHint);
    this->setWindowStyle();
}

bool CustomizeTitle::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    MSG *msg = reinterpret_cast<MSG*>(message);
    switch (msg->message) {
    case WM_NCCALCSIZE:
    {
        *result = 0;
        return true;
    }
    case WM_NCHITTEST:
    {
        QPoint mouse_pos(GET_X_LPARAM(msg->lParam),GET_Y_LPARAM(msg->lParam));
        *result = adjustResizeWindow(msg->hwnd,mouse_pos);
        if (*result != 0) {
            return true;
        }    return false;
    }

    default:
        return QWindow::nativeEvent(eventType,message,result);
    }
    return QWindow::nativeEvent(eventType,message,result);
}

void CustomizeTitle::setWindowStyle()
{
    // 强制转换
    auto hwnd = reinterpret_cast<HWND>(this->winId());  // QT提供,获取窗口句柄
    DWORD style = GetWindowLong(hwnd,GWL_STYLE);
    SetWindowLong(hwnd,GWL_STYLE,style |WS_THICKFRAME|WS_CAPTION|WS_MAXIMIZEBOX|WS_MINIMIZEBOX);
    const MARGINS shadow = {1,1,1,1};
    ::DwmExtendFrameIntoClientArea(hwnd,&shadow);
}

int CustomizeTitle::adjustResizeWindow(HWND hwnd, const QPoint &mouse_pos)
{
    int result =0;
    RECT window_rect = {0,0,0,0};
    ::GetWindowRect(hwnd,&window_rect);

    bool allow_resize_width = this->minimumWidth() != this->maximumWidth();
    bool allow_resize_height = this->minimumHeight() != this->maximumHeight();

    int mouse_x = mouse_pos.x();
    int mouse_y = mouse_pos.y();
    if (allow_resize_width)
    {
        if (mouse_x >= window_rect.left && mouse_x < window_rect.left + RESIZE_EDGE_THRESHOLD) {
            result = HTLEFT;
        }
        else if(mouse_x <= window_rect.right && mouse_x>window_rect.right-RESIZE_EDGE_THRESHOLD)
        {
            result = HTRIGHT;
        }
    }
    if (allow_resize_height) {
        if (mouse_y >= window_rect.top && mouse_y < window_rect.top + RESIZE_EDGE_THRESHOLD) {
            result = HTTOP;
        }
        else if(mouse_y <= window_rect.bottom && mouse_y>window_rect.bottom-RESIZE_EDGE_THRESHOLD)
        {
            result = HTBOTTOM;
        }
    }
    if (allow_resize_width && allow_resize_height)
    {
        if (mouse_x >= window_rect.left && mouse_x < window_rect.left + RESIZE_EDGE_THRESHOLD &&
            mouse_y >= window_rect.top && mouse_y < window_rect.top + RESIZE_EDGE_THRESHOLD) {
            result = HTTOPLEFT;
        }
        if (mouse_x <= window_rect.right && mouse_x>window_rect.right-RESIZE_EDGE_THRESHOLD &&
            mouse_y >= window_rect.top && mouse_y < window_rect.top + RESIZE_EDGE_THRESHOLD){
            result = HTTOPRIGHT;
        }
        if (mouse_x >= window_rect.left && mouse_x < window_rect.left + RESIZE_EDGE_THRESHOLD &&
            mouse_y <= window_rect.bottom && mouse_y>window_rect.bottom-RESIZE_EDGE_THRESHOLD) {
            result = HTBOTTOMLEFT;
        }
        if (mouse_x <= window_rect.right && mouse_x>window_rect.right-RESIZE_EDGE_THRESHOLD &&
            mouse_y <= window_rect.bottom && mouse_y>window_rect.bottom-RESIZE_EDGE_THRESHOLD){
            result = HTBOTTOMRIGHT;
        }

    }
    return result;
}

void CustomizeTitle::adjustWindowContentMarginsWhenMaximized(bool is_maxmized)
{
    auto content_item = this->contentItem();
    auto content_layout = content_item->childItems().first();
    if (is_maxmized) {
        // 获取超出的大小
        RECT frame= {0,0,0,0};
        ::AdjustWindowRectEx(&frame,WS_OVERLAPPEDWINDOW,FALSE,0);
        frame.left = std::abs(frame.left);
        frame.top = std::abs(frame.bottom);
        double pixel_ratio = this->devicePixelRatio();

        QMetaObject::invokeMethod(content_layout,"adjustWindowContentMarginsWhenMaximized",
                                  Q_ARG(QVariant, static_cast<int>(frame.left / pixel_ratio)),
                                  Q_ARG(QVariant, static_cast<int>(frame.right / pixel_ratio)),
                                  Q_ARG(QVariant, static_cast<int>(frame.top / pixel_ratio)),
                                  Q_ARG(QVariant, static_cast<int>(frame.bottom / pixel_ratio)));
    }
    else {

        QMetaObject::invokeMethod(content_layout,"adjustWindowContentMarginsWhenMaximized",
                                  Q_ARG(QVariant, 0),
                                  Q_ARG(QVariant, 0),
                                  Q_ARG(QVariant, 0),
                                  Q_ARG(QVariant, 0));
    }
}

bool CustomizeTitle::event(QEvent *event)
{
    if (event->type() == QEvent::Type::WindowStateChange) {
        auto windows_state_changed_event = dynamic_cast<QWindowStateChangeEvent*>(event);
        if (this->windowStates() & Qt::WindowState::WindowMaximized)
        {
            this->adjustWindowContentMarginsWhenMaximized(true);
        }
        else
        {
            this->adjustWindowContentMarginsWhenMaximized(false);
        }
    }
    return QQuickWindow::event(event);
}



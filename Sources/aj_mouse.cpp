#include "aj_mouse.h"
#include <QDebug>
#include <QThread>

void aj_mouseClick(POINT obj_center, AjAccCmd cmd)
{
    POINT cursor_last;
    GetCursorPos(&cursor_last);
//    RECT rect;
//    GetWindowRect(hwnd, &rect);
//    offset_x -= rect.left;
//    offset_y -= rect.top;
    SetCursorPos(obj_center.x + cmd.offset_x, obj_center.y + cmd.offset_y);
//    aj_setMouse(obj_center.x + offset_x, obj_center.y + offset_y);

    QThread::msleep(AJ_MOUSE_DELAY);

    if( cmd.action==AJ_CMD_LMB )
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
    else if( cmd.action==AJ_CMD_RMB )
    {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    }
    else if( cmd.action==AJ_CMD_MMB )
    {
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
    }
    else if( cmd.action==AJ_CMD_DCLICK )
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        QThread::msleep(AJ_DOUBLE_DELAY);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
    else
    {
        qDebug() << "click type problem! fuck this shit, code shouldn't reach here";
        return;
    }

    QThread::msleep(AJ_MOUSE_DELAY);

//    SetCursorPos(cursor_last.x, cursor_last.y);  //any value other than main window
}

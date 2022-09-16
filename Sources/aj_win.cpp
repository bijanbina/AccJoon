#include "aj_win.h"
#include "aj_keyboard.h"

AjWin::AjWin(HWND hWindow)
{
    hwnd = hWindow;
    window_title = "";
}

void AjWin::listChildren(IAccessible *pAcc, QString path)
{
    QString pAcc_name = aj_getAccName(pAcc, CHILDID_SELF);
    qDebug() << "####### getChildren - acc path : " + pAcc_name;

    long childCount;
    long returnCount;
    HRESULT hr = pAcc->get_accChildCount(&childCount);
    VARIANT* pArray = new VARIANT[childCount];
    hr = AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);
    path += QString(".");

    for (int x = 0; x < returnCount; x++)
    {
        VARIANT vtChild = pArray[x];
        if (vtChild.vt == VT_DISPATCH)
        {
            IDispatch* pDisp = vtChild.pdispVal;
            IAccessible* pChild = NULL;
            hr = pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
            if (hr == S_OK)
            {
                QString child_name = aj_getAccName(pChild, CHILDID_SELF);
                long child_count = aj_getChildCount(pChild);
                qDebug() << "-> acc path : " + pAcc_name +
                            " - child[" + QString::number(x) + "/" + QString::number(returnCount-1) + "], childname:" + child_name +
                            "| child count " + QString::number(child_count) + " path:" + path + QString::number(x+1);
                if(child_count>0)
                {
                    listChildren(pChild, path + QString::number(x+1));
                }
                pChild->Release();
            }
            pDisp->Release();
        }
        // Else it's a child element so we have to call accNavigate on the parent,
        //   and we do not recurse because child elements can't have children.
        else
        {
            qDebug() <<"-> acc path : " + pAcc_name +
                        " - child[" + QString::number(x) + "/" + QString::number(returnCount-1) +
                        "] ELEMENT - " + aj_getAccName(pAcc, vtChild.lVal)
                        + " path:" + path + QString::number(x+1);
        }
    }
    delete[] pArray;
    qDebug() <<"####### Exit getChildren - acc path : " + pAcc_name;
}

IAccessible *AjWin::getHwndAcc(HWND hWindow)
{
    char buffer[256];
    IAccessible *acc;

    if( hWindow==NULL )
    {
        hWindow = GetForegroundWindow();
        if( hWindow==NULL )
        {
            qDebug() << "Error: cannot get foreground window handler";
            return NULL;
        }
    }

    GetWindowTextA(hWindow, buffer, 256);
    window_title = QString(buffer);

    acc = aj_getWinPAcc(hWindow);
    return acc;
}

int AjWin::doAction(AjCommand cmd)
{
    if( cmd.key.isEmpty() )
    {
        return doAcc(cmd);
    }
    else if( cmd.action.isEmpty() )
    {
        return doKey(cmd);
    }
    else
    {
        return -1;
    }
}

int AjWin::doKey(AjCommand cmd)
{
    AjKeyboard *keyboard = new AjKeyboard();
    printf("doKey: ");

    if( cmd.alt_key )
    {
        keyboard->pressKey(KEY_LEFTALT);
        qDebug("Alt+");
    }
    if( cmd.ctrl_key )
    {
        QThread::msleep(20);
        keyboard->pressKey(KEY_LEFTCTRL);
        qDebug("Ctrl+");
    }
    if( cmd.shift_key )
    {
        QThread::msleep(20);
        keyboard->pressKey(KEY_LEFTSHIFT);
        qDebug("Shift+");
    }
    if( cmd.meta_key )
    {
        QThread::msleep(20);
        keyboard->pressKey(KEY_META);
        qDebug("Super+");
    }
    cmd.key = cmd.key.toUpper();
    int key = cmd.key.toStdString().c_str()[0];
    QThread::msleep(1000);
    keyboard->sendKey(key);
    qDebug() << cmd.key << key;
    if( cmd.alt_key )
    {
        QThread::msleep(20);
        keyboard->releaseKey(KEY_LEFTALT);
    }
    if( cmd.ctrl_key )
    {
        QThread::msleep(20);
        keyboard->releaseKey(KEY_LEFTCTRL);
    }
    if( cmd.shift_key )
    {
        QThread::msleep(20);
        keyboard->releaseKey(KEY_LEFTSHIFT);
    }
    if( cmd.meta_key )
    {
        QThread::msleep(20);
        keyboard->releaseKey(KEY_META);
    }

    return 0;
}

int AjWin::doAcc(AjCommand cmd)
{
    IAccessible *win_pAcc, *acc;

    path = cmd.acc_path.split('.');
    acc_name = cmd.acc_name;

    offset_x = cmd.offset_x;
    offset_y = cmd.offset_y;
    offset_id = cmd.offset_id;

    int cmd_type = aj_clickType(cmd.action);
    if( cmd_type==-1 )
    {
        qDebug() << "Error: click" << cmd.action << "is not acceptable";
        return -1;
    }

    win_pAcc = getHwndAcc(hwnd);
    if( win_pAcc==NULL )
    {
        qDebug() << "Error: cannot get acc of active window (" << window_title << ")";
        return -1;
    }
//    listChildren(win_pAcc, QString(""));

    //get parent path
    int child_id;
    if( acc_name.isEmpty() )
    {
        child_id = path.last().toInt()-1;
        path.removeLast();
        qDebug() << "child id is" << child_id;
    }

    acc = aj_getAcc(path, win_pAcc);
    if( acc==NULL )
    {
        qDebug() << "Error: cannot get parent acc in window (" << window_title << ")";
        return -1;
    }

    if( acc_name.length() )
    {
        child_id = aj_getChildId(acc_name, acc) + offset_id;
        if( child_id==-1 )
        {
            qDebug() << "Failed to get child id";
            return -1;
        }

        if( cmd_type==AJ_CMD_CHILDID )
        {
            qDebug() << child_id;
            return 0;
        }
    }

    obj_center = getAccLocation(acc,child_id);
    if( obj_center.x==0 && obj_center.y==0 )
    {
        qDebug() << "Error: cannot get location in window (" << window_title << ")";
        return -1;
    }

    doClick(cmd_type);

    return 0;
}

void AjWin::doClick(int cmd)
{
    GetCursorPos(&cursor_last);

    SetCursorPos(obj_center.x + offset_x, obj_center.y + offset_y);

    QThread::msleep(AJ_MOUSE_DELAY);

    if( cmd==AJ_CMD_LMB )
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
    else if( cmd==AJ_CMD_RMB )
    {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    }
    else if( cmd==AJ_CMD_MMB )
    {
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
    }
    else if( cmd==AJ_CMD_DCLICK )
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

    SetCursorPos(cursor_last.x, cursor_last.y);  //any value other than main window
}

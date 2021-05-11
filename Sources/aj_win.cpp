#include "aj_win.h"

AjWin::AjWin(QString acc_path, QString accName, int o_x, int o_y, int o_id)
{
    window_title = "";
    path = acc_path.split('.');
    acc_name = accName;

    offset_x = o_x;
    offset_y = o_y;
    offset_id = o_id;
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

IAccessible *AjWin::getActiveAcc()
{
    char buffer[256];
    IAccessible *acc;
    HWND active_window;

    active_window = GetForegroundWindow();
    if( active_window==NULL )
    {
        qDebug() << "Error: cannot get foreground window handler";
        return NULL;
    }

    GetWindowTextA(active_window, buffer, 256);
    window_title = QString(buffer);

    acc = aj_getWinPAcc(active_window);
    return acc;
}

int AjWin::doAction(QString cmd)
{
    IAccessible *win_pAcc, *acc;

    int cmd_type = aj_clickType(cmd);
    if( cmd_type==-1 )
    {
        qDebug() << "Error: click" << cmd << "is not acceptable";
        return -1;
    }

    win_pAcc = getActiveAcc();
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

    Sleep(AJ_MOUSE_DELAY);

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
        Sleep(AJ_DOUBLE_DELAY);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
    else
    {
        qDebug() << "click type problem! fuck this shit, code shouldn't reach here";
        return;
    }

    Sleep(AJ_MOUSE_DELAY);

    SetCursorPos(cursor_last.x, cursor_last.y);  //any value other than main window
}

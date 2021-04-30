#include "aj_win.h"

AjWin::AjWin(QString acc_path, QString cmd, QString accName, int o_x, int o_y, int o_id)
{
    active_window = NULL;
    active_win_pAcc = NULL;
    window_title = "";
    path = acc_path.split('.');
    cmd_type = aj_clickType(cmd);
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
                            "| child count " + QString::number(child_count) + " path:" + path + QString::number(x);
                if(child_count>0)
                {
                    listChildren(pChild, path + QString::number(x));
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
                        + " path:" + path + QString::number(x);
        }
    }
    delete[] pArray;
    qDebug() <<"####### Exit getChildren - acc path : " + pAcc_name;
}

int AjWin::setWinSpec()
{
    char buffer[256];

    active_window = GetForegroundWindow();
    if( active_window==NULL )
    {
        qDebug() << "Error: cannot get foreground window handler";
        return -1;
    }

    GetWindowTextA(active_window, buffer, 256);
    window_title = QString(buffer);

    active_win_pAcc = aj_getWinPAcc(active_window);
    if( active_win_pAcc==NULL )
    {
        qDebug() << "Error: cannot get pAcc from active window (" << window_title << ")";
        return -1;
    }

//    qDebug() << "Info: Processing window:" << window_title << ", object path:" << path
//             << ", with click:" << aj_click_name(cmd_type);
    return 0;
}

int AjWin::setObjSpec()
{
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = CHILDID_SELF;

    long obj_x = 0, obj_y = 0, obj_w = 0, obj_h = 0;

//    listChildren(active_win_pAcc, QString(""));

    IAccessible *object_acc = aj_getAcc(path, active_win_pAcc);
    if( object_acc==NULL )
    {
        qDebug() << "Error: cannot get object in window (" << window_title << ")";
        return -1;
    }

    object_acc->accLocation(&obj_x, &obj_y, &obj_w, &obj_h, varChild);
    if( obj_x==0 || obj_y==0 || obj_h<0 || obj_w<0 )
    {
        qDebug() << "Error: cannot find location of object in window (" << window_title << ")";
        return -1;
    }

    obj_center_x = obj_x + obj_w/2;
    obj_center_y = obj_y + obj_h/2;

    return 0;
}

void AjWin::doClick()
{
    if( obj_center_x==0 || obj_center_x==0 )
    {
        qDebug() << "object location problem! fuck this shit, code shouldn't reach here";
    }

    GetCursorPos(&cursor_last);

    SetCursorPos(obj_center_x + offset_x, obj_center_y + offset_y);

    Sleep(AJ_MOUSE_DELAY);

    if( cmd_type==AJ_CMD_LMB )
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
    else if( cmd_type==AJ_CMD_RMB )
    {
        mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    }
    else if( cmd_type==AJ_CMD_MMB )
    {
        mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
    }
    else if( cmd_type==AJ_CMD_DCLICK )
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(AJ_DOUBLE_DELAY);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    }
    else if( cmd_type==AJ_CMD_CHILDID )
    {
        //Do nothing, Child ID is already printed
    }
    else
    {
        qDebug() << "click type problem! fuck this shit, code shouldn't reach here";
        return;
    }

    Sleep(AJ_MOUSE_DELAY);

    SetCursorPos(cursor_last.x, cursor_last.y);  //any value other than main window
}

QString aj_click_name(int cmd_type)
{
    if( cmd_type==AJ_CMD_LMB )
    {
        return "left click";
    }
    else if( cmd_type==AJ_CMD_RMB )
    {
        return "right click";
    }
    else if( cmd_type==AJ_CMD_MMB )
    {
        return "middle click";
    }
    else if( cmd_type==AJ_CMD_DCLICK )
    {
        return "double click";
    }
    else if( cmd_type==AJ_CMD_CHILDID )
    {
        return "child id";
    }
    else
    {
        qDebug() << "Error: click type not found, type:" << cmd_type;
        return "";
    }
}

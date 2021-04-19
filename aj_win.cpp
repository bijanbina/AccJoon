#include "aj_win.h"

int acc_debug = 0;

AjWin::AjWin(QString acc_path, QString cmd, QString accName, int o_x, int o_y)
{
    active_window = NULL;
    active_win_pAcc = NULL;
    window_title = "";
    path = acc_path.split('.');
    cmd_type = aj_clickType(cmd);
    acc_name = accName;

    offset_x = o_x;
    offset_y = o_y;
}

QString AjWin::getAccName(IAccessible *pAcc, long childId)
{
    BSTR bstrName;
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = childId;
    /*HRESULT hr = */pAcc->get_accName(varChild, &bstrName);
    return QString::fromWCharArray(bstrName);
}

long AjWin::getChildCount(IAccessible *pAcc)
{
    long cc;
    pAcc->get_accChildCount(&cc);
    return cc;
}

IAccessible* AjWin::getActiveWinPAcc()
{
    IAccessible *pAcc;

    AccessibleObjectFromWindow(active_window, OBJID_WINDOW,
                               IID_IAccessible, (void**) &pAcc);
    return pAcc;
}

// return Acc specific chilren
IAccessible* AjWin::getAcc(QStringList varpath, IAccessible *pAcc)
{
    VARIANT vtChild;
    if( varpath.size()>0 )
    {
        long childCount = getChildCount(pAcc);
        long returnCount;
        VARIANT* pArray = new VARIANT[childCount];

        AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);

        // FIXME: handle error if number
        int indx = varpath[0].toInt() - 1;
        vtChild = pArray[indx];

        if( acc_debug )
        {
            qDebug() << QString("--path:") + varpath.join('.') + " childCount:" + QString::number(childCount) + " " +
                     getAccName(pAcc, CHILDID_SELF) + " indx:" + QString::number(indx) + " " + QString::number(returnCount);
        }

        // return if path is not correct
        if(indx > childCount)
        {
            qDebug() <<"path is not correct, index greater than child";
            return NULL;
        }
        else if( vtChild.vt==VT_DISPATCH )
        {
            IDispatch* pDisp = vtChild.pdispVal;
            IAccessible* pChild = NULL;
            pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);

            return getAcc(varpath.mid(1), pChild);
        }
        else
        {
            qDebug() <<"child is not an Acc, variable type:" << vtChild.vt;
            return NULL;
        }
    }
    else
    {
        if ( acc_name.length() )
        {
            return getAccName(acc_name, pAcc);
        }
        else
        {
            return pAcc;
        }
    }
}

IAccessible* AjWin::getAccName(QString name, IAccessible *pAcc)
{
    VARIANT vtChild;

    long childCount = getChildCount(pAcc);
    long returnCount;
    VARIANT* pArray = new VARIANT[childCount];

    AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);

    //FIXME: handle error if number

    for( int i=0 ; i<childCount ; i++ )
    {
        vtChild = pArray[i];

        if( vtChild.vt==VT_DISPATCH )
        {
            IDispatch* pDisp = vtChild.pdispVal;
            IAccessible* pChild = NULL;
            pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
            QString child_name = getAccName(pChild, CHILDID_SELF);

            if( acc_debug )
            {
                qDebug() << QString("--path:") + name + " childCount:" + QString::number(childCount) + " " +
                         child_name + " indx:" + QString::number(i) + " " + QString::number(returnCount);
            }

            if ( child_name.contains(name) )
            {
                //qDebug() << "found the child";
                if ( cmd_type==AJ_CMD_CHILDID )
                {
                    qDebug() << i;
                }
                return pChild;
            }
        }
        else
        {
            qDebug() <<"child is not an Acc, variable type:" << vtChild.vt;
            return NULL;
        }
    }

    qDebug() <<"No child found with name" << name;
    return NULL;
}

void AjWin::listChildren(IAccessible *pAcc, QString path)
{
    QString pAcc_name = getAccName(pAcc, CHILDID_SELF);
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
                QString child_name = getAccName(pChild, CHILDID_SELF);
                long child_count = getChildCount(pChild);
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
                        "] ELEMENT - " + getAccName(pAcc, vtChild.lVal)
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

    active_win_pAcc = getActiveWinPAcc();
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

    IAccessible *object_acc = getAcc(path, active_win_pAcc);
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

int aj_clickType(QString click_short_name)
{
    if( click_short_name.compare("L", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_LMB;
    }
    else if( click_short_name.compare("R", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_RMB;
    }
    else if( click_short_name.compare("M", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_MMB;
    }
    else if( click_short_name.compare("D", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_DCLICK;
    }
    else if( click_short_name.compare("C", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_CHILDID;
    }
    else
    {
        qDebug() << "Error: click" << click_short_name << "is not acceptable";
        return -1;
    }
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

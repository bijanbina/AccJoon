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
    qDebug() << "####### getChildren: " + path;

    long childCount;
    long returnCount;
    HRESULT hr = pAcc->get_accChildCount(&childCount);
    VARIANT* pArray = new VARIANT[childCount];
    hr = AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);
    if( path.length() )
    {
        path += QString(".");
    }

    for (int i=0 ; i<returnCount ; i++ )
    {
        VARIANT vtChild = pArray[i];
        if (vtChild.vt == VT_DISPATCH)
        {
            IDispatch* pDisp = vtChild.pdispVal;
            IAccessible* pChild = NULL;
            hr = pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
            if (hr == S_OK)
            {
                QString child_name = aj_getAccName(pAcc, i);
                long child_count = aj_getChildCount(pChild);
                qDebug() << "acc[" + QString::number(i) + "/" + QString::number(returnCount-1)
                            + "] name:" + child_name +
                            " child:" + QString::number(child_count)
                            + " path:" + path + QString::number(i+1);
                if(child_count>0)
                {
                    listChildren(pChild, path + QString::number(i+1));
                }
                pChild->Release();
            }
            pDisp->Release();
        }
        // Else it's a child element so we have to call accNavigate on the parent,
        //   and we do not recurse because child elements can't have children.
        else
        {
            qDebug() <<"Element:" + pAcc_name +
                        " - child[" + QString::number(i) + "/" + QString::number(returnCount-1) +
                        "] name:" + aj_getAccName(pAcc, vtChild.lVal)
                        + " path:" + path + QString::number(i+1);
        }
    }
    delete[] pArray;
    qDebug() <<"####### Exit getChildren: " + path;
}

IAccessible *AjWin::getParnetAcc(HWND hWindow)
{
    char buffer[256];
    IAccessible *acc;

    if( hWindow==NULL )
    {
//        hWindow = GetForegroundWindow();
        qDebug() << "Switching to active window";
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

int AjWin::doKey(AjCommand *cmd)
{
    AjKeyboard keyboard;
    if( hwnd!=NULL )
    {
        SetForegroundWindow(hwnd);
    }
    QThread::msleep(10);

    AjKey key = aj_getKey(cmd->args[0]);

    if( key.alt_key )
    {
        keyboard.pressKey(KEY_LEFTALT);
    }
    if( key.ctrl_key )
    {
        QThread::msleep(20);
        keyboard.pressKey(KEY_LEFTCTRL);
    }
    if( key.shift_key )
    {
        QThread::msleep(20);
        keyboard.pressKey(KEY_LEFTSHIFT);
    }
    if( key.meta_key )
    {
        QThread::msleep(20);
        keyboard.pressKey(KEY_META);
    }
    QThread::msleep(1000);
    keyboard.sendKey(key.key);
    if( key.alt_key )
    {
        QThread::msleep(20);
        keyboard.releaseKey(KEY_LEFTALT);
    }
    if( key.ctrl_key )
    {
        QThread::msleep(20);
        keyboard.releaseKey(KEY_LEFTCTRL);
    }
    if( key.shift_key )
    {
        QThread::msleep(20);
        keyboard.releaseKey(KEY_LEFTSHIFT);
    }
    if( key.meta_key )
    {
        QThread::msleep(20);
        keyboard.releaseKey(KEY_META);
    }

    return 0;
}

int AjWin::doAcc(AjCommand *cmd)
{
    IAccessible *win_pAcc, *acc;
    if( hwnd==NULL )
    {
        qDebug() << "Error: HWND is not set";
        return -1;
    }
    SetForegroundWindow(hwnd);
    QThread::msleep(10);

    QString path_raw = cmd->args[0].remove("\"").trimmed();
    QStringList path = path_raw.split('.', QString::SkipEmptyParts);

    offset_x = 0;
    offset_y = 0;
    offset_id = 0;
    QString action = "L";
    QString acc_name;

    if( cmd->args.size()>1 )
    {
        action = cmd->args[1];
    }
    if( cmd->args.size()>2 )
    {
        acc_name = cmd->args[2];
    }
    if( cmd->args.size()>3 )
    {
        offset_x = cmd->args[3].toInt();
    }
    if( cmd->args.size()>4 )
    {
        offset_y = cmd->args[4].toInt();
    }
    if( cmd->args.size()>5 )
    {
        offset_id = cmd->args[5].toInt();
    }

    int cmd_type = aj_clickType(action);
    if( cmd_type==-1 )
    {
        qDebug() << "Error: click" << action << "is not acceptable";
        return -1;
    }

    win_pAcc = getParnetAcc(hwnd);
//    qDebug() << "HWND" << win_pAcc->get_accName(0);
    if( win_pAcc==NULL )
    {
        qDebug() << "Error [doAcc]: cannot get parent acc of window ("
                 << window_title << ") HWND" << hwnd;
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
        qDebug() << "Error: cannot get acc in window (" << window_title << ")";
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

    POINT obj_center;
    obj_center = getAccLocation(acc, child_id);
    if( obj_center.x==0 && obj_center.y==0 )
    {
        qDebug() << "Error: cannot get location in window (" << window_title << ")";
        return -1;
    }
    qDebug() << "child_id" << child_id
             << "obj_center" << obj_center.x
             << obj_center.y << ")";

    doClick(obj_center, cmd_type);

    return 0;
}

QString AjWin::readAcc(AjCommand *cmd)
{
    IAccessible *win_pAcc, *acc;
    if( hwnd==NULL )
    {
        qDebug() << "Error: HWND is not set";
        return "";
    }
    SetForegroundWindow(hwnd);
    QThread::msleep(10);

    QString path_raw = cmd->args[0].remove("\"").trimmed();
    QStringList path = path_raw.split('.');

    win_pAcc = getParnetAcc(hwnd);
    if( win_pAcc==NULL )
    {
        qDebug() << "Error: cannot get parent acc of window (" << window_title << ")";
        return "";
    }

    // presume acc_name is empty
    int child_id;
    child_id = path.last().toInt()-1;
    path.removeLast();
//    qDebug() << "child id is" << child_id;

    acc = aj_getAcc(path, win_pAcc);
    if( acc==NULL )
    {
        qDebug() << "Error: cannot get acc in window (" << window_title << ")";
        return "";
    }

    BSTR value;
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = child_id; //CHILDID_SELF?
    HRESULT hr = acc->get_accValue(varChild, &value);

    if( hr!=S_OK )
    {
        qDebug() << "Error: cannot get value of acc (" << path_raw << ")";
        return "";
    }

    return aj_toQString(value);
}

int AjWin::writeAcc(AjCommand *cmd)
{
    IAccessible *win_pAcc, *acc;
    if( hwnd==NULL )
    {
        qDebug() << "Error: HWND is not set";
        return -1;
    }
    SetForegroundWindow(hwnd);
    QThread::msleep(10);

    QString path_raw = cmd->args[0].remove("\"").trimmed();
    QStringList path = path_raw.split('.');

    win_pAcc = getParnetAcc(hwnd);
    if( win_pAcc==NULL )
    {
        qDebug() << "Error: cannot get parent acc of window (" << window_title << ")";
        return -1;
    }

    // presume acc_name is empty
    int child_id;
    child_id = path.last().toInt()-1;
    path.removeLast();
//    qDebug() << "child id is" << child_id;

    acc = aj_getAcc(path, win_pAcc);
    if( acc==NULL )
    {
        qDebug() << "Error: cannot get acc in window (" << window_title << ")";
        return -1;
    }

    BSTR value = SysAllocString(L"");
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = child_id;

    value = aj_toBSTR(cmd->args.last());

    HRESULT hr = acc->put_accValue(varChild, value);

    if( hr!=S_OK )
    {
        qDebug() << "Error: cannot set value of acc (" << path_raw << ")";
        return -1;
    }

    return 0;
}

void AjWin::doClick(POINT obj_center, int cmd)
{
    GetCursorPos(&cursor_last);
//    RECT rect;
//    GetWindowRect(hwnd, &rect);
//    offset_x -= rect.left;
//    offset_y -= rect.top;
    SetCursorPos(obj_center.x + offset_x, obj_center.y + offset_y);
//    aj_setMouse(obj_center.x + offset_x, obj_center.y + offset_y);

    QThread::msleep(AJ_MOUSE_DELAY);
    qDebug() << "doClick offset_x" << offset_x << "offset_y"
             << offset_y;

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

//    SetCursorPos(cursor_last.x, cursor_last.y);  //any value other than main window
}

BSTR aj_toBSTR(QString input)
{
    BSTR result= SysAllocStringLen(0, input.length());
    input.toWCharArray(result);
    return result;
}

QString aj_toQString(BSTR input)
{
    return QString::fromUtf16(reinterpret_cast<ushort*>(input));
}

void AjVar::addVar(QString name, QString value)
{
    int len = vars_name.size();
    for( int i=0 ; i<len ; i++ )
    {
        if( vars_name[i]==name )
        {
            vars_value[i] = value;
            return;
        }
    }
    vars_name.push_back(name);
    vars_value.push_back(value);
}

QString AjVar::getVal(QString name)
{
    int len = vars_name.size();
    for( int i=0; i<len; i++ )
    {
        if( vars_name[i]==name )
        {
            return vars_value[i];
        }
    }
    return "";
}

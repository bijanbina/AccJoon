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

void AjWin::setFocus(HWND hWindow)
{
    char buffer[256];

    if( hWindow==NULL )
    {
//        hWindow = GetForegroundWindow();
        qDebug() << "Switching to active window";
        if( hWindow==NULL )
        {
            qDebug() << "Error: cannot get foreground window handler";
            return;
        }
    }

    GetWindowTextA(hWindow, buffer, 256);
    window_title = QString(buffer);
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
    keyboard.execKey(&key);

    return 0;
}

int AjWin::doAcc(AjCommand *cmd)
{
    AjAccCmd acc_cmd;
    if( hwnd==NULL )
    {
        qDebug() << "Error: HWND is not set";
        return -1;
    }
    SetForegroundWindow(hwnd);
    QThread::msleep(10);

    QString path = cmd->args[0].remove("\"").trimmed();

    if( cmd->args.size()>1 )
    {
        acc_cmd.action = cmd->args[1];
    }
    if( cmd->args.size()>2 )
    {
       acc_cmd.acc_name = cmd->args[2];
    }
    if( cmd->args.size()>3 )
    {
       acc_cmd.offset_x = cmd->args[3].toInt();
    }
    if( cmd->args.size()>4 )
    {
        acc_cmd.offset_y = cmd->args[4].toInt();
    }
    if( cmd->args.size()>5 )
    {
        acc_cmd.offset_id = cmd->args[5].toInt();
    }

    setFocus(hwnd);
    POINT obj_center;
    obj_center = getAccLocation(acc_cmd, hwnd, path);

    if( obj_center.x==0 && obj_center.y==0 )
    {
        qDebug() << "Error: cannot get location in window (" << window_title << ")";
        return -1;
    }
    qDebug() << "obj_center" << obj_center.x
             << obj_center.y << ")";

    aj_mouseClick(obj_center, acc_cmd);

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

    setFocus(hwnd);

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

    win_pAcc = setFocus(hwnd);
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

#include "aj_acc_prop.h"

QString aj_getAccName(HWND hwnd, QString path)
{
    QString parent = aj_getAccParent(path);
    IAccessible *acc = aj_getAccHWND(hwnd, parent);
    int child_id = path.split(".").last().toInt();
    qDebug() << "par" << parent << "chl" << child_id;
    return aj_getAccName(acc, child_id-1);
}

POINT aj_getAccLocationI4(IAccessible *acc, int childID)
{
    VARIANT varChild;
    POINT ret;

    varChild.vt = VT_I4;
    varChild.lVal = childID;

    long obj_x = 0, obj_y = 0, obj_w = 0, obj_h = 0;

    acc->accLocation(&obj_x, &obj_y, &obj_w, &obj_h, varChild);
    if( obj_x==0 || obj_y==0 || obj_h<0 || obj_w<0 )
    {
        qDebug() << "aj_getAccLocationI4 Failed x y h w" << obj_x
                 << obj_y << obj_h << obj_w;
        return ret;
    }
    qDebug() << "aj_getAccLocationI4 x y w h" << obj_x
             << obj_y << obj_w << obj_h;

    ret.x = obj_x + obj_w/2;
    ret.y = obj_y + obj_h/2;

    return ret;
}

POINT aj_getAccLocation(IAccessible *acc, int childID)
{
    POINT ret;
    long returnCount;
    long childCount = aj_getChildCount(acc);
    VARIANT* pArray = new VARIANT[childCount];
    AccessibleChildren(acc, 0L, childCount, pArray, &returnCount);

    if( childID<childCount )
    {
        VARIANT vtChild  = pArray[childID];
        if( vtChild.vt==VT_DISPATCH )
        {
            IDispatch   *pDisp = vtChild.pdispVal;
            IAccessible *pChild = NULL;
            pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
            return aj_getAccLocationI4(pChild, CHILDID_SELF);
        }
        else if( vtChild.vt==VT_I4 ) //An element object
        {
            qDebug() << "getAccLocation element";
            return aj_getAccLocationI4(acc, childID);
        }
    }
    else
    {
        qDebug() << "ChildID exceed, id" << childID << "count"
                 << childCount;
    }

    return ret;
}

POINT aj_getAccLocation(AjAccCmd cmd, HWND hwnd, QString path)
{
    POINT obj_center;
    IAccessible *win_pAcc, *acc;
    QStringList path_split = path.split('.', QString::SkipEmptyParts);

    obj_center.x = 0;
    obj_center.y = 0;

    win_pAcc = aj_getWinPAcc(hwnd);
//    qDebug() << "HWND" << win_pAcc->get_accName(0);
    if( win_pAcc==NULL )
    {
        qDebug() << "Error [doAcc]: cannot get parent acc of HWND ("
                 << hwnd;
        return obj_center;
    }
//    aj_accList(win_pAcc, "");

    //get parent path
    int child_id;
    if( cmd.acc_name.isEmpty() )
    {
        child_id = path_split.last().toInt()-1;
        path_split.removeLast();
        qDebug() << "child id is" << child_id;
    }

    acc = aj_getAcc(path_split, win_pAcc);
    qDebug() << "---------------------------------";
    if( acc==NULL )
    {
        qDebug() << "Error: cannot get acc in HWND (" << hwnd << ")";
        return obj_center;
    }

    if( cmd.acc_name.length() )
    {
        child_id = aj_getChildId(cmd.acc_name, acc) + cmd.offset_id;
        if( child_id==-1 )
        {
            qDebug() << "Failed to get child id";
            return obj_center;
        }

        if( cmd.action==AJ_CMD_CHILDID )
        {
            qDebug() << child_id;
            return obj_center;
        }
    }


    obj_center = aj_getAccLocation(acc, child_id);
    return  obj_center;
}

QString aj_getAccValue(HWND hwnd, QString path)
{
    BSTR value;
    QString parent = aj_getAccParent(path);
    IAccessible *acc = aj_getAccHWND(hwnd, parent);
    VARIANT varChild = aj_getVarChild(path);
    HRESULT hr = acc->get_accValue(varChild, &value);

    if( hr!=S_OK )
    {
        qDebug() << "Error: cannot get value of acc ("
                 << path << ")";
        return "";
    }

    return aj_toQString(value);
}

QString aj_getAccState(HWND hwnd, QString path)
{
    QString parent = aj_getAccParent(path);
    IAccessible *acc = aj_getAccHWND(hwnd, parent);
    VARIANT varChild = aj_getVarChild(path);

    VARIANT varState;
    VariantInit(&varState);
    HRESULT hr = acc->get_accState(varChild, &varState);

    if( hr!=S_OK )
    {
        qDebug() << "Error: cannot get state of acc ("
                 << path << ")";
        return "";
    }
    else if( hr==S_OK && varState.vt==VT_I4 )
    {
        return aj_getStateName(varState.lVal);
    }
    return "";
}

QString aj_getAccType(HWND hwnd, QString path)
{
    QString parent = aj_getAccParent(path);
    IAccessible *acc = aj_getAccHWND(hwnd, parent);
    VARIANT varChild = aj_getVarChild(path);

    VARIANT varRole;
    VariantInit(&varRole);
    HRESULT hr = acc->get_accRole(varChild, &varRole);

    if( hr!=S_OK )
    {
        qDebug() << "Error: cannot get role of acc ("
                 << path << ")";
        return "";
    }
    else
    {
        char buffer[1024];
        long role = varRole.lVal;
        GetRoleTextA(role, buffer, 1024);
        return buffer;
    }
    return "";
}

QString aj_getStateName(long val)
{
    if( val&STATE_SYSTEM_CHECKED )
    {
        qDebug() << "aj_getStateName"
                 << val << "checked";
        return "checked";
    }
    else
    {
        qDebug() << "aj_getStateName"
                 << val << "unchecked";
        return "unchecked";
    }
}

QString aj_getChild(HWND hwnd, QString path, QString name)
{
    IAccessible *acc = aj_getAccHWND(hwnd, path);
    int child_id = aj_getChildId(name, acc);
    path += "." + QString::number(child_id+1);
    return path;
}

void aj_setAccValue(HWND hwnd, QString path, QString val)
{
    QStringList path_split = path.split('.', QString::SkipEmptyParts);
    // presume acc_name is empty
    int child_id;
    child_id = path_split.last().toInt()-1;
    path_split.removeLast();

    IAccessible *win_pAcc = aj_getWinPAcc(hwnd);
//    qDebug() << "child id is" << child_id;

    IAccessible *acc = aj_getAcc(path_split, win_pAcc);
    if( acc==NULL )
    {
        qDebug() << "Error: cannot get acc in HWND (" << hwnd << ")";
        return;
    }

    BSTR val_bstr = aj_toBSTR(val);
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = child_id;

    HRESULT hr = acc->put_accValue(varChild, val_bstr);

    if( hr!=S_OK )
    {
        qDebug() << "Error: cannot set value of acc (" << path << ")";
    }
}

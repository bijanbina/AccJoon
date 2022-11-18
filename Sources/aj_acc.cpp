#include "aj_acc.h"

QString aj_getAccNameI4(IAccessible *acc, long childId)
{
    BSTR bstrName;
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = childId;
    acc->get_accName(varChild, &bstrName);

    return QString::fromWCharArray(bstrName);
}

QString aj_getAccName(IAccessible *acc, long childId)
{
    long childCount = aj_getChildCount(acc);
    long returnCount;
    VARIANT *pArray = new VARIANT[childCount];
    AccessibleChildren(acc, 0L, childCount, pArray, &returnCount);

    VARIANT vtChild = pArray[childId];

    if( childId>childCount )
    {
        return "";
    }
    else if( vtChild.vt==VT_DISPATCH )
    {
        IDispatch   *pDisp  = vtChild.pdispVal;
        IAccessible *pChild = NULL;
        pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
        return aj_getAccNameI4(pChild, CHILDID_SELF);
    }
    else if( vtChild.vt==VT_I4 ) //An element object
    {
        return aj_getAccNameI4(acc, childId);
    }
    else
    {
        return "";
    }
}

POINT getAccLocationI4(IAccessible *acc, int childID)
{
    VARIANT varChild;
    POINT ret;

    varChild.vt = VT_I4;
    varChild.lVal = childID;

    long obj_x = 0, obj_y = 0, obj_w = 0, obj_h = 0;

    acc->accLocation(&obj_x, &obj_y, &obj_w, &obj_h, varChild);
    if( obj_x==0 || obj_y==0 || obj_h<0 || obj_w<0 )
    {
        qDebug() << "getAccLocationI4 Failed x y h w" << obj_x
                 << obj_y << obj_h << obj_w;
        return ret;
    }
    qDebug() << "getAccLocationI4 x y w h" << obj_x
             << obj_y << obj_w << obj_h;

    ret.x = obj_x + obj_w/2;
    ret.y = obj_y + obj_h/2;

    return ret;
}

POINT getAccLocation(IAccessible *acc, int childID)
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
            return getAccLocationI4(pChild, CHILDID_SELF);
        }
        else if( vtChild.vt==VT_I4 ) //An element object
        {
            qDebug() << "getAccLocation element";
            return getAccLocationI4(acc, childID);
        }
    }
    else
    {
        qDebug() << "ChildID exceed, id" << childID << "count"
                 << childCount;
    }

    return ret;
}

long aj_getChildCount(IAccessible *pAcc)
{
    long cc;
    pAcc->get_accChildCount(&cc);
    return cc;
}

IAccessible* aj_getWinPAcc(HWND window)
{
    IAccessible *pAcc;

    AccessibleObjectFromWindow(window, OBJID_WINDOW,
                               IID_IAccessible, (void**) &pAcc);
    return pAcc;
}

IAccessible* aj_getChild(IAccessible *acc, int index)
{
    long childCount = aj_getChildCount(acc);
    long returnCount;
    VARIANT* pArray = new VARIANT[childCount];
    AccessibleChildren(acc, 0L, childCount, pArray, &returnCount);

    VARIANT vtChild  = pArray[index];

//    QString msg = "Get Child:" + QString::number(index+1);
//    msg += " childCount:" + QString::number(childCount) + " " +
//            aj_getAccName(acc, CHILDID_SELF) + " " + QString::number(returnCount);
//    logMessage(msg);

    // return if path is not correct
    if( index>childCount )
    {
        QString msg = "path is not correct, index greater than child";
        qDebug() << msg;
        return NULL;
    }
    else if( vtChild.vt==VT_DISPATCH )
    {
        IDispatch* pDisp = vtChild.pdispVal;
        IAccessible* pChild = NULL;
        pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);

        return pChild;
    }
    else if( vtChild.vt==VT_I4 ) //An element object
    {
        QString msg = "child is an element " + QString::number(vtChild.iVal);
        msg += " name = " + aj_getAccName(acc, vtChild.iVal);
        logMessage(msg);

        return NULL;
    }
    else
    {
        QString msg = "child is not an Acc, variable type: ";
        msg += QString::number(vtChild.vt) + ", index:";
        msg += QString::number(index);
        logMessage(msg);

        return NULL;
    }
}

// return Acc specific chilren
IAccessible* aj_getAcc(QStringList varpath, IAccessible *pAcc)
{
    if( varpath.size()>0 )
    {
        int index = varpath[0].toInt() - 1;
        IAccessible* pChild = aj_getChild(pAcc, index);

        if ( pChild!=NULL )
        {
            return aj_getAcc(varpath.mid(1), pChild);
        }
        else
        {
            return NULL;
        }

    }
    else
    {
        return pAcc;
    }
}

IAccessible* aj_getAcc(HWND hwnd, QString path)
{
    IAccessible *acc;
    QStringList path_split = path.split('.', QString::SkipEmptyParts);
    // presume acc_name is empty
    path_split.removeLast();

    IAccessible *win_pAcc = aj_getWinPAcc(hwnd);
    aj_accList(win_pAcc, "");
    acc = aj_getAcc(path_split, win_pAcc);
    if( acc==NULL )
    {
        qDebug() << "Error: cannot get acc in window ("
                 << hwnd << ")";
        return acc;
    }

    return acc;
}

VARIANT aj_getVarChild(QString path)
{
    int child_id;
    QStringList path_split = path.split('.', QString::SkipEmptyParts);
    child_id = path_split.last().toInt()-1;
    path_split.removeLast();

    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = child_id; //CHILDID_SELF?
    return varChild;
}

int aj_getChildId(QString name, IAccessible *acc)
{
    long childCount = aj_getChildCount(acc);

    for( int i=0 ; i<childCount ; i++ )
    {
        QString child_name = aj_getAccName(acc, i);
//        QString msg = "Get ChildID:" + QString::number(i);
//        msg += " childCount:" + QString::number(childCount) + " " +
//                child_name;
//        logMessage(msg);

        if ( child_name.contains(name) )
        {
           return i;
        }
    }

    return -1;
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

POINT getAccLocation(AjAccCmd cmd, HWND hwnd, QString path)
{
    POINT obj_center;
    IAccessible *win_pAcc, *acc;
    QStringList path_split = path.split('.', QString::SkipEmptyParts);

    obj_center.x = -1;
    obj_center.y = -1;

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


    obj_center = getAccLocation(acc, child_id);
    return  obj_center;
}

QString getAccValue(HWND hwnd, QString path)
{
    BSTR value;
    IAccessible *acc = aj_getAcc(hwnd, path);
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

QString getAccState(HWND hwnd, QString path)
{
    IAccessible *acc = aj_getAcc(hwnd, path);
    VARIANT varChild = aj_getVarChild(path);

    VARIANT varState;
    VariantInit(&varState);
    HRESULT hr = acc->get_accState(varChild, &varState);

    if( hr!=S_OK )
    {
        qDebug() << "Error: cannot get value of acc ("
                 << path << ")";
        return "";
    }
    else if( hr==S_OK && varState.vt==VT_I4 )
    {
        return aj_getStateName(varState.lVal);
    }
    return "";
}

QString aj_getStateName(long val)
{
    if( val&STATE_SYSTEM_CHECKED )
    {
        return "checked";
    }
    else
    {
        return "unchecked";
    }
}

void setAccValue(HWND hwnd, QString path, QString val)
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

void aj_accList(IAccessible *pAcc, QString path)
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
                    aj_accList(pChild, path + QString::number(i+1));
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

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
    VARIANT* pArray = new VARIANT[childCount];
    AccessibleChildren(acc, 0L, childCount, pArray, &returnCount);

    VARIANT vtChild  = pArray[childId];

    // return if path is not correct
    if(childId > childCount)
    {
        return "";
    }
    else if( vtChild.vt==VT_DISPATCH )
    {
        IDispatch* pDisp = vtChild.pdispVal;
        IAccessible* pChild = NULL;
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
        return ret;
    }

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

    // return if path is not correct
    if(childID < childCount)
    {
        VARIANT vtChild  = pArray[childID];
        if( vtChild.vt==VT_DISPATCH )
        {
            IDispatch* pDisp = vtChild.pdispVal;
            IAccessible* pChild = NULL;
            pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
            return getAccLocationI4(pChild, CHILDID_SELF);
        }
        else if( vtChild.vt==VT_I4 ) //An element object
        {
            return getAccLocationI4(acc, childID+1);
        }
    }
    else
    {
        qDebug() << "ChildID exceed, id"<< childID << "count" << childCount;
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

    QString msg = "Get Child:" + QString::number(index+1);
    msg += " childCount:" + QString::number(childCount) + " " +
            aj_getAccName(acc, CHILDID_SELF) + " " + QString::number(returnCount);
    logMessage(msg);

    // return if path is not correct
    if(index > childCount)
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
        msg += QString::number(vtChild.vt);
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

int aj_getChildId(QString name, IAccessible *pAcc)
{
    long childCount = aj_getChildCount(pAcc);

    for( int i=0 ; i<childCount ; i++ )
    {
        QString child_name = aj_getAccName(pAcc, i);
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

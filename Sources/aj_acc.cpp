#include "aj_acc.h"

QString aj_getAccNameI4(IAccessible *acc, long childId)
{
    BSTR bstrName;
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = childId;
    acc->get_accName(varChild, &bstrName);

    QString ret = QString::fromWCharArray(bstrName);
    SysFreeString(bstrName);
    return ret;
}

QString aj_accGetName(IAccessible *acc, long childId)
{
    long child_count = aj_getChildCount(acc);
    if( child_count<0 )
    {
        return "";
    }
    long returnCount;
    VARIANT *pArray = new VARIANT[child_count];
    AccessibleChildren(acc, 0L, child_count, pArray, &returnCount);

    VARIANT vtChild = pArray[childId];

    if( childId>child_count )
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

QString aj_getAccParent(QString path)
{
    QStringList path_split = path.split(".");
    path_split.removeLast();
    QString path_combine = path_split.join(".");
    return path_combine;
}

long aj_getChildCount(IAccessible *pAcc)
{
    long cc;
    if( pAcc==NULL )
    {
        return -1;
    }
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

IAccessible* aj_accGetChild(IAccessible *acc, int index)
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
        msg += " name = " + aj_accGetName(acc, vtChild.iVal);
        logMessage(msg);

        return NULL;
    }
    else
    {
        QString msg = "child is not an Acc, child count: ";
        msg += QString::number(childCount) + ", index:";
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
        IAccessible* pChild = aj_accGetChild(pAcc, index);
//        aj_accList2(pAcc);

        if( pChild!=NULL )
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

IAccessible* aj_getAccHWND(HWND hwnd, QString path)
{
    IAccessible *acc = NULL;
    QStringList path_split = path.split('.', QString::SkipEmptyParts);

    IAccessible *win_pAcc = aj_getWinPAcc(hwnd);
    if( win_pAcc==NULL )
    {
        qDebug() << "Error: cannot get p_acc in window ("
                 << hwnd << ")";
        return acc;
    }
//    aj_accList(win_pAcc, "");
    acc = aj_getAcc(path_split, win_pAcc);

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
        QString child_name = aj_accGetName(acc, i);
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

void aj_accList(IAccessible *pAcc, QString path)
{
    QString pAcc_name = aj_accGetName(pAcc, CHILDID_SELF);
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
                QString child_name = aj_accGetName(pAcc, i);
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
                        "] name:" + aj_accGetName(pAcc, vtChild.lVal)
                        + " path:" + path + QString::number(i+1);
        }
    }
    delete[] pArray;
    qDebug() <<"####### Exit getChildren: " + path;
}

void aj_accListChild(IAccessible *pAcc)
{
    QString pAcc_name = aj_accGetName(pAcc, CHILDID_SELF);

    long childCount;
    long returnCount;
    HRESULT hr = pAcc->get_accChildCount(&childCount);
    VARIANT* pArray = new VARIANT[childCount];
    hr = AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);

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
                QString child_name = aj_accGetName(pAcc, i);
                long child_count = aj_getChildCount(pChild);
                qDebug() << "acc[" + QString::number(i) + "/" + QString::number(returnCount-1)
                            + "] name:" + child_name +
                            " child:" + QString::number(child_count);
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
                        "] name:" + aj_accGetName(pAcc, vtChild.lVal);
        }
    }
    delete[] pArray;
}

QString aj_findAcc(HWND hwnd, QString path, QString name)
{
    clock_t start = clock();
    IAccessible *win_pAcc = aj_getWinPAcc(hwnd);
    qDebug() << "pacc" << getDiffTime(start);
    QStringList path_list = path.split(".");
    start = clock();
    QString path_c = aj_findAcc(win_pAcc, path_list, name);
    qDebug() << "findAcc" << getDiffTime(start);
    return path_c; // complete path
}

QString aj_findAcc(IAccessible *acc, QStringList path_list, QString name)
{
    int search_index = path_list.indexOf("?");
    QStringList fix_part = path_list.mid(0,search_index);
    QStringList var_part = path_list.mid(search_index);

    clock_t start = clock();
    IAccessible *acc_part1 = aj_getAcc(fix_part, acc);
    qDebug() << "findAcc1" << getDiffTime(start);
    start = clock();
    IAccessible *acc_full = NULL;

    int child_count = aj_getChildCount(acc_part1);
    for( int i=0; i<child_count; i++)
    {
        var_part[0] = QString::number(i+1);
        if( var_part.contains("?") ) // recursive part
        {
            QString ret = aj_findAcc(acc_part1, var_part, name);
            if( ret.length() )
            {
                return fix_part.join(".") + "." + ret;
            }
            else
            {
                continue;
            }
        }
        QString parent = aj_getAccParent(var_part.join("."));
        acc_full = aj_getAcc(parent.split("."), acc_part1);

        if( acc_full )
        {
            int child_id = var_part.back().toInt()-1;
            QString acc_name = aj_accGetName(acc_full, child_id);
            qDebug() << "var_part" << var_part[0] << acc_name << child_id;
            if( acc_name==name )
            {
                QStringList total_list = fix_part + var_part;
                return total_list.join(".");
            }
        }
    }
    return "";
}

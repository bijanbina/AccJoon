#include "aj_acc.h"


QString aj_getAccName(IAccessible *pAcc, long childId)
{
    BSTR bstrName;
    VARIANT varChild;
    varChild.vt = VT_I4;
    varChild.lVal = childId;
    pAcc->get_accName(varChild, &bstrName);

    return QString::fromWCharArray(bstrName);
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

// return Acc specific chilren
IAccessible* aj_getAcc(QStringList varpath, IAccessible *pAcc)
{
    VARIANT vtChild;
    if( varpath.size()>0 )
    {
        long childCount = aj_getChildCount(pAcc);
        long returnCount;
        VARIANT* pArray = new VARIANT[childCount];

        AccessibleChildren(pAcc, 0L, childCount, pArray, &returnCount);

        // FIXME: handle error if number
        int indx = varpath[0].toInt() - 1;
        vtChild = pArray[indx];

        QString msg = "--path:";
        msg += varpath.join('.') + " childCount:" + QString::number(childCount) + " " +
                aj_getAccName(pAcc, CHILDID_SELF) + " indx:" + QString::number(indx) + " " + QString::number(returnCount);
        logMessage(msg);


        // return if path is not correct
        if(indx > childCount)
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

            return aj_getAcc(varpath.mid(1), pChild);
        }
        else if( vtChild.vt==VT_I4 ) //An element object
        {
            qDebug() << "Hello Baby";

            QString msg = "child is an element " + QString::number(vtChild.iVal);
            msg += " name = " + aj_getAccName(pAcc, vtChild.iVal);
            logMessage(msg);

            return NULL;
        }
        else
        {
            QString msg = "child is not an Acc, variable type: ";
            msg += QString::number(vtChild.vt);
            logMessage(msg);

            IDispatch* pDisp = vtChild.pdispVal;
            IAccessible* pChild = NULL;
            pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
            QString child_name = aj_getAccName(pChild, CHILDID_SELF);

            msg = "--path:";
            msg += child_name + " childCount:" + QString::number(childCount) + " " +
                    aj_getAccName(pAcc, CHILDID_SELF) + " indx:" + QString::number(indx) + " " + QString::number(returnCount);
            logMessage(msg);
            return NULL;
        }
    }
    else
    {
//        if ( acc_name.length() )
//        {
//            return aj_getAccName(acc_name, pAcc);
//        }
//        else
//        {
            return pAcc;
//        }
    }
}

IAccessible* aj_getAccName(QString name, IAccessible *pAcc)
{
    VARIANT vtChild;

    long childCount = aj_getChildCount(pAcc);
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
            QString child_name = aj_getAccName(pChild, CHILDID_SELF);

            QString msg = "--path:";
            msg += name + " childCount:" + QString::number(childCount) + " " +
                    aj_getAccName(pAcc, CHILDID_SELF) + " indx:" + QString::number(i) + " " + QString::number(returnCount);
            logMessage(msg);

            if ( child_name.contains(name) )
            {
                //qDebug() << "found the child";
//                if ( cmd_type==AJ_CMD_CHILDID )
//                {
//                    qDebug() << i;
//                }

//                if ( offset_id )
//                {
//                    vtChild = pArray[i+offset_id];
//                    if( vtChild.vt==VT_DISPATCH )
//                    {
//                        pDisp = vtChild.pdispVal;
//                        pChild = NULL;
//                        pDisp->QueryInterface(IID_IAccessible, (void**) &pChild);
//                        return pChild;
//                    }
//                    else
//                    {
//                        qDebug() <<"child offset is not an Acc, variable type:" << vtChild.vt;
//                        return NULL;
//                    }
//                }
//                else // if offset_id==0
//                {
                    return pChild;
//                }
            }
        }
        else
        {
            QString msg = "child ";
            msg += QString::number(i) + "is not an Acc, variable type:" + QString::number(vtChild.vt);
            logMessage(msg);
        }
    }

    QString msg = "No child found with name ";
    msg += name;
    logMessage(msg);
    return NULL;
}


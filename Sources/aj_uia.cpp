#include "aj_uia.h"

AjUia::AjUia(QObject *parent): QObject(parent)
{
    // Get a pointer to the IUIAutomation interface. It is assumed that CoInitialize
    // has already been called.
    HRESULT hr = CoCreateInstance(UUID_CUIAutomation, NULL,
                                  CLSCTX_INPROC_SERVER, UUID_IUIAutomation,
                                  (LPVOID *)&pAutomation);
}

AjUia::~AjUia()
{
    ;
}

IUIAutomationElement* AjUia::getElement(HWND hwnd)
{
    IUIAutomationElement *uia = NULL;
    pAutomation->ElementFromHandle(hwnd, &uia);

    return uia;
}

void AjUia::list(IAccessible *pAcc, QString path)
{
//    QString pAcc_name = aj_getAccName(pAcc, CHILDID_SELF);
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
                QString child_name = ""; //aj_getAccName(pAcc, i);
                long child_count = 1; //aj_getChildCount(pChild);
                qDebug() << "acc[" + QString::number(i) + "/" + QString::number(returnCount-1)
                            + "] name:" + child_name +
                            " child:" + QString::number(child_count)
                            + " path:" + path + QString::number(i+1);
                if(child_count>0)
                {
                    list(pChild, path + QString::number(i+1));
                }
                pChild->Release();
            }
            pDisp->Release();
        }
        // Else it's a child element so we have to call accNavigate on the parent,
        //   and we do not recurse because child elements can't have children.
        else
        {
//            qDebug() <<"Element:" + pAcc_name +
//                        " - child[" + QString::number(i) + "/" + QString::number(returnCount-1) +
//                        "] name:" + aj_getAccName(pAcc, vtChild.lVal)
//                        + " path:" + path + QString::number(i+1);
        }
    }
    delete[] pArray;
    qDebug() <<"####### Exit getChildren: " + path;
}

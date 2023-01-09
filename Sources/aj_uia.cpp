#include "aj_uia.h"

AjUia::AjUia(AjApplication *a)
{
    // Get a pointer to the IUIAutomation interface. It is assumed that CoInitialize
    // has already been called.
    HRESULT hr = CoCreateInstance(UUID_CUIAutomation, NULL,
                                  CLSCTX_INPROC_SERVER, UUID_IUIAutomation,
                                  (LPVOID *)&pAutomation);

    app = a;
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

void AjUia::list(IUIAutomationElement *parent, int indent)
{
//    QString pAcc_name = aj_getAccName(pAcc, CHILDID_SELF);
    qDebug() << "####### getChildren: " + indent;

    IUIAutomationTreeWalker* pControlWalker = NULL;
    IUIAutomationElement* pNode = NULL;

    pAutomation->get_ControlViewWalker(&pControlWalker);
    if (pControlWalker == NULL)
        goto cleanup;

    pControlWalker->GetFirstChildElement(parent, &pNode);
    if (pNode == NULL)
        goto cleanup;

    while (pNode)
    {
        BSTR desc;
        pNode->get_CurrentLocalizedControlType(&desc);
        for( int x=0 ; x<=indent ; x++ )
        {
           qDebug() << L"   ";
        }
        qDebug() << desc << L"\n";
        SysFreeString(desc);

        list(pNode, indent+1);
        IUIAutomationElement* pNext;
        pControlWalker->GetNextSiblingElement(pNode, &pNext);
        pNode->Release();
        pNode = pNext;
    }

cleanup:
    if (pControlWalker != NULL)
        pControlWalker->Release();

    if (pNode != NULL)
        pNode->Release();

    qDebug() <<"####### Exit getChildren: " + indent;
    return;
}

void AjUia::ListWindow(HWND hwnd)
{
    IUIAutomationElement *parent = getElement(hwnd);

    if (parent == NULL)
            return;

    int indent = 0;
    list(parent, indent);
}

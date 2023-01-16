#include "aj_uia.h"

AjUia::AjUia(AjApplication *a)
{
    // Get a pointer to the IUIAutomation interface. It is assumed that CoInitialize
    // has already been called.
    HRESULT hr = CoCreateInstance(UUID_CUIAutomation, NULL,
                                  CLSCTX_INPROC_SERVER, UUID_IUIAutomation,
                                  (LPVOID *)&pAutomation);

    if( hr )
    {
        qDebug() << "UUID_CUIAutomation Failed";
    }

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

void AjUia::list(IUIAutomationElement *parent, QString path)
{
    IUIAutomationTreeWalker* pControlWalker = NULL;
    IUIAutomationElement* pNode = NULL;
    int child_id = 0;

    pAutomation->get_ControlViewWalker(&pControlWalker);
    if( pControlWalker==NULL )
        goto cleanup;

    pControlWalker->GetFirstChildElement(parent, &pNode);
    if( pNode==NULL )
        goto cleanup;

    if( path.length() )
    {
        path += QString(".");
    }

    while( pNode )
    {
        child_id += 1;
        BSTR desc, name;
        pNode->get_CurrentLocalizedControlType(&desc);
        pNode->get_CurrentName(&name);
        QString print_desc = path;
        print_desc.chop(1);
        print_desc += " ";
        print_desc += QString::fromStdWString(desc);
        print_desc += ":";
        print_desc += QString::fromStdWString(name);
        qDebug() << print_desc;
        SysFreeString(desc);

        list(pNode, path + QString::number(child_id+1));
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

    qDebug() <<"####### Exit getChildren: ";
    return;
}

void AjUia::ListWindow(HWND hwnd)
{
    IUIAutomationElement *parent = getElement(hwnd);

    if (parent == NULL)
            return;

    list(parent);
}

QString AjUia::getValue(HWND hwnd, QString path)
{
    return "";
}

void AjUia::setValue(HWND hwnd, QString path, QString val)
{

}

IAccessible* AjUia::getHWND(HWND hwnd, QString path)
{
    return 0;
}

void AjUia::list(IUIAutomationElement *elem)
{
    list(elem, "");
    qDebug() << "list";
}

void AjUia::list2(IUIAutomationElement *elem)
{
    qDebug() << "list2";
}

QString AjUia::getName(HWND hwnd, QString path)
{
    return 0;
}

QString AjUia::getState(HWND hwnd, QString path)
{
    return "";
}

QString AjUia::getType(HWND hwnd, QString path)
{
    return "";
}

QString AjUia::getParent(QString path)
{
    return "";
}

QString AjUia::getChild(HWND hwnd, QString path, QString name)
{
    return "";
}

QString AjUia::find(HWND hwnd, QString path, QString name)
{
    return "";
}

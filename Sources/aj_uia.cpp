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
        qDebug() << "Error 152: Failed to create UUID_CUIAutomation instance."
                 << "hr =" << hr;
        exit(1);
    }

    pAutomation->get_ControlViewWalker(&pControlWalker);
    if( pControlWalker==NULL )
    {
        qDebug() << "Error 153: Failed to get IUIAutomationTreeWalker.";
        exit(1);
    }

    app = a;
}

AjUia::~AjUia()
{
    if( pControlWalker )
    {
        pControlWalker->Release();
    }
}

UiaElement* AjUia::getElement(HWND hwnd)
{
    UiaElement *uia = NULL;
    pAutomation->ElementFromHandle(hwnd, &uia);

    return uia;
}

void AjUia::list(UiaElement* root, QString path)
{
    UiaElement* pNode = NULL;
    int child_id = 0;

    pControlWalker->GetFirstChildElement(root, &pNode);
    if( pNode==NULL )
    {
        return;
    }

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
        print_desc += QString::number(child_id);
        print_desc += " ";
        print_desc += QString::fromStdWString(desc);
        print_desc += ":";
        if( name!=NULL )
        {
            print_desc += QString::fromStdWString(name);
        }
        qDebug() << print_desc;
        SysFreeString(desc);
        SysFreeString(name);

        list(pNode, path + QString::number(child_id));
        UiaElement* pNext;
        pControlWalker->GetNextSiblingElement(pNode, &pNext);
        pNode->Release();
        pNode = pNext;
    }
}

void AjUia::ListWindow(HWND hwnd)
{
    UiaElement *parent = getElement(hwnd);

    if (parent == NULL)
            return;

    list(parent);
}

QString AjUia::getValue(IUIAutomationElement *root, QString path)
{
    VARIANT value;
    IUIAutomationElement *elem = getElem(root, path);

    if( elem==NULL )
    {
        qDebug() << "Error: cannot get value of uia ("
                 << path << ")";
        return "";
    }

    elem->GetCurrentPropertyValue(UIA_ToggleToggleStatePropertyId,
                                  &value);

    qDebug() << "lval =" << value.lVal;
    return "";
//    return QString::fromStdWString(value.bstrVal);
}

void AjUia::setValue(IUIAutomationElement *root, QString path, QString val)
{
    IUIAutomationElement *elem = getElem(root, path);

    if( elem==NULL )
    {
        qDebug() << "Error: cannot set value of uia ("
                 << path << ")";
        return;
    }

    IUIAutomationValuePattern *pattern = NULL;
    HRESULT hr = elem->GetCurrentPattern(UIA_TogglePatternId,
                                         reinterpret_cast<IUnknown **>(&pattern));
    if( hr!=S_OK || pattern==NULL )
    {
        return;
    }
    BSTR value = SysAllocString(val.toStdWString().c_str());
    pattern->SetValue(value);

    return;
//    return QString::fromStdWString(value.bstrVal);
}

IUIAutomationElement* AjUia::getElem(IUIAutomationElement *root, QString path)
{
    IUIAutomationElement *elem = NULL;
    QStringList path_split = path.split('.', QString::SkipEmptyParts);

    elem = getElem(root, path_split);

    return elem;
}

IUIAutomationElement* AjUia::getElem(IUIAutomationElement *elem, QStringList path_list)
{
    if( path_list.size()>0 )
    {
        int index = path_list[0].toInt() - 1;
        IUIAutomationElement* child = getChild(elem, index);

        if( child!=NULL )
        {
            qDebug() << "path =" << path_list;
            return getElem(child, path_list.mid(1));
        }
        else
        {
            return NULL;
        }

    }
    else
    {
        return elem;
    }
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

IUIAutomationElement* AjUia::getChild(IUIAutomationElement *elem, int index)
{
    IUIAutomationTreeWalker* pControlWalker = NULL;
    IUIAutomationElement* node = NULL;
    int i = 0;

    pAutomation->get_ControlViewWalker(&pControlWalker);
    if( pControlWalker==NULL )
        goto cleanup;

    pControlWalker->GetFirstChildElement(elem, &node);
    if( node==NULL )
        goto cleanup;

    for( i=1 ; i<index ; i++ )
    {
        IUIAutomationElement* next;
        pControlWalker->GetNextSiblingElement(node, &next);
        node->Release();
        node = next;

        if( node==NULL )
        {
            qDebug() << "Error 151: Index child surpass child count"
                     << "i =" << i << index;
            break;
        }
    }

    if( i==index )
    {
        pControlWalker->Release();
        return node;
    }

cleanup:
    if( pControlWalker!=NULL )
    {
        pControlWalker->Release();
    }

    if( node!=NULL )
    {
        node->Release();
    }

    return NULL;
}

QString AjUia::find(HWND hwnd, QString path, QString name)
{
    return "";
}

long AjUia::getChildCount(IUIAutomationElement *elem)
{
    long count;
    if( elem==NULL )
    {
        return -1;
    }
//    elem->get_->get_accChildCount(&cc);
    return count;
}

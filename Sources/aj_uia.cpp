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

UiaElement* AjUia::getElem(UiaElement *root, QString path)
{
    UiaElement *elem = NULL;
    QStringList path_split = path.split('.', QString::SkipEmptyParts);

    elem = getElem(root, path_split);

    return elem;
}

UiaElement* AjUia::getElem(UiaElement *elem, QStringList path_list)
{
    if( path_list.size()>0 )
    {
        int index = path_list[0].toInt();
        UiaElement* child = getChild(elem, index);

        if( child!=NULL )
        {
//            qDebug() << "path =" << path_list;
            return getElem(child, path_list.mid(1));
        }
        else
        {
//            qDebug() << "null bud";
            return NULL;
        }
    }
    else
    {
        return elem;
    }
}

QString AjUia::getParent(QString path)
{
    QStringList path_split = path.split(".");
    path_split.removeLast();
    QString path_combine = path_split.join(".");
    return path_combine;
}

void AjUia::list(UiaElement* root)
{
    list(root, "");
}

void AjUia::listChild(UiaElement *parent)
{
    UiaElement* pNode = NULL;
    int child_id = 0;

    pControlWalker->GetFirstChildElement(parent, &pNode);
    if( pNode==NULL )
    {
        return;
    }

    while( pNode )
    {
        child_id += 1;
        BSTR desc, name;
        pNode->get_CurrentLocalizedControlType(&desc);
        pNode->get_CurrentName(&name);

        QString print_desc = QString::number(child_id) + ")";
        print_desc += QString::fromStdWString(desc);
        print_desc += ":";
        if( name!=NULL )
        {
            print_desc += QString::fromStdWString(name);
        }
        qDebug() << print_desc;
        SysFreeString(desc);
        SysFreeString(name);

        UiaElement* pNext;
        pControlWalker->GetNextSiblingElement(pNode, &pNext);
        pNode->Release();
        pNode = pNext;
    }
}

UiaElement* AjUia::getChild(UiaElement *elem, int index)
{
    UiaElement* node = NULL;
    int i = 0;

    pControlWalker->GetFirstChildElement(elem, &node);
    if( node==NULL )
    {
        return NULL;
    }

    for( i=1 ; i<index ; i++ )
    {
        UiaElement* next;
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
        return node;
    }

    return NULL;
}

int AjUia::getChildId(UiaElement *parent, QString name)
{
    UiaElement* pNode = NULL;
    int child_id = 0;

    pControlWalker->GetFirstChildElement(parent, &pNode);
    if( pNode==NULL )
    {
        return -1;
    }

    while( pNode )
    {
        BSTR name_bstr;
        pNode->get_CurrentName(&name_bstr);

        if( name!=NULL )
        {
            if( QString::fromStdWString(name_bstr)==name )
            {
                return child_id;
            }
        }
        SysFreeString(name_bstr);
        UiaElement* pNext;
        pControlWalker->GetNextSiblingElement(pNode, &pNext);
        pNode->Release();
        pNode = pNext;
        child_id += 1;
    }
    return -1;
}

QString AjUia::find(HWND hwnd, QString path, QString name)
{
    UiaElement *root = getElement(hwnd);
    QStringList path_list = path.split(".");
    QString path_c = find(root, path_list, name);
    return path_c;
}

QString AjUia::find(UiaElement *elem, QStringList path_list, QString name)
{
    int search_index = path_list.indexOf("?");
    QStringList fix_part = path_list.mid(0,search_index);
    QStringList var_part = path_list.mid(search_index);
    UiaElement *elem_part1 = getElem(elem, fix_part);
    UiaElement *elem_full = NULL;

    UiaElement* pNode = NULL;
    int child_id = 0;

    pControlWalker->GetFirstChildElement(elem_part1, &pNode);
    if( pNode==NULL )
    {
        return "";
    }

    while( pNode )
    {
        var_part[0] = QString::number(child_id+1);
        if( var_part.contains("?") ) // recursive part
        {
            QString ret = find(elem_part1, var_part, name);
            if( ret.length() )
            {
                pNode->Release();
                return fix_part.join(".") + "." + ret;
            }
            else
            {
                continue;
            }
        }
        elem_full = getElem(elem_part1, var_part);
        if( elem_full )
        {
            BSTR name_bstr, type;
            elem_full->get_CurrentName(&name_bstr);
            elem_full->get_CurrentLocalizedControlType(&type);

//            qDebug() << "finding: " << var_part[0]
//                     << QString::fromStdWString(name_bstr)
//                     << QString::fromStdWString(type);
            if( QString::fromStdWString(name_bstr)==name )
            {
                QStringList total_list = fix_part + var_part;
                SysFreeString(name_bstr);
                pNode->Release();
                return total_list.join(".");
            }
            SysFreeString(name_bstr);
            SysFreeString(type);
        }

        UiaElement* pNext;
        pControlWalker->GetNextSiblingElement(pNode, &pNext);
        pNode->Release();
        pNode = pNext;
        child_id += 1;
    }
    return "";
}

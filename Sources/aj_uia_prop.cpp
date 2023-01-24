#include "aj_uia_prop.h"

AjUiaProp::AjUiaProp(AjUia *u)
{
    uia = u;
}

AjUiaProp::~AjUiaProp()
{
    ;
}

QString AjUiaProp::getValue(HWND hwnd, QString path)
{
    VARIANT value;
    UiaElement* root = uia->getElement(hwnd);
    UiaElement *elem = uia->getElem(root, path);

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

void AjUiaProp::setValue(HWND hwnd, QString path, QString val)
{
    UiaElement* root = uia->getElement(hwnd);
    UiaElement *elem = uia->getElem(root, path);

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
    SysFreeString(value);
//    return QString::fromStdWString(value.bstrVal);
}

QString AjUiaProp::getToggle(HWND hwnd, QString path)
{
    VARIANT value;
    UiaElement* root = uia->getElement(hwnd);
    UiaElement *elem = uia->getElem(root, path);

    if( elem==NULL )
    {
        qDebug() << "Error: cannot get value of uia ("
                 << path << ")";
        return "";
    }

    elem->GetCurrentPropertyValue(UIA_ToggleToggleStatePropertyId,
                                  &value);

    return QString::number(value.lVal);
}

void AjUiaProp::toggle(HWND hwnd, QString path)
{
    UiaElement* root = uia->getElement(hwnd);
    UiaElement *elem = uia->getElem(root, path);

    if( elem==NULL )
    {
        qDebug() << "Error: cannot get value of uia ("
                 << path << ")";
        return;
    }
    IUIAutomationValuePattern *pattern = NULL;
    HRESULT hr = elem->GetCurrentPattern(UIA_TogglePatternId,
                                         reinterpret_cast<IUnknown **>(&pattern));
    if( hr!=S_OK || pattern==NULL )
    {
        qDebug() << "Error: Toggling failed";
        return;
    }
    pattern->SetValue(BSTR());
}

QString AjUiaProp::getName(HWND hwnd, QString path)
{
    UiaElement *root = uia->getElement(hwnd);
    UiaElement *elem = uia->getElem(root, path);

    if( elem==NULL )
    {
        qDebug() << "Error: cannot get value of uia ("
                 << path << ")";
        return "";
    }

    BSTR name;
    elem->get_CurrentName(&name);

    QString ret = aj_toQString(name);
    SysFreeString(name);
    return ret;
}

QString AjUiaProp::getState(HWND hwnd, QString path)
{
    UiaElement *root = uia->getElement(hwnd);
    UiaElement *elem = uia->getElem(root, path);

    if( elem==NULL )
    {
        qDebug() << "Error: cannot get value of uia ("
                 << path << ")";
        return "";
    }

    BSTR state;
    elem->get_CurrentItemStatus(&state);
    QString ret = aj_toQString(state);
    SysFreeString(state);
    return ret;
}

QString AjUiaProp::getType(HWND hwnd, QString path)
{
    UiaElement *root = uia->getElement(hwnd);
    UiaElement *elem = uia->getElem(root, path);

    if( elem==NULL )
    {
        qDebug() << "Error: cannot get value of uia ("
                 << path << ")";
        return "";
    }

    BSTR type;
    elem->get_CurrentLocalizedControlType(&type);
    QString ret = aj_toQString(type);
    SysFreeString(type);
    return ret;
}

QString AjUiaProp::getChildPath(HWND hwnd, QString path, QString name)
{
    UiaElement *root = uia->getElement(hwnd);
    UiaElement *elem = uia->getElem(root, path);
    int child_id = uia->getChildId(elem, name);
    path += "." + QString::number(child_id+1);
    return path;
}

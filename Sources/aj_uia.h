#ifndef AJ_UIA_H
#define AJ_UIA_H

#include <QString>
#include <QtDebug>

#include <oleacc.h>
#include <winbase.h>
#include <windows.h>
#include <psapi.h> // For access to GetModuleFileNameEx
#include <tlhelp32.h> // to get application pid
#include <UIAutomation.h>
#include <uiautomationclient.h>

#include "backend.h"
#include "uia_element.h"
#include "uia_tree_walker.h"
#include "aj_application.h"
#include "uia_pattern.h"

typedef IUIAutomationElement UiaElement;

void        aj_uiaList(HWND hwnd);
UiaElement* aj_getUiaHWND(HWND hwnd);

class AjUia
{
public:
    explicit AjUia(AjApplication *a);
    ~AjUia();

    UiaElement* getElement(HWND hwnd);
    void list(UiaElement *root, QString path);
    void ListWindow(HWND hwnd);

    void list(UiaElement *root);
    void listChild(UiaElement *parent);
    IAccessible* getWinP(HWND window);
    QString getChildPath(HWND hwnd, QString path, QString name);
    QString find(HWND hwnd, QString path, QString name);
    QString find(UiaElement *elem, QStringList path_list, QString name);
    QString getParent(QString path);

    UiaElement* getElem(UiaElement *root, QString path);
    UiaElement* getElem(UiaElement *elem, QStringList path_list);
    UiaElement* getChild(UiaElement *elem, int index);
    int getChildId(UiaElement *parent, QString name);

private:
    IUIAutomation *pAutomation;
    IUIAutomationTreeWalker* pControlWalker;
    AjApplication *app;
};

#endif // AJ_UIA_H

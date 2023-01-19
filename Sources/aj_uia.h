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

void    aj_uiaList(HWND hwnd);
IUIAutomationElement* aj_getUiaHWND(HWND hwnd);

class AjUia
{
public:
    explicit AjUia(AjApplication *a);
    ~AjUia();

    IUIAutomationElement* getElement(HWND hwnd);
    void list(IUIAutomationElement *parent, QString path);
    void ListWindow(HWND hwnd);

    QString getValue(IUIAutomationElement *root, QString path);
    void setValue(IUIAutomationElement *root, QString path, QString val);
    void list(IUIAutomationElement *elem);
    void list2(IUIAutomationElement *elem);
    IAccessible* getWinP(HWND window);
    QString getName(HWND hwnd, QString path);
    QString getState(HWND hwnd, QString path);
    QString getType(HWND hwnd, QString path);
    QString getParent(QString path);
    QString getChild(HWND hwnd, QString path, QString name);
    QString find(HWND hwnd, QString path, QString name);

    IUIAutomationElement* getElem(IUIAutomationElement *root, QString path);
    IUIAutomationElement* getElem(IUIAutomationElement *elem, QStringList path_list);
    IUIAutomationElement* getChild(IUIAutomationElement *elem, int index);
    long                  getChildCount(IUIAutomationElement *pAcc);

private:
    IUIAutomation *pAutomation;
    AjApplication *app;
};

#endif // AJ_UIA_H

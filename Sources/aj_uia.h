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
    void list(IUIAutomationElement *parent, int indent);
    void ListWindow(HWND hwnd);

    QString getValue(HWND hwnd, QString path);
    void setValue(HWND hwnd, QString path, QString val);
    IAccessible* getHWND(HWND hwnd, QString path);
    void list(IAccessible *pAcc, QString path);
    void list2(IAccessible *pAcc);
    IAccessible* getWinP(HWND window);
    QString getName(HWND hwnd, QString path);
    QString getState(HWND hwnd, QString path);
    QString getType(HWND hwnd, QString path);
    QString getParent(QString path);
    QString getChild(HWND hwnd, QString path, QString name);
    QString find(HWND hwnd, QString path, QString name);

private:
    IUIAutomation *pAutomation;
    AjApplication *app;
};

#endif // AJ_UIA_H

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

void    aj_uiaList(HWND hwnd);
IUIAutomationElement* aj_getUiaHWND(HWND hwnd);

class AjUia: public QObject
{
    Q_OBJECT
public:
    explicit AjUia(QObject *parent = nullptr);
    ~AjUia();

    IUIAutomationElement* getElement(HWND hwnd);
    void list(IAccessible *pAcc, QString path);

private:
    IUIAutomation *pAutomation;
};

#endif // AJ_UIA_H

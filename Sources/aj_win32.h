#ifndef AJWIN32_H
#define AJWIN32_H

#include <QString>
#include <QtDebug>
#include <QVector>
#include <QThread>

#include <dwmapi.h>
#include "Windows.h"
#include <tlhelp32.h> // to get pid
#include <tchar.h> // to get file path
#include <psapi.h> // For access to GetModuleFileNameEx

typedef struct AjApplication
{
    QString shortcut_name;
    QString exe_name;
    QString exe_path;
    QString win_title;
    DWORD pid = 0;
    QString pname;
    int workspace;
    HWND hwnd;
}AjApplication;

long aj_getPid(HWND hWnd);
QString aj_getPName(long pid);
QString aj_getPPath(long pid);
QString aj_getWinTitle(HWND hwnd);
void aj_setActiveWindow(HWND hWnd);
HWND aj_getHWND(AjApplication *app);
void aj_findAppByName(QString exe_name, AjApplication *app);
void aj_findWindowByPid(DWORD pid, AjApplication *app);
void aj_setMouse(int x, int y);
void aj_setFocus(AjApplication *app);
HWND aj_getFocusedHWND(AjApplication *app);

#endif // AJWIN_H

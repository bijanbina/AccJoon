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

typedef struct AjWindow
{
    int  verify; //verify hwnd still exist
    int  type;
    long pid;
    QString title;
    QString pname;
    HWND hWnd = NULL;
}AjWindow;

typedef struct AjListW
{
    QVector<AjWindow> windows;
    AjWindow win_active;
}AjThreadW;

void aj_AddHwnd(HWND hwnd, AjListW *thread_w);
long aj_getPid(HWND hWnd);
QString aj_getPName(long pid);
QString aj_getPPath(long pid);
void aj_InsertWindow(AjListW *thread_w, AjWindow win);
void aj_getType(AjWindow *win);
void aj_setActiveWindow(HWND hWnd);
HWND aj_getHWND(QString exe_name);
bool aj_fillWinSpec(HWND hwnd, QString title, AjWindow *win);
void aj_findAppByName(QString exe_name, AjWindow *window);
void aj_findWindowByPid(DWORD pid, AjWindow *window);
void aj_setMouse(int x, int y);

#endif // AJWIN_H

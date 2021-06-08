#ifndef AJWIN32_H
#define AJWIN32_H

#include <QString>
#include <QtDebug>
#include <QVector>

#include <dwmapi.h>
#include "Windows.h"
#include <tlhelp32.h> // to get pid
#include <tchar.h> // to get file path
#include <psapi.h> // For access to GetModuleFileNameEx

#define RE_WIN_UNKNOWN     1
#define RE_WIN_SPOTIFY     2
#define RE_WIN_FIREFOX     3
#define RE_WIN_EXPLORER    4
#define RE_WIN_READING     5
#define RE_WIN_QT          6
#define RE_WIN_TEXTEDITOR  7
#define RE_WIN_OVERVIEW    8
#define RE_WIN_TELEGRAM    9
#define RE_WIN_TERMINAL    10
#define RE_WIN_YOUTUBE     11

typedef struct AjWindow
{
    int  verify; //verify hwnd still exist
    int  type;
    QString title;
    QString pname;
    HWND hWnd;
}AjWindow;

typedef struct AjListW
{
    QVector<AjWindow> windows;
    AjWindow win_active;
}AjThreadW;

void aj_AddHwnd(HWND hwnd, AjListW *thread_w);
long ajGetPid(HWND hWnd);
QString ajGetPName(long pid);
void aj_InsertWindow(AjListW *thread_w, AjWindow win);
void aj_getType(AjWindow *win);
void aj_setActiveWindow(HWND hWnd);
void aj_setActiveWindow(QString win_name);

#endif // AJWIN_H

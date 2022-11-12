#ifndef AJ_SHORTCUT_H
#define AJ_SHORTCUT_H

#include <windows.h>
#include <QDir>
#include <QDebug>

#include "aj_win.h"


typedef struct AjApplication
{
    QString shortcut_name;
    QString exe_name;
    QString exe_path;
    QString win_title;
    DWORD pid = 0;
    int workspace;
    HWND hwnd;
}AjApplication;


QString getLinkLongPath(QString shortcut_name);
void launchApp(AjApplication *app, QString arg="");
AjApplication getApplication(QString shortcut_name);


QString getLinkPath(QString name);
QString getLinkPathA(QString name);
QString getLinkPathB(QString name);
QString findAppPath(QString path, QString pattern);
HRESULT resolveIt(LPCSTR lnk_path, char *target);


#endif // AJ_SHORTCUT_H

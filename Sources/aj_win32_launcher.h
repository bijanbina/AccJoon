#ifndef AJWIN32LAUNCHER_H
#define AJWIN32LAUNCHER_H

#include <Windows.h>
#include <QDir>
#include <QDebug>

class AjWin32Launcher
{
public:
    AjWin32Launcher(QString app_name);
    DWORD launchApp(QString arg="");
    QString getExeName();

    QString link_path;

private:
    QString getLinkPath(QString name);
    QString getLinkPathA(QString name);
    QString getLinkPathB(QString name);
    QString findAppPath(QString path, QString pattern);
    HRESULT resolveIt(LPCSTR lnk_path, char *target);
};

#endif // AJWIN32LAUNCHER_H

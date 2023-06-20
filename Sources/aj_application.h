#ifndef AJ_APPLICATION_H
#define AJ_APPLICATION_H

#include <windows.h>
#include <QDir>
#include <QDebug>

#include "aj_var.h"

QString getLinkLongPath(QString shortcut_name);
void launchApp(AjApplication *app, QString arg="");
AjApplication getApplication(QString shortcut_name,
                             QString win_title="");

QString getLinkPath(QString name);
QString getLinkPathA(QString name);
QString getLinkPathB(QString name);
QString findAppPath(QString path, QString pattern);
HRESULT resolveIt(LPCSTR lnk_path, char *target);

#endif // AJ_APPLICATION_H

#ifndef AJWIN_H
#define AJWIN_H

#include <QString>
#include <QtDebug>

#include <oleacc.h>
#include <winbase.h>
#include <windows.h>
#include <psapi.h> // For access to GetModuleFileNameEx
#include <tlhelp32.h> // to get application pid
#include <tchar.h> // to get application file path

#include "backend.h"
#include "aj_conf_parser.h"
#include "aj_acc.h"

#define AJ_MOUSE_DELAY   20
#define AJ_DOUBLE_DELAY  3

class AjWin
{
public:
    AjWin(AjAccOptions acc_conf);
    int doAction(QString cmd);

private:
    void listChildren(IAccessible *pAcc, QString path);
    IAccessible *getActiveAcc();
    int setObjLocation(IAccessible *acc, int childID);
    void doClick(int cmd);

    QString window_title;
    QString acc_name;
    QStringList path;
    POINT obj_center;

    int offset_x;
    int offset_y;
    int offset_id;
    POINT cursor_last;
};

#endif // AJWIN_H

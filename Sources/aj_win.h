#ifndef AJWIN_H
#define AJWIN_H

#include <QString>
#include <QtDebug>
#include <QThread>

#include <oleacc.h>
#include <winbase.h>
#include <windows.h>
#include <psapi.h> // For access to GetModuleFileNameEx
#include <tlhelp32.h> // to get application pid
#include <tchar.h> // to get application file path

#include "backend.h"
#include "aj_win32.h"
#include "aj_acc.h"
#include "aj_lua.h"

#define AJ_MOUSE_DELAY   20
#define AJ_DOUBLE_DELAY  3

typedef struct AjCommand
{
    QList<AjLuaInfo> scripts;
    int delay;
    // key section
    int key;
    int alt_key;
    int ctrl_key;
    int shift_key;
    int meta_key;
    // acc section
    QString acc_path;
    QString action;
    QString acc_name;
    int offset_x;
    int offset_y;
    int offset_id;
}AjCommand;

typedef struct AjAppOptions{
    QString app_name;
    QString app_func;
    QString pcheck; // process check
    QString args;
    int workspace;
    int is_open;
    int start_delay;
    int open_delay;
    QList<AjLuaInfo> start_scripts;
    QList<AjLuaInfo> open_scripts;
    QVector<AjCommand> commands;
}AjAppOptions;

class AjWin
{
public:
    AjWin(HWND hWindow=NULL);
    int doAction(AjCommand acc_conf);

private:
    void listChildren(IAccessible *pAcc, QString path);
    IAccessible *getParnetAcc(HWND hWindow);
    int  setObjLocation(IAccessible *acc, int childID);
    void doClick(POINT obj_center, int cmd);
    int  doAcc(AjCommand cmd);
    int  doKey(AjCommand cmd);

    QString window_title;
    QStringList path;
    HWND hwnd;

    int offset_x;
    int offset_y;
    int offset_id;
    POINT cursor_last;
};

#endif // AJWIN_H

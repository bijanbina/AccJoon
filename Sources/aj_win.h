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

#define AJ_CMD_DELAY    1
#define AJ_CMD_SCRIPT   2
#define AJ_CMD_KEY      3
#define AJ_CMD_ACC      4
#define AJ_CMD_APP      5
#define AJ_CMD_OPEN     6

typedef struct AjCommand
{
    int type;
    int delay;
    // lua section
    QString path;
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
    int open_delay;
    QVector<AjCommand> commands;
}AjAppOptions;

class AjWin
{
public:
    AjWin(HWND hWindow=NULL);
    int  doAcc(AjCommand cmd);
    int  doKey(AjCommand cmd);

private:
    void listChildren(IAccessible *pAcc, QString path);
    IAccessible *getParnetAcc(HWND hWindow);
    int  setObjLocation(IAccessible *acc, int childID);
    void doClick(POINT obj_center, int cmd);

    QString window_title;
    QStringList path;
    HWND hwnd;

    int offset_x;
    int offset_y;
    int offset_id;
    POINT cursor_last;
};

#endif // AJWIN_H

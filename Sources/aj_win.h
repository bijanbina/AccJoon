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

#define AJ_MOUSE_DELAY   20
#define AJ_DOUBLE_DELAY  3

typedef struct AjCommand
{
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
    int workspace;
    int is_open;
    int open_delay;
    int start_delay;
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
    int setObjLocation(IAccessible *acc, int childID);
    void doClick(int cmd);
    int doAcc(AjCommand cmd);
    int doKey(AjCommand cmd);

    QString window_title;
    QStringList path;
    POINT obj_center;
    HWND hwnd;

    int offset_x;
    int offset_y;
    int offset_id;
    POINT cursor_last;
};

#endif // AJWIN_H

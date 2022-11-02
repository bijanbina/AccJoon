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

#define AJ_CMD_EOF      0 // end of file
#define AJ_CMD_DELAY    1
#define AJ_CMD_SCRIPT   2
#define AJ_CMD_KEY      3
#define AJ_CMD_ACC      4
#define AJ_CMD_WRITE    5 // Write Value to Acc
#define AJ_CMD_READ     6 // Read Value of Acc
#define AJ_CMD_APP      7
#define AJ_CMD_OPEN     8
#define AJ_CMD_END      9

class AjVar
{
public:
    void addVar(QString name, QString value);
    QString getVal(QString name);
private:
    QStringList vars_name;
    QStringList vars_value;
};

typedef struct AjAcc
{
    QString acc_path;
    QString action;
    QString acc_name;
    QString value;
    QString value_name;
    int offset_x;
    int offset_y;
    int offset_id;
}AjAcc;

typedef struct AjApp
{
    QString app_name;
    QString app_func;
    QString pcheck; // process check
    QString args;
    int workspace;
    int is_open;
    int open_delay;
}AjApp;

typedef struct AjCommand
{
    QString command;
    QString output;
    QStringList args;
}AjCommand;

class AjWin
{
public:
    AjWin(HWND hWindow=NULL);
    int  doAcc(AjCommand cmd);
    int  doKey(AjCommand cmd);
    QString readAcc(AjCommand cmd);
    int writeAcc(AjCommand cmd);

private:
    void listChildren(IAccessible *pAcc, QString path);
    IAccessible *getParnetAcc(HWND hWindow);
    int  setObjLocation(IAccessible *acc, int childID);
    void doClick(POINT obj_center, int cmd);

    QString window_title;
    HWND hwnd;

    int offset_x;
    int offset_y;
    int offset_id;
    POINT cursor_last;
};

QString aj_toQString(BSTR input);
BSTR aj_toBSTR(QString input);

#endif // AJWIN_H

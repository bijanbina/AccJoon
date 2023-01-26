#ifndef AJ_ACC_H
#define AJ_ACC_H

#include <QString>
#include <QtDebug>

#include <oleacc.h>
#include <winbase.h>
#include <windows.h>
#include <psapi.h> // For access to GetModuleFileNameEx
#include <tlhelp32.h> // to get application pid
#include <tchar.h> // to get application file path

#include "backend.h"

typedef struct AjAccCmd
{
    QString acc_path;
    QString action = "L";
    QString acc_name;
    QString value;
    QString value_name;
    int offset_x = 0;
    int offset_y = 0;
    int offset_id = 0;
}AjAccCmd;

void    aj_accList(IAccessible *pAcc, QString path);
void    aj_accListChild(IAccessible *pAcc);
QString aj_accGetName(IAccessible *acc, long childId);
QString aj_getAccNameI4(IAccessible *acc, long childId);
QString aj_getAccParent(QString path);

long aj_getChildCount(IAccessible *pAcc);
IAccessible* aj_accGetChild(IAccessible *acc, int index);

IAccessible* aj_getWinPAcc(HWND window);
IAccessible* aj_getAcc(QStringList varpath, IAccessible *pAcc);
IAccessible* aj_getAccHWND(HWND hwnd, QString path);
VARIANT aj_getVarChild(QString path);
int aj_getChildId(QString name, IAccessible *acc);
QString aj_findAcc(HWND hwnd, QString path, QString name);
QString aj_findAcc(IAccessible *acc, QStringList path_list, QString name);

void aj_execAcc(AjAccCmd cmd);

#endif // AJ_ACC_H

#ifndef AJACC_H
#define AJACC_H

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

QString aj_getAccNameI4(IAccessible *acc, long childId);
QString aj_getAccName(IAccessible *acc, long childId);
POINT   getAccLocationI4(IAccessible *acc, int childID);
POINT   getAccLocation(IAccessible *acc, int childID);
POINT   getAccLocation(AjAccCmd cmd, HWND hwnd, QString path);
QString getAccValue(HWND hwnd, QString path);
QString getAccState(HWND hwnd, QString path);
void    setAccValue(HWND hwnd, QString path, QString val);
void    aj_accList(IAccessible *pAcc, QString path);

long aj_getChildCount(IAccessible *pAcc);
IAccessible* aj_getChild(IAccessible *acc, int index);

IAccessible* aj_getWinPAcc(HWND window);
IAccessible* aj_getAcc(QStringList varpath, IAccessible *pAcc);
IAccessible* aj_getAcc(HWND hwnd, QString path);
VARIANT aj_getVarChild(QString path);
int aj_getChildId(QString name, IAccessible *acc);

QString aj_getStateName(long val);
QString aj_toQString(BSTR input);
BSTR aj_toBSTR(QString input);

void aj_execAcc(AjAccCmd cmd);
#endif // AJACC_H

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

QString aj_getAccNameI4(IAccessible *acc, long childId);
QString aj_getAccName(IAccessible *acc, long childId);
long aj_getChildCount(IAccessible *pAcc);
IAccessible* aj_getChild(IAccessible *acc, int index);

IAccessible* aj_getWinPAcc(HWND window);
IAccessible* aj_getAcc(QStringList varpath, IAccessible *pAcc);
int aj_getChildId(QString name, IAccessible *pAcc);

#endif // AJACC_H

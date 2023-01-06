#ifndef AJ_ACC_PROP_H
#define AJ_ACC_PROP_H

#include "aj_acc.h"

POINT   aj_accGetLocationI4(IAccessible *acc, int childID);
POINT   aj_accGetLocation(IAccessible *acc, int childID);
POINT   aj_accGetLocation(AjAccCmd cmd, HWND hwnd, QString path);
QString aj_accGetValue(HWND hwnd, QString path);
QString aj_accGetState(HWND hwnd, QString path);
QString aj_accGetType(HWND hwnd, QString path);
QString aj_accGetName(HWND hwnd, QString path);
QString aj_accGetStateName(long val);
void    aj_accSetValue(HWND hwnd, QString path, QString val);
QString aj_accGetChild(HWND hwnd, QString path, QString name);

#endif // AJ_ACC_PROP_H

#ifndef AJ_ACC_PROP_H
#define AJ_ACC_PROP_H

#include "aj_acc.h"

POINT   aj_getAccLocationI4(IAccessible *acc, int childID);
POINT   aj_getAccLocation(IAccessible *acc, int childID);
POINT   aj_getAccLocation(AjAccCmd cmd, HWND hwnd, QString path);
QString aj_getAccValue(HWND hwnd, QString path);
QString aj_getAccState(HWND hwnd, QString path);
QString aj_getAccType(HWND hwnd, QString path);
QString aj_getAccName(HWND hwnd, QString path);
QString aj_getStateName(long val);
void    aj_setAccValue(HWND hwnd, QString path, QString val);

#endif // AJ_ACC_PROP_H

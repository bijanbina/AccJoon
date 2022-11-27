#ifndef AJ_MOUSE_H
#define AJ_MOUSE_H

#include <stdio.h>
#include <Windows.h>
#include <QVector>
#include "backend.h"
#include "aj_acc_prop.h"

#define AJ_MOUSE_DELAY   20
#define AJ_DOUBLE_DELAY  3

void aj_mouseClick(POINT obj_center, AjAccCmd cmd);

#endif // AJ_MOUSE_H

#ifndef AJ_EXECUTER_H
#define AJ_EXECUTER_H

#include "aj_win.h"

void aj_execute(QVector<AjAppOptions> apps);
HWND aj_executeApp(AjAppOptions);
void aj_executeCmds(AjAppOptions app, HWND hwnd);

#endif // AJ_EXECUTER_H

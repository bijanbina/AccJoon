#ifndef AJ_EXECUTER_H
#define AJ_EXECUTER_H

#include "aj_win.h"
#include "aj_parser.h"

void aj_execute(QString conf_path);
HWND aj_executeApp(AjAppOptions);
void aj_executeCmds(AjAppOptions app, HWND hwnd);
void aj_addVar(QString name, QString value);
AjVar aj_findVar(QString name);

QVector<AjVar> script_vars;

#endif // AJ_EXECUTER_H

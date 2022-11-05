#ifndef AJ_EXECUTER_H
#define AJ_EXECUTER_H

#include "aj_win.h"
#include "aj_parser.h"

typedef struct AjApplication
{
    QString app_name;
    QString exe_name;
    DWORD pid;
    AjWindow *req_win;
    AjLauncher *win_launcher;
    HWND hwnd;
}AjApplication;

void aj_execute(QString conf_path);
void aj_executeLine(AjParser *parser, AjApplication *app);
void aj_executeOpen(AjApplication *app, AjCommand *cmd);
void aj_clearApp(AjApplication *app);
HWND aj_getHwnd(AjApplication *app);

#endif // AJ_EXECUTER_H

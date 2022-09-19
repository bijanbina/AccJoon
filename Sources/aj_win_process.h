#ifndef AJ_WIN_PROCESS_H
#define AJ_WIN_PROCESS_H

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <QString>

int aj_isProcOpen(QString name);

#endif // AJ_WIN_PROCESS_H

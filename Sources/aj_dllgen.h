#ifndef AJDLLGEN_H
#define AJDLLGEN_H

#include <QFile>
#include "aj_win32_launcher.h"

void aj_dllGen();
void aj_fillBatFile(QFile *bat_file);
QString aj_getQtCompiler();
QString aj_getQtPath();
QString aj_getQtShortCut();
QString aj_getQtCreator();
QString aj_findCompiler(QString pattern, QString dirname);
QString aj_findQtShortcut(QString dirname);
QString aj_getFirstDir(QString path);
QString aj_makeToolsPath();

#endif // AJDLLGEN_H

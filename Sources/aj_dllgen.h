#ifndef AJDLLGEN_H
#define AJDLLGEN_H

#include <QFile>
#include <QDir>
#include "aj_application.h"

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
QStringList aj_listGccCompilers(QString tools_path);
QStringList aj_getConfList();
QFileInfoList aj_searchDir(QString path, QString pattern,
                           QDir::Filters filter);

#endif // AJDLLGEN_H

#ifndef AJDLLGEN_H
#define AJDLLGEN_H

#include <QFile>
#include "aj_win32_launcher.h"

class AjDllGen
{
public:
    AjDllGen(QString dll_path);

private:
    void fillBatFile();
    QString getQtCompiler();
    QString getQtPath();
    QString getQtCreator();
    QString findCompiler(QString pattern, QString dirname);
    QString findQtShortcut(QString dirname);
    QString getFirstDir(QString path);
    QString makeToolsPath();
    void addToolsLib(QString lib);

    QFile *bat_file;
    QString creator_path;
    QString project_path;
    QString tools_path;
};

#endif // AJDLLGEN_H

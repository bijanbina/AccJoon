#ifndef AJDLLGEN_H
#define AJDLLGEN_H

#include <QFile>
#include "aj_win32_launcher.h"
#define SHORTCUT_QT "Qt Creator\\Qt Creator 4.15.1 (Community)"

class AjDllGen
{
public:
    AjDllGen(QString dll_path);

private:
    QString getQtCompiler();
    QString getQtPath();
    QString findDir(QString pattern, QString dirname);
    void fillBatFile();

    QFile *bat_file;
};

#endif // AJDLLGEN_H

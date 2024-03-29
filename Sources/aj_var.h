#ifndef AJ_VAR_H
#define AJ_VAR_H

#include <QString>
#include <QtDebug>
#include <QThread>

#include <oleacc.h>
#include <winbase.h>
#include <windows.h>
#include <psapi.h> // For access to GetModuleFileNameEx
#include <tlhelp32.h> // to get application pid
#include <tchar.h> // to get application file path

#include "backend.h"
#include "aj_win32.h"
#include "aj_acc_prop.h"
#include "aj_lua.h"
#include "aj_mouse.h"
#include "aj_application.h"

#define AJ_CMD_EOF      0 // end of file
#define AJ_CMD_DELAY    1
#define AJ_CMD_SCRIPT   2
#define AJ_CMD_KEY      3
#define AJ_CMD_ACC      4
#define AJ_CMD_WRITE    5 // Write Value to Acc
#define AJ_CMD_READ     6 // Read Value of Acc
#define AJ_CMD_APP      7
#define AJ_CMD_OPEN     8
#define AJ_CMD_END      9

class AjVar
{
public:
    void setVar(QString name, QString value);
    QString getVal(QString name);
    void setArg(int id, QString val);
    void printVars();
    QString getArg(int id);


private:
    QVector<QString> args;
    QStringList vars_name;
    QStringList vars_value;
};

typedef struct AjCommand
{
    QString command;
    QString output;
    QStringList args;
    int flag_append;
}AjCommand;


#endif // AJ_VAR_H

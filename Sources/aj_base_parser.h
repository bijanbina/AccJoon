#ifndef AJ_BASE_PARSER_H
#define AJ_BASE_PARSER_H

#include <QDebug>
#include "aj_var.h"

#define AJ_APP_CMD      "app"
#define AJ_ISOPEN_CMD   "isOpen"
#define AJ_OPEN_CMD     "open"
#define AJ_SLEEP_CMD    "sleep"
#define AJ_CLICK_CMD    "click"
#define AJ_KEY_CMD      "key"
#define AJ_PRINT_CMD    "print"
#define AJ_LUA_CMD      "lua"
#define AJ_RET_CMD      "return"
#define AJ_W8OPEN_CMD   "waitOpen"

// conditional options structure
typedef struct AjCondOpt
{
    int if_start;
    int if_end;
    int else_start;
    int else_end;
    QVector<int> elif_start;
    QVector<int> elif_end;
    QString if_cond;
    QStringList elif_cond;
}AjCondOpt;

typedef struct AjLine
{
    AjCondOpt *cond;
    QString line;
}AjLine;

// app options structure
typedef struct AjApp
{
    int start_line;
    int end_line;
    QString app_name;
    QString win_title;
    QVector<AjLine *> lines;
}AjApp;

QStringList aj_getArguments(QString line);
QString aj_getArgument(QString line, int arg_index);
QStringList aj_getCondition(QString line, AjCommand *cmd);
QString aj_getCommand(QString line);
int aj_isFunction(QString line);
int aj_isConditional(QString line);
int aj_isKeyword(QString line);
int aj_findEnd(int line_number);
void aj_openScript(QString sc_path);
int aj_getScLineSize();
QString aj_getScLine(int index);
QString aj_getInPar(QString line);
void aj_parseKeyword( QString line, AjCommand *cmd);

#endif // AJ_BASE_PARSER_H

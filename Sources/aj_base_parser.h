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

QStringList aj_getArguments(QString line);
QString aj_getArgument(QString line, int arg_index);
QStringList aj_getCondition(QString line, AjCommand *cmd);
QString aj_getCommand(QString line);
bool aj_isFunction(QString line);
bool aj_isConditional(QString line);
int aj_findEnd(int line_number);
void aj_openScript(QString sc_path);
int aj_getScLineSize();
QString aj_getScLine(int index);
QString aj_getInPar(QString line);

#endif // AJ_BASE_PARSER_H

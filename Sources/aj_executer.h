#ifndef AJ_EXECUTER_H
#define AJ_EXECUTER_H

#include "aj_keyboard.h"
#include "aj_parser.h"
#include "aj_virt.h"

#define AJ_CHECK_FAILED  1
#define AJ_CHECK_SUCCESS 2


class AjExecuter
{
public:
    AjExecuter(QString script_path);

    int inside_false_if;

private:
    void exec(AjCommand *cmd);
    void execNormal(AjCommand *cmd);

    int  execOpen (AjCommand *cmd);
    int  execClick(AjCommand *cmd);
    int  execKey  (AjCommand *cmd);
    void execSetVal(AjCommand *cmd);
    void execLua(AjCommand *cmd);
    void execSleep(AjCommand *cmd);
    QString execGetVal(AjCommand *cmd);
    QString execState(AjCommand *cmd);
    QString execGetType(AjCommand *cmd);

    void setFocus();

    QString  conf_path;
    AjParser parser; // value stored in parser
    AjVirt   vi;
    AjApplication app;
};


#endif // AJ_EXECUTER_H

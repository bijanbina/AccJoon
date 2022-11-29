#ifndef AJ_EXECUTER_H
#define AJ_EXECUTER_H

#include "aj_keyboard.h"
#include "aj_parser.h"
#include "aj_virt.h"

#define AJ_CHECK_FAILED  1
#define AJ_CHECK_SUCCESS 2

#define AJ_RUN_NEXT_BLOCK  0
#define AJ_TRUE_COND       1
#define AJ_PENDING_ELSE    2
#define AJ_NORMAL          3

class AjExecuter
{
public:
    AjExecuter(QString script_path);

    int condition_flag;

private:
    void exec(AjCommand *cmd);
    void execNormal(AjCommand *cmd);
    void execAcc(AjCommand *cmd);

    int  execOpen (AjCommand *cmd);
    int  execClick(AjCommand *cmd);
    int  execKey  (AjCommand *cmd);
    void execSetVal(AjCommand *cmd);
    void execLua(AjCommand *cmd);
    void execSleep(AjCommand *cmd);
    void execAccList(AjCommand *cmd);
    void execAccSearch(AjCommand *cmd);
    void execGetVal(AjCommand *cmd);
    void execState(AjCommand *cmd);
    void execGetType(AjCommand *cmd);
    void execGetName(AjCommand *cmd);
    void execGetParent(AjCommand *cmd);
    void execGetChild(AjCommand *cmd);
    void execAssign(AjCommand *cmd, QString val);

    void setFocus();
    void printCondFlag();

    QString  conf_path;
    AjParser parser; // value stored in parser
    AjVirt   vi;
    AjApplication app;
};


#endif // AJ_EXECUTER_H

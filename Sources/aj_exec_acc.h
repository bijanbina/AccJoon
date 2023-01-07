#ifndef AJ_EXEC_ACC_H
#define AJ_EXEC_ACC_H

#include "aj_keyboard.h"
#include "aj_parser.h"

class AjExecAcc
{
public:
    AjExecAcc(AjParser *p, AjApplication *a);

    void exec(AjCommand *cmd);

private:
    void execSetVal(AjCommand *cmd);
    void execList(AjCommand *cmd);
    void execSearch(AjCommand *cmd);
    void execGetVal(AjCommand *cmd);
    void execState(AjCommand *cmd);
    void execGetType(AjCommand *cmd);
    void execGetName(AjCommand *cmd);
    void execGetParent(AjCommand *cmd);
    void execGetChild(AjCommand *cmd);
    void execAssign(AjCommand *cmd, QString val);

    AjApplication *app;
    AjParser *parser; // value stored in parser
};


#endif // AJ_EXEC_ACC_H

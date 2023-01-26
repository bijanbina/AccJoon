#ifndef AJ_EXEC_UIA_H
#define AJ_EXEC_UIA_H

#include "aj_keyboard.h"
#include "aj_parser.h"
#include "aj_uia_prop.h"

class AjExecUia
{
public:
    AjExecUia(AjParser *p, AjApplication *a);

    void exec(AjCommand *cmd);

private:
    void execSetVal(AjCommand *cmd);
    void execList(AjCommand *cmd);
    void execListChild(AjCommand *cmd);
    void execSearch(AjCommand *cmd);
    void execGetVal(AjCommand *cmd);
    void execState(AjCommand *cmd);
    void execGetType(AjCommand *cmd);
    void execGetName(AjCommand *cmd);
    void execGetParent(AjCommand *cmd);
    void execGetChild(AjCommand *cmd);
    void execAssign(AjCommand *cmd, QString val);
    void executeToggle(AjCommand *cmd);
    void executeGetToggle(AjCommand *cmd);

    AjApplication *app;
    AjParser      *parser; // value stored in parser
    AjUiaProp     *uia_prop;
    AjUia         *uia;
};

#endif // AJ_EXEC_UIA_H

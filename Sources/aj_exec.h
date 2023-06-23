#ifndef AJ_EXEC_H
#define AJ_EXEC_H

#include "aj_keyboard.h"
#include "aj_parser.h"
#include "aj_virt.h"
#include "aj_exec_acc.h"
#include "aj_uia.h"
#include "aj_exec_uia.h"
#include "aj_tree_parser.h"

#define AJ_CHECK_FAILED  1
#define AJ_CHECK_SUCCESS 2

#define AJ_RUN_NEXT_BLOCK  0
#define AJ_TRUE_COND       1
#define AJ_PENDING_ELSE    2
#define AJ_NORMAL          3

class AjExec
{
public:
    AjExec(QString script_path);

    int condition_flag;

private:
    void execApps();
    void execApp(AjAppOpt *app);
    void exec(AjCommand *cmd);
    void execNormal(AjCommand *cmd);

    int  execOpen (AjCommand *cmd);
    int  execIsOpen(AjCommand *cmd);
    int  execClick(AjCommand *cmd);
    int  execKey  (AjCommand *cmd);
    void execLua(AjCommand *cmd);
    void execSleep(AjCommand *cmd);
    void execAssign(AjCommand *cmd, QString val);

    void setFocus();
    void printCondFlag();

    QVector<AjAppOpt *> apps;
    QString  conf_path;
    AjParser parser; // value stored in parser
    AjTreeParser *tree_parser;
    AjVirt   vi;
    AjApplication  app;
    AjExecAcc     *acc;
    AjExecUia     *uia;
};


#endif // AJ_EXEC_H

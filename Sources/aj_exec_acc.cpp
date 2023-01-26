#include "aj_exec_acc.h"
#include "aj_win_process.h"
#include "aj_application.h"

AjExecAcc::AjExecAcc(AjParser *p, AjApplication *a)
{
    parser = p;
    app = a;
}

void AjExecAcc::exec(AjCommand *cmd)
{
    if( cmd->command=="acc_getVal" )
    {
        execGetVal(cmd);
    }
    else if( cmd->command=="acc_setVal" )
    {
        execSetVal(cmd);
    }
    else if( cmd->command=="acc_list" )
    {
        execList(cmd);
    }
    else if( cmd->command=="acc_listChild" )
    {
        execList(cmd);
    }
    else if( cmd->command=="acc_getName" )
    {
        execGetName(cmd);
    }
    else if( cmd->command=="acc_getState" )
    {
        execState(cmd);
    }
    else if( cmd->command=="acc_getType" )
    {
        execGetType(cmd);
    }
    else if( cmd->command=="acc_getParent" )
    {
        execGetParent(cmd);
    }
    else if( cmd->command=="acc_getChild" )
    {
        execGetChild(cmd);
    }
    else if( cmd->command=="acc_search" )
    {
        execSearch(cmd);
    }
}

void AjExecAcc::execGetVal(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_accGetValue(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecAcc::execSetVal(AjCommand *cmd)
{
    QString path = cmd->args[0];
    aj_accSetValue(app->hwnd, path, cmd->args.last());
}

void AjExecAcc::execList(AjCommand *cmd)
{
    if( cmd->args.size() )
    {
        IAccessible* acc = aj_getAccHWND(app->hwnd, cmd->args[0]);
        if( cmd->command=="acc_listChild" )
        {
            aj_accListChild(acc);
        }
        else
        {
            aj_accList(acc, cmd->args[0]);
        }
    }
    else
    {
        IAccessible* acc = aj_getWinPAcc(app->hwnd);
        if( cmd->command=="acc_listChild" )
        {
            aj_accListChild(acc);
        }
        else
        {
            aj_accList(acc, "");
        }
    }
}

void AjExecAcc::execGetName(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_accGetName(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecAcc::execState(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_accGetState(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecAcc::execGetType(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_accGetType(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecAcc::execGetParent(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_getAccParent(path);
    execAssign(cmd, ret);
}

void AjExecAcc::execGetChild(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString name = cmd->args[1];
    QString ret = aj_accGetChild(app->hwnd, path, name);
    execAssign(cmd, ret);
}

void AjExecAcc::execSearch(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString name = cmd->args[1];
    QString ret  = aj_findAcc(app->hwnd, path, name);
    execAssign(cmd, ret);
}

void AjExecAcc::execAssign(AjCommand *cmd, QString val)
{
    if( cmd->flag_append )
    {
        val = parser->vars.getVal(cmd->output) + val;
    }
    parser->vars.setVar(cmd->output, val);
}

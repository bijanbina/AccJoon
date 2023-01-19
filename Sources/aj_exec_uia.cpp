#include "aj_exec_uia.h"
#include "aj_win_process.h"
#include "aj_application.h"

AjExecUia::AjExecUia(AjParser *p, AjApplication *a)
{
    parser = p;
    app = a;
    uia = new AjUia(app);
}

void AjExecUia::exec(AjCommand *cmd)
{
    if( cmd->command=="uia_getVal" )
    {
        execGetVal(cmd);
    }
    else if( cmd->command=="uia_setVal" )
    {
        execSetVal(cmd);
    }
    else if( cmd->command=="uia_list" )
    {
        execList(cmd);
    }
    else if( cmd->command=="uia_listChild" )
    {
        execList(cmd);
    }
    else if( cmd->command=="uia_getName" )
    {
        execGetName(cmd);
    }
    else if( cmd->command=="uia_getState" )
    {
        execState(cmd);
    }
    else if( cmd->command=="uia_getType" )
    {
        execGetType(cmd);
    }
    else if( cmd->command=="uia_getParent" )
    {
        execGetParent(cmd);
    }
    else if( cmd->command=="uia_getChild" )
    {
        execGetChild(cmd);
    }
    else if( cmd->command=="uia_search" )
    {
        execSearch(cmd);
    }
}

void AjExecUia::execGetVal(AjCommand *cmd)
{
    QString path = cmd->args[0];
    IUIAutomationElement* element = uia->getElement(app->hwnd);
    QString ret = uia->getValue(element, path);
    execAssign(cmd, ret);
}

void AjExecUia::execSetVal(AjCommand *cmd)
{
    QString path = cmd->args[0];
    IUIAutomationElement* element = uia->getElement(app->hwnd);
    uia->setValue(element, path, cmd->args.last());
}

void AjExecUia::execList(AjCommand *cmd)
{
    if( cmd->args.size() )
    {
        IUIAutomationElement* element = uia->getElement(app->hwnd);
        if( cmd->command=="uia_listChild" )
        {
            uia->list2(element);
        }
        else
        {
            uia->list(element, cmd->args[0]);
        }
    }
    else
    {
        IUIAutomationElement* element = uia->getElement(app->hwnd);
        if( cmd->command=="uia_listChild" )
        {
            uia->list2(element);
        }
        else
        {
            uia->list(element, "");
        }
    }
}

void AjExecUia::execGetName(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = uia->getName(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecUia::execState(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = uia->getState(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecUia::execGetType(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = uia->getType(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecUia::execGetParent(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = uia->getParent(path);
    execAssign(cmd, ret);
}

void AjExecUia::execGetChild(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString name = cmd->args[1];
    ///FIXME: Please implement this function
    QString ret = "";
//    QString ret = uia->getChild(app->hwnd, path, name);
    execAssign(cmd, ret);
}

void AjExecUia::execSearch(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString name = cmd->args[1];
    QString ret  = uia->find(app->hwnd, path, name);
    execAssign(cmd, ret);
}

void AjExecUia::execAssign(AjCommand *cmd, QString val)
{
    if( cmd->flag_append )
    {
        val = parser->vars.getVal(cmd->output) + val;
    }
    parser->vars.setVar(cmd->output, val);
}

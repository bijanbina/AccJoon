#include "aj_exec_uia.h"
#include "aj_win_process.h"
#include "aj_application.h"

AjExecUia::AjExecUia(AjParser *p, AjApplication *a)
{
    parser = p;
    app = a;
    uia = new AjUia(app);
    uia_prop = new AjUiaProp(uia);
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
    else if( cmd->command=="uia_toggle" )
    {
        executeToggle(cmd);
    }
    else if( cmd->command=="uia_getToggle" )
    {
        executeGetToggle(cmd);
    }
}

void AjExecUia::execGetVal(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = uia_prop->getValue(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecUia::execSetVal(AjCommand *cmd)
{
    QString path = cmd->args[0];
    uia_prop->setValue(app->hwnd, path, cmd->args.last());
}

void AjExecUia::execList(AjCommand *cmd)
{
    UiaElement* root = uia->getElement(app->hwnd);
    if( cmd->args.size() )
    {
        UiaElement* parent = uia->getElem(root, cmd->args[0]);
        uia->list(parent, cmd->args[0]);
    }
    else
    {
        uia->list(root, "");
    }
}

void AjExecUia::execListChild(AjCommand *cmd)
{
    UiaElement* root = uia->getElement(app->hwnd);
    if( cmd->args.size() )
    {
        UiaElement* parent = uia->getElem(root, cmd->args[0]);
        uia->listChild(parent);
    }
    else
    {
        uia->listChild(root);
    }
}

void AjExecUia::execGetName(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = uia_prop->getName(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecUia::execState(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = uia_prop->getState(app->hwnd, path);
    execAssign(cmd, ret);
}

void AjExecUia::execGetType(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = uia_prop->getType(app->hwnd, path);
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
    QString ret = uia_prop->getChildPath(app->hwnd, path, name);
    execAssign(cmd, ret);
}

void AjExecUia::execSearch(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString name = cmd->args[1];
    QString var  = uia->find(app->hwnd, path, name);
    execAssign(cmd, var);
}

void AjExecUia::execAssign(AjCommand *cmd, QString val)
{
    if( cmd->flag_append )
    {
        val = parser->vars.getVal(cmd->output) + val;
    }
    parser->vars.setVar(cmd->output, val);
}

void AjExecUia::executeToggle(AjCommand *cmd)
{
    QString path = cmd->args[0];
    uia_prop->toggle(app->hwnd, path);
}

void AjExecUia::executeGetToggle(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret  = uia_prop->getToggle(app->hwnd, path);
    execAssign(cmd, ret);
}

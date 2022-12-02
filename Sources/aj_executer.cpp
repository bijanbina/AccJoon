#include "aj_executer.h"
#include "aj_win_process.h"
#include "aj_application.h"

AjExecuter::AjExecuter(QString script_path)
{
    condition_flag = AJ_NORMAL;

    parser.openFile(script_path);
    while( parser.eof==0 )
    {
        AjCommand cmd = parser.parseLine();
        exec(&cmd);
    }
}

void AjExecuter::exec(AjCommand *cmd)
{
    if( condition_flag==AJ_RUN_NEXT_BLOCK )
    {
        if( cmd->command=="EOB" )
        {
            condition_flag = AJ_NORMAL;
        }
    }
    else
    {
        if( cmd->command=="shortcut" )
        {
            QString shortcut_name = cmd->args[0];
            QString win_title;;
            if( cmd->args.size()>1 )
            {
                win_title = cmd->args[1];
            }
            app = getApplication(shortcut_name, win_title);
            if( app.exe_name=="" )
            {
                qDebug() << "Error: exe file not found"
                     << app.exe_path;
                exit(0);
            }
        }
        else if( cmd->command=="if_t" )
        {
            condition_flag = AJ_TRUE_COND;
        }
        else if( cmd->command=="if_f" )
        {
            condition_flag = AJ_RUN_NEXT_BLOCK;
        }
        else if( cmd->command=="else" )
        {
            if( condition_flag==AJ_PENDING_ELSE )
            {
                condition_flag = AJ_RUN_NEXT_BLOCK;
            }
            else // AJ_NORMAL
            {
                condition_flag = AJ_TRUE_COND;
            }
        }
        else if( cmd->command=="EOB" )
        {
            if( condition_flag==AJ_TRUE_COND )
            {
                condition_flag = AJ_PENDING_ELSE;
            }
            else
            {
                app.hwnd = NULL;
            }
        }
        else
        {
            if( condition_flag!=AJ_TRUE_COND )
            {
                condition_flag = AJ_NORMAL;
            }
            execNormal(cmd);
        }
    }
//    printCondFlag();
}

void AjExecuter::execNormal(AjCommand *cmd)
{
    if( app.hwnd==NULL )
    {
        qDebug() << "Warning: HWND is not set"
                 << "line:" << parser.line_number;
    }
    else
    {
//        setFocus();
    }

    if( cmd->command=="key" )
    {
        execKey(cmd);
    }
    else if( cmd->command=="print" )
    {
        qDebug() << cmd->args[0];
    }
    else if( cmd->command=="open" )
    {
        execOpen(cmd);
    }
    else if( cmd->command=="lua" )
    {
        execLua(cmd);
    }
    else if( cmd->command=="sleep" )
    {
        execSleep(cmd);
    }
    else if( cmd->command=="assign" )
    {
        execAssign(cmd, cmd->args[0]);
    }
    else
    {
        execAcc(cmd);
    }
}

void AjExecuter::execAcc(AjCommand *cmd)
{
    if( cmd->command=="click" )
    {
        execClick(cmd);
    }
    else if( cmd->command=="getVal" )
    {
        execGetVal(cmd);
    }
    else if( cmd->command=="setVal" )
    {
        execSetVal(cmd);
    }
    else if( cmd->command=="accList" )
    {
        execAccList(cmd);
    }
    else if( cmd->command=="accListChild" )
    {
        execAccList(cmd);
    }
    else if( cmd->command=="getName" )
    {
        execGetName(cmd);
    }
    else if( cmd->command=="getState" )
    {
        execState(cmd);
    }
    else if( cmd->command=="getType" )
    {
        execGetType(cmd);
    }
    else if( cmd->command=="getParent" )
    {
        execGetParent(cmd);
    }
    else if( cmd->command=="getChild" )
    {
        execGetChild(cmd);
    }
    else if( cmd->command=="findAcc" )
    {
        execFindAcc(cmd);
    }
}

int AjExecuter::execOpen(AjCommand *cmd)
{
    QString args;
    if( cmd->args.size()>0 )
    {
        QString pcheck = cmd->args[0];
        if( pcheck.length() )
        {
            if( aj_isProcOpen(pcheck) )
            {
                return AJ_CHECK_FAILED;
            }
        }
    }
    if( cmd->args.size()>1 )
    {
        args = cmd->args[1];
    }
    if( cmd->args.size()>2 )
    {
        bool conversion_ok;
        int workspace = cmd->args[2].toInt(&conversion_ok);
        if( conversion_ok && workspace>0 )
        {
            vi.setDesktop(workspace-1);
        }
        else
        {
            qDebug() << "Error: workspace value is wrong";
        }
    }
    launchApp(&app, args);

    return AJ_CHECK_SUCCESS;
}

void AjExecuter::setFocus()
{
    if( app.hwnd==NULL )
    {
//        app->hwnd = GetForegroundWindow();
//        qDebug() << "Switching to active window";
//        if( app.hwnd==NULL )
//        {
            qDebug() << "Error: cannot get foreground window handler";
            return;
//        }
    }
    SetForegroundWindow(app.hwnd);
    QThread::msleep(10);

    char buffer[256];
    GetWindowTextA(app.hwnd, buffer, 256);
    app.win_title = buffer;
}

void AjExecuter::execAssign(AjCommand *cmd, QString val)
{
    if( cmd->flag_append )
    {
        val = parser.vars.getVal(cmd->output) + val;
    }
    parser.vars.setVar(cmd->output, val);
}

int AjExecuter::execClick(AjCommand *cmd)
{
    AjAccCmd acc_cmd;
    QString path = cmd->args[0];

    if( cmd->args.size()>1 )
    {
        acc_cmd.action = cmd->args[1];
    }
    if( cmd->args.size()>2 )
    {
       acc_cmd.acc_name = cmd->args[2];
    }
    if( cmd->args.size()>3 )
    {
       acc_cmd.offset_x = cmd->args[3].toInt();
    }
    if( cmd->args.size()>4 )
    {
        acc_cmd.offset_y = cmd->args[4].toInt();
    }
    if( cmd->args.size()>5 )
    {
        acc_cmd.offset_id = cmd->args[5].toInt();
    }

    POINT obj_center;
    obj_center = aj_getAccLocation(acc_cmd, app.hwnd, path);

    if( obj_center.x==0 && obj_center.y==0 )
    {
        qDebug() << "Error: cannot get location in window ("
                 << app.win_title << ")";
        return -1;
    }
    qDebug() << "obj_center" << obj_center.x
             << obj_center.y << ")";

    aj_mouseClick(obj_center, acc_cmd);

    return 0;
}

void AjExecuter::execGetVal(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_getAccValue(app.hwnd, path);
    execAssign(cmd, ret);
}

void AjExecuter::execSetVal(AjCommand *cmd)
{
    QString path = cmd->args[0];
    aj_setAccValue(app.hwnd, path, cmd->args.last());
}

void AjExecuter::execAccList(AjCommand *cmd)
{
    if( cmd->args.size() )
    {
        IAccessible* acc = aj_getAccHWND(app.hwnd, cmd->args[0]);
        if( cmd->command=="accListChild" )
        {
            aj_accList2(acc);
        }
        else
        {
            aj_accList(acc, cmd->args[0]);
        }
    }
    else
    {
        IAccessible* acc = aj_getWinPAcc(app.hwnd);
        if( cmd->command=="accListChild" )
        {
            aj_accList2(acc);
        }
        else
        {
            aj_accList(acc, "");
        }
    }
}

void AjExecuter::execGetName(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_getAccName(app.hwnd, path);
    execAssign(cmd, ret);
}

int AjExecuter::execKey(AjCommand *cmd)
{
    AjKeyboard keyboard;
    AjKey key = aj_getKey(cmd->args[0]);
    keyboard.execKey(&key);

    return 0;
}

void AjExecuter::execLua(AjCommand *cmd)
{
    AjLua lua;
    QString path = cmd->args[0].remove("\"");
    lua.run(path);
}

void AjExecuter::execSleep(AjCommand *cmd)
{
    bool conversion_ok;
    int delay = cmd->args[0].toInt(&conversion_ok);
    if( conversion_ok && delay>0 )
    {
        QThread::msleep(delay);
    }
    else
    {
        qDebug() << "Error: delay value is wrong";
    }
}

void AjExecuter::execState(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_getAccState(app.hwnd, path);
    execAssign(cmd, ret);
}

void AjExecuter::execGetType(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_getAccType(app.hwnd, path);
    execAssign(cmd, ret);
}

void AjExecuter::execGetParent(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString ret = aj_getAccParent(path);
    execAssign(cmd, ret);
}

void AjExecuter::execGetChild(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString name = cmd->args[1];
    QString ret = aj_getChild(app.hwnd, path, name);
    execAssign(cmd, ret);
}

void AjExecuter::execFindAcc(AjCommand *cmd)
{
    QString path = cmd->args[0];
    QString name = cmd->args[1];
    QString ret  = aj_findAcc(app.hwnd, path, name);
    execAssign(cmd, ret);
}

void AjExecuter::printCondFlag()
{
    if( condition_flag==AJ_RUN_NEXT_BLOCK )
    {
        qDebug() << ">> RUN_NEXT_BLOCK";
    }
    else if( condition_flag==AJ_TRUE_COND )
    {
        qDebug() << ">> TRUE_COND";
    }
    else if( condition_flag==AJ_PENDING_ELSE )
    {
        qDebug() << ">> PENDING_ELSE";
    }
    else if( condition_flag==AJ_NORMAL )
    {
        qDebug() << ">> NORMAL";
    }
}

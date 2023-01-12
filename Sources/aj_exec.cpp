#include "aj_exec.h"
#include "aj_win_process.h"
#include "aj_application.h"

AjExec::AjExec(QString script_path)
{
    condition_flag = AJ_NORMAL;
    acc = new AjExecAcc(&parser, &app);
    uia = new AjExecUia(&parser, &app);

    parser.openFile(script_path);
    while( parser.eof==0 )
    {
        AjCommand cmd = parser.parseLine();
        exec(&cmd);
    }
}

void AjExec::exec(AjCommand *cmd)
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

void AjExec::execNormal(AjCommand *cmd)
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

    if( cmd->command=="click" )
    {
        execClick(cmd);
    }
    else if( cmd->command=="key" )
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
    else if( cmd->command.startsWith("acc_") )
    {
        acc->exec(cmd);
    }
    else if( cmd->command.startsWith("uia_") )
    {
        uia->exec(cmd);
    }
    else
    {
        qDebug() << "unknown command";
    }
}

int AjExec::execOpen(AjCommand *cmd)
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

void AjExec::setFocus()
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

int AjExec::execClick(AjCommand *cmd)
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
    obj_center = aj_accGetLocation(acc_cmd, app.hwnd, path);

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

int AjExec::execKey(AjCommand *cmd)
{
    AjKeyboard keyboard;
    AjKey key = aj_getKey(cmd->args[0]);
    keyboard.execKey(&key);

    return 0;
}

void AjExec::execLua(AjCommand *cmd)
{
    AjLua lua;
    QString path = cmd->args[0].remove("\"");
    lua.run(path);
}

void AjExec::execSleep(AjCommand *cmd)
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

void AjExec::printCondFlag()
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

void AjExec::execAssign(AjCommand *cmd, QString val)
{
    if( cmd->flag_append )
    {
        val = parser.vars.getVal(cmd->output) + val;
    }
    parser.vars.setVar(cmd->output, val);
}

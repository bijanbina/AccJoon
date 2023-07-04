#include "aj_exec.h"
#include "aj_win_process.h"
#include "aj_application.h"

AjExec::AjExec(AjTreeParser *tp, QStringList arguments)
{
    tree_parser = tp;
    addArgs(arguments);
    acc = new AjExecAcc(&parser, &application);
    uia = new AjExecUia(&parser, &application);
}

void AjExec::execApps(QVector<AjApp *> apps)
{
    int len = apps.size();
    for( int i=0 ; i<len ; i++ )
    {
        qDebug() << "---------------" << apps[i]->app_name
                 << "---------------";
        updateApp(apps[i]);
        execApp(apps[i]);
    }
}

int AjExec::execApp(AjApp *app)
{
    int lines_size = app->lines.size();
    for( int i=0 ; i<lines_size ; i++ )
    {
        if( app->lines[i]->cond==NULL )
        {
            QString line = app->lines[i]->line;
            AjCommand cmd = parser.parseLine(line);
            if( cmd.command==AJ_RET_CMD )
            {
                qDebug() << "execApp:return";
                return 1;
            }
            exec(&cmd);
        }
        else
        {
            AjCondOpt *cond = app->lines[i]->cond;
            int cond_result = parser.parseCondition(cond);
            if( cond_result )
            {
                AjApp fake_app = *app;
                fake_app.start_line = cond->if_start;
                fake_app.end_line = cond->if_end;
                fake_app.lines.clear();
                tree_parser->parseConditions(&fake_app);
                int ret = execApp(&fake_app);
                if( ret )
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void AjExec::updateApp(AjApp *app)
{
    application = getApplication(app->app_name, app->win_title);
    if( application.exe_name=="" )
    {
        qDebug() << "Error: exe file not found"
             << application.exe_path;
        exit(0);
    }
}

void AjExec::exec(AjCommand *cmd)
{
    if( application.hwnd==NULL )
    {
        qDebug() << "Warning: HWND is not set, line:"
                 << parser.line_number;
    }
    else
    {
        aj_setFocus(&application);
    }

    if( cmd->command==AJ_CLICK_CMD )
    {
        execClick(cmd);
    }
    else if( cmd->command==AJ_KEY_CMD )
    {
        execKey(cmd);
    }
    else if( cmd->command==AJ_PRINT_CMD )
    {
        qDebug() << cmd->args[0];
    }
    else if( cmd->command==AJ_OPEN_CMD )
    {
        execOpen(cmd);
    }
    else if( cmd->command==AJ_ISOPEN_CMD )
    {
        execIsOpen(cmd);
    }
    else if( cmd->command==AJ_LUA_CMD )
    {
        execLua(cmd);
    }
    else if( cmd->command==AJ_SLEEP_CMD )
    {
        execSleep(cmd);
    }
    else if( cmd->command==AJ_W8OPEN_CMD )
    {
        execWaitOpen(cmd);
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
        qDebug() << "Error 133: unknown command" << cmd->command;
    }
}

void AjExec::execWaitOpen(AjCommand *cmd)
{
    if( cmd->args.size()==0 )
    {
        qDebug() << "WaitOpen not correct argument size";
        exit(0);
    }
    QString waited_process = cmd->args[0];
    while( 1 )
    {
        QThread::msleep(10);
        if( aj_isProcOpen(waited_process) )
        {
            break;
        }
    }
}

int AjExec::execOpen(AjCommand *cmd)
{
    QString args;
    if( cmd->args.size()>0 )
    {
        args = cmd->args[0];
    }
    if( cmd->args.size()>1 )
    {
        bool conversion_ok;
        int workspace = cmd->args[1].toInt(&conversion_ok);
        if( conversion_ok && workspace>0 )
        {
            vi.setDesktop(workspace-1);
        }
        else
        {
            qDebug() << "Error: workspace value is wrong";
        }
    }
    launchApp(&application, args);
    /// FIXME: implement a function to wait for a HWND to show up
    ///        and update application.hwnd and then uncomment line 89
    ///        and test
    aj_findWindowByPid(application.pid, &application);
    return AJ_CHECK_SUCCESS;
}

void AjExec::execIsOpen(AjCommand *cmd)
{
    QString var  = "0";
    if( cmd->args.size()==0 )
    {
        qDebug() << "IsOpen not correct argument size";
        exit(0);
    }
    QString pcheck = cmd->args[0];
    if( aj_isProcOpen(pcheck) )
    {
        var = "1";
    }
    execAssign(cmd, var);
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
    obj_center = aj_accGetLocation(acc_cmd, application.hwnd, path);

    if( obj_center.x==0 && obj_center.y==0 )
    {
        qDebug() << "Error: cannot get location in window ("
                 << application.win_title << ")";
        return -1;
    }
//    qDebug() << "obj_center" << obj_center.x
//             << obj_center.y;

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
    qDebug() << "assign" << cmd->output
             << "=" << val;
    parser.vars.setVar(cmd->output, val);
}

void AjExec::addArgs(QStringList args)
{
    int len = args.size();
    for( int i=0 ; i<len ; i++ )
    {
        parser.vars.setArg(i, args[i]);
    }
}

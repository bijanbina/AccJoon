#include "aj_executer.h"
#include "aj_win_process.h"
#include "aj_shortcut.h"

AjExecuter::AjExecuter(QString script_path)
{
    parser.openFile(script_path);
    while( parser.eof==0 )
    {
        aj_findAppByName(app.exe_name, &(app.window));
        AjCommand cmd = parser.parseLine();
        exec(&cmd);
    }
}

void AjExecuter::exec(AjCommand *cmd)
{
    QString command = cmd->command.toLower();
    AjWin aj_win(app.hwnd);

    if( command=="read" && condition_flag>=0 )
    {
        QString ret = aj_win.execRead(cmd);
        if( ret.length() )
        {
            parser.vars.addVar(cmd->output, ret);
        }
    }
    else if( command=="write" && condition_flag>=0 )
    {
        aj_win.execWrite(cmd);
    }
    else if( command=="click" && condition_flag>=0 )
    {
        aj_win.execClick(cmd);
    }
    else if( command=="key" && condition_flag>=0 )
    {
        aj_win.execKey(cmd);
    }
    else if( command=="open" && condition_flag>=0 )
    {
        execOpen(cmd);
    }
    else if( command=="delay" && condition_flag>=0 )
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
    else if( command=="lua" && condition_flag>=0 )
    {
        AjLua lua;
        QString path = cmd->args[0].remove("\"");
        lua.run(path);
    }
    else if( command=="shortcut" )
    {
        app.shortcut_name = cmd->args[0].remove("\"").trimmed();
        app = getApplication(app.shortcut_name);
        if( app.exe_name=="" )
        {
            qDebug() << "Error: exe file not found"
                 << app.exe_path;
            exit(0);
        }
    }
    else if( command=="if" )
    {
        if( cmd->args[0]==cmd->args[1] )
        {
            condition_flag = 1;
        }
        else
        {
            condition_flag = -1;
        }
    }
    else if( command=="EOF" )
    {
        ;
    }
    else if( command=="EOA" )
    {
        if( condition_flag )
        {
            condition_flag = 0;
        }
        else
        {
            app.shortcut_name = ""; //fixme: all of them
        }
    }
}

int AjExecuter::execOpen(AjCommand *cmd)
{
    QString args;
    if( cmd->args.size()>0 )
    {
        QString pcheck = cmd->args[0].remove("\"").trimmed();
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
        args = cmd->args[1].remove("\"").trimmed();
    }
    if( cmd->args.size()>2 )
    {
        bool conversion_ok;
        int workspace = cmd->args[2].trimmed().toInt(&conversion_ok);
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

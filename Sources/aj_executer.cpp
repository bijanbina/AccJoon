#include "aj_executer.h"
#include "aj_win_process.h"
#include "aj_launcher.h"
#include "aj_virt.h"

AjVirt vi;

void aj_execute(QString conf_path)
{
    AjParser parser(conf_path); // value stored in parser
    AjApplication app;
    aj_clearApp(&app);

    while( parser.atEnd() )
    {
        aj_executeLine(&parser, &app);
    }
}

void aj_executeLine(AjParser *parser, AjApplication *app)
{
    AjCommand cmd = parser->parseLine();
    QString command = cmd.command.toLower();

    if( command=="read" && parser->condition_flag>=0 )
    {
        AjWin aj_win(aj_getHwnd(app));
        QString ret = aj_win.readAcc(cmd);
        if( ret.length() )
        {
            parser->vars.addVar(cmd.output, ret);
        }
    }
    else if( command=="write" && parser->condition_flag>=0 )
    {
        AjWin aj_win(aj_getHwnd(app));
        aj_win.writeAcc(cmd);
    }
    else if( command=="click" && parser->condition_flag>=0 )
    {
        AjWin aj_win(aj_getHwnd(app));
        aj_win.doAcc(cmd);
    }
    else if( command=="key" && parser->condition_flag>=0 )
    {
        AjWin aj_win(aj_getHwnd(app));
        aj_win.doKey(cmd);
    }
    else if( command=="open" && parser->condition_flag>=0 )
    {
        aj_executeOpen(app, &cmd);
    }
    else if( command=="delay" && parser->condition_flag>=0 )
    {
        bool conversion_ok;
        int delay = cmd.args[0].toInt(&conversion_ok);
        if( conversion_ok && delay>0 )
        {
            QThread::msleep(delay);
        }
        else
        {
            qDebug() << "Error: delay value is wrong";
        }
    }
    else if( command=="lua" && parser->condition_flag>=0 )
    {
        AjLua lua;
        QString path = cmd.args[0].remove("\"");
        lua.run(path);
    }
    else if( command=="shortcut" )
    {
        app->app_name = cmd.args[0].remove("\"").trimmed();
        app->win_launcher = new AjLauncher(app->app_name);
        app->app_name = app->win_launcher->getExeName();
        if( app->app_name=="" )
        {
            qDebug() << "Error: exe file not found"
                 << app->win_launcher->link_path;
            exit(0);
        }
    }
    else if( command=="if" )
    {
        if( cmd.args[0] == cmd.args[1] )
        {
            parser->condition_flag = 1;
        }
        else
        {
            parser->condition_flag = -1;
        }
    }
    else if( command=="EOF" )
    {
        ;
    }
    else if( command=="EOA" )
    {
        if( parser->condition_flag )
        {
            parser->condition_flag = 0;
        }
        else
        {
            aj_clearApp(app);
        }
    }
}

void aj_executeOpen(AjApplication *app, AjCommand *cmd)
{
    QString args;
    if( cmd->args.size()>0 )
    {
        QString pcheck = cmd->args[0].remove("\"").trimmed();
        if( pcheck.length() )
        {
            if( aj_isProcOpen(pcheck) )
            {
                return;
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
    DWORD pid = app->win_launcher->launchApp(args);
    app->req_win = aj_findAppByPid(pid);
}

void aj_clearApp(AjApplication *app)
{
    app->app_name = "";
    app->exe_name = "";
    app->pid = 0;
    if( app->req_win )
    {
        delete app->req_win;
    }
    app->req_win = NULL;
}

HWND aj_getHwnd(AjApplication *app)
{
    if( app->req_win==NULL )
    {
        app->req_win = aj_findAppByName(app->exe_name);
    }
    return app->req_win->hWnd;
}

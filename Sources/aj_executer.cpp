#include "aj_executer.h"
#include "aj_win_process.h"
#include "aj_launcher.h"
#include "aj_virt.h"

AjVirt vi;

void aj_execute(QString conf_path)
{
    AjAppOptions current_app;
    AjParser parser(conf_path); // value stored in parser

    while( !parser.atEnd() )
    {
        parser.parseLine(&current_app);
    }


    script_vars.clear();

    HWND hwnd = NULL;
    if( apps[i].app_name.length() )
    {
        hwnd = aj_executeApp(apps[i]);
    }
    aj_executeCmds(apps[i], hwnd);
}

HWND aj_executeApp(AjAppOptions app)
{
    if( app.pcheck.length() )
    {
        if( aj_isProcOpen(app.pcheck) )
        {
            return NULL;
        }
    }

    if( app.workspace )
    {
        vi.setDesktop(app.workspace-1);
    }

    AjWindow *req_win;
    AjLauncher win_launcher(app.app_name);
    QString exe_name = win_launcher.getExeName();
    if( exe_name=="" )
    {
        qDebug() << "Error: exe file not found"
             << win_launcher.link_path;
        return NULL;
    }
    if( app.is_open )
    {
        DWORD pid = win_launcher.launchApp(app.args);
        req_win = aj_findAppByPid(pid);
        QThread::msleep(app.open_delay);
    }
    else
    {
        req_win = aj_findAppByName(exe_name);
    }
    return req_win->hWnd;
}

void aj_executeCmds(AjAppOptions app, HWND hwnd)
{
    AjLua lua;
    AjWin aj_win(hwnd);
    AjVar var_list;

    for( int j=0; j<app.command.size(); j++ )
    {
        if( app.command[j].type==AJ_CMD_SCRIPT )
        {
            lua.run(app.command[j].path);
        }
        else if( app.command[j].type==AJ_CMD_KEY )
        {
            aj_win.doKey(app.command[j]);
        }
        else if( app.command[j].type==AJ_CMD_ACC )
        {
            aj_win.doAcc(app.command[j]);
        }
        else if( app.command[j].type==AJ_CMD_READ )
        {
            QString ret = aj_win.readAcc(app.command[j]);
            if( ret.length() )
            {
                aj_addVar(app.command[j].value_name, ret);
            }
        }
        else if( app.command[j].type==AJ_CMD_WRITE )
        {
            QString ret = var_list.getVal(app.command[j].value_name);
            if( ret.length() )
            {
                app.command[j].value = ret;
                aj_win.writeAcc(app.command[j]);
            }
        }
        QThread::msleep(app.command[j].delay);
    }
}

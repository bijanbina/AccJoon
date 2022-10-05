#include "aj_executer.h"
#include "aj_win_process.h"
#include "aj_win32_launcher.h"

void aj_execute(QVector<AjAppOptions> apps)
{
    for( int i=0; i<apps.size(); i++ )
    {
        aj_executeApp(apps[i]);
    }
}

void aj_executeApp(AjAppOptions app)
{
    if( app.pcheck.length() )
    {
        if( aj_isProcOpen(app.pcheck) )
        {
            return;
        }
    }
    AjWindow *req_win;
    AjWin32Launcher *win_launcher = new AjWin32Launcher(
                app.app_name);
    QString exe_name = win_launcher->getExeName();
    QThread::msleep(app.start_delay);
    if( exe_name=="" )
    {
        qDebug() << "Error: exe file not found"
                 << app.app_name;
        return;
    }
    if( app.is_open )
    {
        DWORD pid = win_launcher->launchApp();
        req_win = aj_findAppByPid(pid);
        QThread::msleep(app.open_delay);
    }
    else
    {
        req_win = aj_findAppByName(exe_name);
    }

    AjWin aj_win(req_win->hWnd);

    for( int j=0; j<app.commands.size(); j++ )
    {
        if( aj_win.doAction(app.commands[j])!=0 )
        {
            return;
        }
        QThread::msleep(app.commands[j].delay);
    }
}

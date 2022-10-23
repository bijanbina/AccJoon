#include "aj_executer.h"
#include "aj_win_process.h"
#include "aj_launcher.h"
#include "aj_virt.h"

AjVirt vi;
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

    if( app.workspace )
    {
        vi.setDesktop(app.workspace-1);
    }

    AjWindow *req_win;
    AjLauncher *win_launcher = new AjLauncher(
                app.app_name);
    QString exe_name = win_launcher->getExeName();
    QThread::msleep(app.start_delay);
    if( exe_name=="" )
    {
        qDebug() << "Error: exe file not found"
                 << win_launcher->link_path;
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

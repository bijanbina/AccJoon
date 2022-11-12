#include "aj_executer.h"
#include "aj_win_process.h"
#include "aj_shortcut.h"

AjExecuter::AjExecuter(QString script_path)
{
    parser.openFile(script_path);
    while( parser.eof==0 )
    {
        AjCommand cmd = parser.parseLine();
        exec(&cmd);
    }
}

void AjExecuter::exec(AjCommand *cmd)
{
    if( inside_false_if )
    {
        if( cmd->command=="EOB" )
        {
            inside_false_if = 0;
        }
    }
    else
    {
        if( cmd->command=="shortcut" )
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
        else if( cmd->command=="if" )
        {
            if( cmd->args[0]==cmd->args[1] )
            {
                inside_false_if = 0;
            }
            else
            {
                inside_false_if = 1;
            }
        }
        else if( cmd->command=="EOB" )
        {
            app.hwnd = NULL;
        }
        else
        {
            execNormal(cmd);
        }
    }
}

void AjExecuter::execNormal(AjCommand *cmd)
{
    if( cmd->command=="click" )
    {
        execClick(cmd);
    }
    else if( cmd->command=="key" )
    {
        execKey(cmd);
    }
    else if( cmd->command=="open" )
    {
        execOpen(cmd);
    }
    else if( cmd->command=="delay" )
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
    else if( cmd->command=="lua" )
    {
        AjLua lua;
        QString path = cmd->args[0].remove("\"");
        lua.run(path);
    }
    else if( cmd->command=="read" )
    {
        QString ret = execRead(cmd);
        if( ret.length() )
        {
            parser.vars.addVar(cmd->output, ret);
        }
    }
    else if( cmd->command=="write" )
    {
        execWrite(cmd);
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

void AjExecuter::setFocus()
{
    if( app.hwnd==NULL )
    {
//        app->hwnd = GetForegroundWindow();
        qDebug() << "Switching to active window";
        if( app.hwnd==NULL )
        {
            qDebug() << "Error: cannot get foreground window handler";
            return;
        }
    }

    char buffer[256];
    GetWindowTextA(app.hwnd, buffer, 256);
    app.win_title = buffer;
}

int AjExecuter::execKey(AjCommand *cmd)
{
    AjKeyboard keyboard;
    if( app.hwnd!=NULL )
    {
        SetForegroundWindow(app.hwnd);
    }
    QThread::msleep(10);

    AjKey key = aj_getKey(cmd->args[0]);
    keyboard.execKey(&key);

    return 0;
}

int AjExecuter::execClick(AjCommand *cmd)
{
    AjAccCmd acc_cmd;
    if( app.hwnd==NULL )
    {
        qDebug() << "Error: HWND is not set";
        return -1;
    }
    SetForegroundWindow(app.hwnd);
    QThread::msleep(10);

    QString path = cmd->args[0].remove("\"").trimmed();

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

    setFocus();
    POINT obj_center;
    obj_center = getAccLocation(acc_cmd, app.hwnd, path);

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

QString AjExecuter::execRead(AjCommand *cmd)
{
    if( app.hwnd==NULL )
    {
        qDebug() << "Error: HWND is not set";
        return "";
    }
    SetForegroundWindow(app.hwnd);
    QThread::msleep(10);

    QString path = cmd->args[0].remove("\"").trimmed();

    setFocus();

    QString ret = getAccValue(app.hwnd, path);

    return ret;
}

void AjExecuter::execWrite(AjCommand *cmd)
{
    if( app.hwnd==NULL )
    {
        qDebug() << "Error: HWND is not set";
        return;
    }
    SetForegroundWindow(app.hwnd);
    QThread::msleep(10);

    QString path = cmd->args[0].remove("\"").trimmed();

    setFocus();
    setAccValue(app.hwnd, path, cmd->args.last());
}

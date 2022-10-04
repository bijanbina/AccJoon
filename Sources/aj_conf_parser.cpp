#include "aj_conf_parser.h"
#include "aj_win32.h"
#include "aj_dllgen.h"
#include "aj_win_process.h"
#include "aj_keyboard.h"
#include <QDir>

AjExecuter::AjExecuter(QString path)
{
    conf_path = path;
    parseConf();
    printConf();
}

void AjExecuter::run()
{
    for( int i=0; i<apps.size(); i++ )
    {
        runApp(i);
    }
}

void AjExecuter::runApp(int i)
{
    if( apps[i].pcheck.length() )
    {
        if( aj_isProcOpen(apps[i].pcheck) )
        {
            return;
        }
    }
    AjWindow *req_win;
    AjWin32Launcher *win_launcher = new AjWin32Launcher(
                apps[i].app_name);
    QString exe_name = win_launcher->getExeName();
    QThread::msleep(apps[i].start_delay);
    if( exe_name=="" )
    {
        qDebug() << "Error: exe file not found"
                 << apps[i].app_name;
        return;
    }
    if( apps[i].is_open )
    {
        DWORD pid = win_launcher->launchApp();
        req_win = aj_findAppByPid(pid);
        QThread::msleep(apps[i].open_delay);
    }
    else
    {
        req_win = aj_findAppByName(exe_name);
    }

    AjWin *aj_win;
    aj_win = new AjWin(req_win->hWnd);

    for( int j=0; j<apps[i].commands.size(); j++ )
    {
        if( aj_win->doAction(apps[i].commands[j])!=0 )
        {
            return;
        }
        QThread::msleep(apps[i].commands[j].delay);
    }
    delete aj_win;
}

void AjExecuter::parseConf()
{
    conf_file = new QFile(conf_path);
    qDebug() << "Working dir is" << QDir::current().path();
    if( !conf_file->open(QIODevice::ReadOnly |
                        QIODevice::Text) )
    {
        qDebug() << "Error: cannot open conf file" << conf_path;
        qDebug() << "Working dir is" << QDir::current().path();
        return;
    }

    end_of_file = false;
    while( !end_of_file )
    {
        addAppSpec();
    }
    conf_file->close();
}

void AjExecuter::addAppSpec()
{
    QByteArray line = readLine();
    if( line!="" && !end_of_app )
    {
        if( !setAppConf(line) )
        {
            qDebug() << "Error: cannot parse 1st line" << conf_path;
            return;
        }
    }
    else
    {
        qDebug() << "Error: incomplete conf file"
                 << "- (app name) - app[" << apps.size() << "]" << conf_path;
        return;
    }

    line = readLine();
    if( line!="" && !end_of_app )
    {
        if( !setOpenState(line) )
        {
            qDebug() << "Error: cannot parse 2nd line" << conf_path;
            return;
        }
    }
    else
    {
        qDebug() << "Error: incomplete conf file"
                 << "- (open state) - app[" << apps.size() << "]" << conf_path;
        return;
    }

    line = readLine();
    if( line!="" && !end_of_app )
    {
        if( !addCmd(line) )
        {
            qDebug() << "Error: cannot parse 3rd line" << conf_path;
            return;
        }
    }
    else
    {
        qDebug() << "Error: incomplete conf file"
                 << "- (commands) - app[" << apps.size() << "]" << conf_path;
        return;
    }

    int line_cnt = 4;
    line = readLine();
    while( line!="" && !end_of_app )
    {
        if( !addCmd(line) )
        {
            qDebug() << "Error: cannot parse" << line_cnt
                     << "th line" << conf_path;
            return;
        }
        line = readLine();
        line_cnt++;
    }
    appendApp();
}

bool AjExecuter::addCmd(QByteArray data)
{
    QByteArrayList data_list = data.split(' ');
    if( data_list.size()<1 )
    {
        return false;
    }

    if( data_list[0].contains("key") )
    {
        return addKey(data_list);
    }
    else if( data_list[0].contains("path") )
    {
        return addAcc(data_list);
    }
    return true;
}

bool AjExecuter::addKey(QByteArrayList data_list)
{
    QString key = "";
    int key_int = -1;
    int delay=0, alt_key=0, ctrl_key=0, shift_key=0, meta_key=0;

    for( int i=0; i<data_list.size(); i++)
    {
        if( checkParam(data_list[i], "key") )
        {
            key = data_list[i].split('=')[1];
            key = key.toLower();
            QStringList key_list = key.split('+');
            for( int i=0; i<key_list.size(); i++ )
            {
                if( i==key_list.size()-1 )
                {
                    key = key_list[i];
                    if( key.size()>1 )
                    {
                        key_int = aj_keyCode(key);
                    }
                    else
                    {
                        key_int = key.toUpper().toStdString()[0];
                    }
                }
                else if( key_list[i].contains("alt") )
                {
                    alt_key = 1;
                }
                else if( key_list[i].contains("ctrl") )
                {
                    ctrl_key = 1;
                }
                else if( key_list[i].contains("shift") )
                {
                    shift_key = 1;
                }
                else if( key_list[i].contains("super") )
                {
                    meta_key = 1;
                }
                else
                {
                    return false;
                }
            }
        }
        else if( checkParam(data_list[i], "delay") )
        {
            delay = data_list[i].split('=')[1].toInt();
        }
        else
        {
            return false;
        }
    }

    AjCommand acc_conf;
    acc_conf.key = key_int;
    acc_conf.delay = delay + delay_line;
    acc_conf.alt_key = alt_key;
    acc_conf.ctrl_key = ctrl_key;
    acc_conf.shift_key = shift_key;
    acc_conf.meta_key = meta_key;
    commands.push_back(acc_conf);
    return true;
}

bool AjExecuter::addAcc(QByteArrayList data_list)
{
    QString acc_path, cmd="L", acc_name="";
    int delay=0, offset_x=0, offset_y=0, offset_id=0;

    for( int i=0; i<data_list.size(); i++ )
    {
        if( checkParam(data_list[i], "path") )
        {
            acc_path = data_list[i].split('=')[1];
        }
        else if( checkParam(data_list[i], "name") )
        {
            acc_name = data_list[i].split('=')[1];
        }
        else if( checkParam(data_list[i], "cmd") )
        {
            cmd = data_list[i].split('=')[1];
        }
        else if( checkParam(data_list[i], "delay") )
        {
            delay = data_list[i].split('=')[1].toInt();
        }
        else if( checkParam(data_list[i], "ox") )
        {
            offset_x = data_list[i].split('=')[1].toInt();
        }
        else if( checkParam(data_list[i], "oy") )
        {
            offset_y = data_list[i].split('=')[1].toInt();
        }
        else if( checkParam(data_list[i], "oid") )
        {
            offset_id = data_list[i].split('=')[1].toInt();
        }
        else
        {
            return false;
        }
    }

    AjCommand acc_conf;
    acc_conf.acc_path = acc_path;
    acc_conf.acc_name = acc_name;
    acc_conf.action = cmd;
    acc_conf.delay = delay;
    acc_conf.offset_x = offset_x;
    acc_conf.offset_y = offset_y;
    acc_conf.offset_id = offset_id;
    acc_conf.key = -1;
    commands.push_back(acc_conf);
    return true;
}

bool AjExecuter::setAppConf(QByteArray data)
{
    QByteArrayList data_list = data.split('=');
    if( data_list.size()<2 )
    {
        return false;
    }
    if( data_list[0].contains("shortcut") ||
        data_list[0].contains("pid") ||
        data_list[0].contains("pname") ||
        data_list[0].contains("title") )
    {
        app_func = data_list[0].trimmed();
        app_name = data_list[1].trimmed();
        start_delay = delay_line;
        return true;
    }
    else
    {
        return false;
    }
}

bool AjExecuter::setOpenState(QByteArray data)
{
    is_open = 0;
    open_delay = 0;
    workspace = 0;
    pcheck = "";

    QByteArrayList data_list = data.split(' ');
    if( data_list.size()<1 )
    {
        return false;
    }

    for( int i=0 ; i<data_list.size() ; i++ )
    {
        if( checkParam(data_list[i], "open") )
        {
            QByteArray value = data_list[i].split('=')[1];
            is_open = value.trimmed().toInt();
        }
        else if( checkParam(data_list[i], "delay") )
        {
            QByteArray value = data_list[i].split('=')[1];
            open_delay = value.trimmed().toInt();
        }
        else if( checkParam(data_list[i], "workspace") )
        {
            QByteArray value = data_list[i].split('=')[1];
            workspace = value.trimmed().toInt();
        }
        else if( checkParam(data_list[i], "check") )
        {
            QByteArray value = data_list[i].split('=')[1];
            pcheck = value.trimmed();
        }
        else
        {
            return false;
        }
    }
    open_delay += delay_line;
    return true;
}

void AjExecuter::appendApp()
{
    AjAppOptions app;
    app.app_name = app_name;
    app.app_func = app_func;
    app.is_open = is_open;
    app.start_delay = start_delay;
    app.open_delay = open_delay;
    app.commands = commands;
    app.pcheck = pcheck;
    app.workspace = workspace;
    apps.push_back(app);

    commands.clear();
    app_name.clear();
    app_func.clear();
    pcheck.clear();
    workspace = 0;
    is_open = 0;
    start_delay = 0;
    open_delay = 0;
}

QByteArray AjExecuter::readLine()
{
    delay_line = 0;
    end_of_app = false;
    while( !conf_file->atEnd() )
    {
        QByteArray line = conf_file->readLine().trimmed();
        if( line.startsWith("--") )
        {
            continue;
        }
        else if( line.startsWith("delay") )
        {
            QByteArrayList words = line.split('=');
            if( words.size()>1 )
            {
                delay_line += words[1].trimmed().toInt();
            }
            continue;
        }
        else if( line.startsWith("{") )
        {
            continue;
        }
        else if( line.startsWith("}") )
        {
            end_of_app = true;
            if( conf_file->atEnd() )
            {
                end_of_file = true;
            }
        }
        return line;
    }
    if( conf_file->atEnd() )
    {
        end_of_file = true;
    }
    return "";
}

bool AjExecuter::checkParam(QByteArray data, QString match, char sep)
{
    QByteArrayList data_list = data.split(sep);
    if(data_list.size()<2)
    {
        return false;
    }
    if( !data_list[0].contains(match.toStdString().c_str()) )
    {
        return false;
    }
    return true;
}

void AjExecuter::printConf()
{
    for( int j=0; j<apps.size(); j++ )
    {
        qDebug() << "--------" << apps[j].app_func
                 << apps[j].app_name << "-------"
                 << "open:" << apps[j].is_open
                 << "check:" << apps[j].pcheck
                 << "workspace:" << apps[j].workspace
                 << "start-delay:" << apps[j].start_delay
                 << "open-delay:" << apps[j].open_delay;
        for( int i=0; i<apps[j].commands.size(); i++ )
        {
            AjCommand acc_conf = apps[j].commands[i];
            if( acc_conf.key>0 )
            {
                qDebug() << i << ")" << acc_conf.key
                         << acc_conf.alt_key << acc_conf.ctrl_key
                         << acc_conf.shift_key << acc_conf.meta_key
                         << acc_conf.delay;
            }
            else if( acc_conf.action.length() )
            {
                qDebug() << i << ")" << acc_conf.acc_path
                         << acc_conf.acc_name << acc_conf.action
                         << acc_conf.offset_x << acc_conf.offset_y
                         << acc_conf.offset_id << acc_conf.delay;
            }
        }
    }
}

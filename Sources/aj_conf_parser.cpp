#include "aj_conf_parser.h"
#include "aj_win32.h"
#include "aj_dllgen.h"

AjExecuter::AjExecuter(QString conf_path)
{
    readConfFile(conf_path);
    AjDllGen *test = new AjDllGen("dll_gen.bat");
//    printConf();
}

void AjExecuter::run()
{
    AjWindow *req_win;
    AjWin32Launcher *win_launcher = new AjWin32Launcher(app_name);
    exe_name = win_launcher->getExeName();
    if( exe_name=="" )
    {
        qDebug() << "Error: exe file not found.";
        return;
    }
    if( is_open )
    {
        DWORD pid = win_launcher->launchApp();
        req_win = aj_findAppByPid(pid);
        QThread::msleep(open_delay);
    }
    else
    {
        req_win = aj_findAppByName(exe_name);
    }
    AjWin *aj_win;
    aj_win = new AjWin(req_win->hWnd);
    for( int i=0; i<commands.size(); i++ )
    {
        if( aj_win->doAction(commands[i])!=0 )
        {
            return;
        }
        QThread::msleep(commands[i].delay);
    }
    delete aj_win;
}

void AjExecuter::readConfFile(QString conf_path)
{
    conf_file = new QFile(conf_path);
    if( !conf_file->open(QIODevice::ReadOnly |
                        QIODevice::Text) )
    {
        qDebug() << "Error: cannot open conf file" << conf_path;
        return;
    }

    QByteArray line = readLine();
    if( line!="" )
    {
        if( !setAppConf(line) )
        {
            qDebug() << "Error: cannot parse 1st line" << conf_path;
            return;
        }
    }
    else
    {
        qDebug() << "Error: incomplete conf file" << conf_path;
        return;
    }

    line = readLine();
    if( line!="" )
    {
        if( !setOpenState(line) )
        {
            qDebug() << "Error: cannot parse 2nd line" << conf_path;
            return;
        }
    }
    else
    {
        qDebug() << "Error: incomplete conf file" << conf_path;
        return;
    }

    line = readLine();
    if( line!="" )
    {
        if( !addCmd(line) )
        {
            qDebug() << "Error: cannot parse 3rd line" << conf_path;
            return;
        }
    }
    else
    {
        qDebug() << "Error: incomplete conf file" << conf_path;
        return;
    }

    int line_cnt = 4;
    line = readLine();
    while( line!="" )
    {
        if( !addCmd(line) )
        {
            qDebug() << "Error: cannot parse" << line_cnt++
                     << "th line" << conf_path;
            return;
        }
        line = readLine();
    }
    conf_file->close();
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
    QString key;
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
                        qDebug() << "Error: more than 1 key is not supported";
                        return false;
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
    acc_conf.key = key;
    acc_conf.delay = delay;
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
        return true;
    }
    else
    {
        return false;
    }
}

bool AjExecuter::setOpenState(QByteArray data)
{
    QByteArrayList data_list = data.split(' ');
    if( data_list.size()<AJ_OPEN_PAR )
    {
        return false;
    }

    if( checkParam(data_list[0], "open") )
    {
        QByteArray value = data_list[0].split('=')[1];
        is_open = value.trimmed().toInt();
    }
    else
    {
        return false;
    }

    if( checkParam(data_list[1], "delay") )
    {
        QByteArray value = data_list[1].split('=')[1];
        open_delay = value.trimmed().toInt();
    }
    else
    {
        return false;
    }
    return true;
}

QByteArray AjExecuter::readLine()
{
    while( !conf_file->atEnd() )
    {
        QByteArray line = conf_file->readLine();
        if( line.size()>2 )
        {
            if( line.mid(0, 2)=="--" )
            {
                continue;
            }
        }
        return line;
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
    qDebug() << "--------" << app_func << app_name << "-------";
    qDebug() << "open:" << is_open;
    for( int i=0; i<commands.size(); i++ )
    {
        AjCommand acc_conf = commands[i];
        if( acc_conf.key.isEmpty() )
        {
            qDebug() << i << ")" << acc_conf.acc_path
                     << acc_conf.acc_name
                     << acc_conf.action << acc_conf.delay
                     << acc_conf.offset_x << acc_conf.offset_y
                     << acc_conf.offset_id;
        }
        else if( acc_conf.action.isEmpty() )
        {
            qDebug() << i << ")" << acc_conf.key
                     << acc_conf.alt_key << acc_conf.ctrl_key
                     << acc_conf.shift_key << acc_conf.meta_key;
        }
    }
}

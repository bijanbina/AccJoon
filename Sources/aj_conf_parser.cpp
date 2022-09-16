#include "aj_conf_parser.h"
#include "aj_win32.h"

AjExecuter::AjExecuter(QString conf_path)
{
    QFile conf_file(conf_path);
    if( !conf_file.open(QIODevice::ReadOnly |
                        QIODevice::Text) )
    {
        qDebug() << "Error: cannot open conf file" << conf_path;
        return;
    }

    if( !conf_file.atEnd() )
    {
        QByteArray line = conf_file.readLine();
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

    if( !conf_file.atEnd() )
    {
        QByteArray line = conf_file.readLine();
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

    if( !conf_file.atEnd() )
    {
        QByteArray line = conf_file.readLine();
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
    while( !conf_file.atEnd() )
    {
        QByteArray line = conf_file.readLine();
        if( !addCmd(line) )
        {
            qDebug() << "Error: cannot parse" << line_cnt++
                     << "th line" << conf_path;
            return;
        }
    }
    conf_file.close();

//    printConf();
}

void AjExecuter::run()
{
    AjWindow *req_win;
    AjWin32Launcher *win_launcher = new AjWin32Launcher(app_name);
    exe_name = win_launcher->getExeName();
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

bool AjExecuter::addCmd(QByteArray data)
{
    QByteArrayList data_list = data.split(' ');
    if( data_list.size()<AJ_KEY_PAR )
    {
        return false;
    }

    if( data_list[0].contains("key") )
    {
        return addKey(data_list);
    }
    else if( data_list[0].contains("path") )
    {
        if( data_list.size()<AJ_ACC_PAR )
        {
            return false;
        }
        return addAcc(data_list);
    }
    return true;
}

bool AjExecuter::addKey(QByteArrayList data_list)
{
    QString key;
    int delay, alt_key=0, ctrl_key=0, shift_key=0, meta_key=0;

    if( checkParam(data_list[0], "key") )
    {
        key = data_list[0].split('=')[1];
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
    else
    {
        return false;
    }

    if( checkParam(data_list[1], "delay") )
    {
        delay = data_list[1].split('=')[1].toInt();
    }
    else
    {
        return false;
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
    QString acc_path, cmd, acc_name;
    int delay, offset_x, offset_y, offset_id;

    if( checkParam(data_list[0], "path") )
    {
        acc_path = data_list[0].split('=')[1];
    }
    else
    {
        return false;
    }

    if( checkParam(data_list[1], "name") )
    {
        acc_name = data_list[1].split('=')[1];
    }
    else
    {
        return false;
    }

    if( checkParam(data_list[2], "cmd") )
    {
        cmd = data_list[2].split('=')[1];
    }
    else
    {
        return false;
    }

    if( checkParam(data_list[3], "delay") )
    {
        delay = data_list[3].split('=')[1].toInt();
    }
    else
    {
        return false;
    }

    if( checkParam(data_list[4], "ox") )
    {
        offset_x = data_list[4].split('=')[1].toInt();
    }
    else
    {
        return false;
    }

    if( checkParam(data_list[5], "oy") )
    {
        offset_y = data_list[5].split('=')[1].toInt();
    }
    else
    {
        return false;
    }

    if( checkParam(data_list[6], "oid") )
    {
        offset_id = data_list[6].split('=')[1].toInt();
    }
    else
    {
        return false;
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

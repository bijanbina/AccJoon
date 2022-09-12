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
        if( !addAccConf(line) )
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
        if( !addAccConf(line) )
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
    AjWin32Launcher *win_launcher = new AjWin32Launcher(app_name);
    exe_name = win_launcher->getExeName();
    qDebug() << "exe_name" << exe_name;
    AjWindow* req_win = aj_findApp(app_name, exe_name);
    if( req_win==NULL && is_open )
    {
        win_launcher->launchApp();

        /// FIXME
        /// req_win = aj_findApp(app_name, exe_name);
//        if( req_win==NULL )
//        {
//            qDebug() << "Error: cannot find window although opening it";
//            return;
//        }
    }
    else if( req_win==NULL && !is_open )
    {
        qDebug() << "Warning: cannot find window";
        return;
    }
}

bool AjExecuter::addAccConf(QByteArray data)
{
    QList<QByteArray> data_list = data.split(' ');
    if( data_list.size()<AJ_ACC_PAR )
    {
        return false;
    }
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

    AjAccOptions acc_conf;
    acc_conf.acc_path = acc_path;
    acc_conf.acc_name = acc_name;
    acc_conf.cmd = cmd;
    acc_conf.delay = delay;
    acc_conf.offset_x = offset_x;
    acc_conf.offset_y = offset_y;
    acc_conf.offset_id = offset_id;
    acc_conf_list.push_back(acc_conf);

    return true;
}

bool AjExecuter::setAppConf(QByteArray data)
{
    QList<QByteArray> data_list = data.split('=');
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
    if( !checkParam(data, "open") )
    {
        return false;
    }
    QByteArray value = data.split('=')[1];
    is_open = value.trimmed().toInt();
    return true;
}

bool AjExecuter::checkParam(QByteArray data, QString match, char sep)
{
    QList<QByteArray> data_list = data.split(sep);
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
    for( int i=0; i<acc_conf_list.size(); i++ )
    {
        AjAccOptions acc_conf = acc_conf_list[i];
        qDebug() << i << ")" << acc_conf.acc_path
                 << acc_conf.acc_name
                 << acc_conf.cmd << acc_conf.delay
                 << acc_conf.offset_x << acc_conf.offset_y
                 << acc_conf.offset_id;
    }
}

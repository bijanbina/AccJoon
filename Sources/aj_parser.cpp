#include "aj_parser.h"
#include "aj_win32.h"
#include "aj_dllgen.h"
#include "aj_win_process.h"
#include "aj_keyboard.h"
#include <QDir>

AjParser::AjParser(QString path)
{
    conf_path = path;
    parseConf();
//    printConf();
}

void AjParser::parseConf()
{
    conf_file = new QFile(conf_path);
//    qDebug() << "Working dir is" << QDir::current().path();
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

void AjParser::addAppSpec()
{
    QByteArray line = readLine();
    if( line!="" && !end_of_app )
    {
        if( !setAppConf(line) )
        {
            qDebug() << "Error: cannot parse app[" << apps.size()
                     << "] line 1" << conf_path;
            return;
        }
    }
    else
    {
        qDebug() << "Error: incomplete conf file"
                 << "- (app name) - app[" << apps.size()
                 << "]" << conf_path;
        return;
    }

    line = readLine();
    if( line!="" && !end_of_app )
    {
        if( !setOpenState(line) )
        {
            qDebug() << "Error: cannot parse app[" << apps.size()
                     << "] line 2" << conf_path;
            return;
        }
    }
    else
    {
        qDebug() << "Error: incomplete conf file"
                 << "- (open state) - app[" << apps.size()
                 << "]" << conf_path;
        return;
    }

    int line_cnt = 3;
    line = readLine();
    while( line!="" && !end_of_app )
    {
        if( !addCmd(line) )
        {
            qDebug() << "Error: cannot parse app[" << apps.size()
                     << "] line" << line_cnt << conf_path;
            return;
        }
        line = readLine();
        line_cnt++;
    }
    appendApp();
}

bool AjParser::addCmd(QByteArray data)
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

bool AjParser::addKey(QByteArrayList data_list)
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

    AjCommand key_conf;
    key_conf.key = key_int;
    key_conf.delay = delay + delay_line;
    key_conf.alt_key = alt_key;
    key_conf.ctrl_key = ctrl_key;
    key_conf.shift_key = shift_key;
    key_conf.meta_key = meta_key;
    key_conf.scripts.append(scripts_line);
    commands.push_back(key_conf);
    return true;
}

bool AjParser::addAcc(QByteArrayList data_list)
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
    acc_conf.delay = delay + delay_line;
    acc_conf.scripts.append(scripts_line);
    acc_conf.offset_x = offset_x;
    acc_conf.offset_y = offset_y;
    acc_conf.offset_id = offset_id;
    acc_conf.key = -1;
    commands.push_back(acc_conf);
    return true;
}

bool AjParser::setAppConf(QByteArray data)
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
        start_scripts = scripts_line;
        return true;
    }
    else
    {
        return false;
    }
}

bool AjParser::setOpenState(QByteArray data)
{
    is_open = 0;
    open_delay = 0;
    workspace = 0;
    open_scripts.clear();
    pcheck = "";
    args = "";

    // args with cotation
    if( data.contains("args") )
    {
        if( data.contains("\"") )
        {
            int first_cot = data.indexOf('\"');
            int last_cot = data.lastIndexOf('\"');
            if( first_cot>0 && last_cot>first_cot )
            {
                args = data.mid(first_cot+1,
                                last_cot-first_cot-1);
                int arg_index = data.indexOf("args");
                data.remove(arg_index, last_cot-arg_index+1);
            }
        }
    }

    QByteArrayList data_list = data.split(' ');
    data_list.removeAll("");
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
        // args without cotation
        else if( checkParam(data_list[i], "args") )
        {
            QByteArray value = data_list[i].split('=')[1];
            args = value.trimmed();
        }
        else
        {
            return false;
        }
    }
    open_scripts = scripts_line;
    open_delay += delay_line;
    return true;
}

void AjParser::appendApp()
{
    AjAppOptions app;
    app.app_name = app_name;
    app.app_func = app_func;
    app.is_open = is_open;
    app.start_delay = start_delay;
    app.open_delay = open_delay;
    app.start_scripts = start_scripts;
    app.open_scripts = open_scripts;
    app.commands = commands;
    app.pcheck = pcheck;
    app.workspace = workspace;
    app.args = args;
    apps.push_back(app);

    commands.clear();
    app_name.clear();
    app_func.clear();
    pcheck.clear();
    start_scripts.clear();
    open_scripts.clear();
    workspace = 0;
    is_open = 0;
    start_delay = 0;
    open_delay = 0;
}

QByteArray AjParser::readLine()
{
    delay_line = 0;
    scripts_line.clear();
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
        else if( line.startsWith("lua") )
        {
            QByteArrayList words = line.split(' ');
            int delay = 0;
            bool correct_flag = true;
            QString lua_path;
            for( int i=0; i<words.size(); i++)
            {
                if( words[i].contains("lua") )
                {
                    QByteArrayList word_list = line.split('=');
                    if( word_list.size()>1 )
                    {
                        lua_path = word_list[1].trimmed();
                    }
                    else
                    {
                        correct_flag = false;
                    }
                }
                else if( words[i].contains("delay") )
                {
                    QByteArrayList word_list = line.split('=');
                    if( word_list.size()>1 )
                    {
                        delay = word_list[1].trimmed().toInt();
                    }
                    else
                    {
                        correct_flag = false;
                    }
                }
                else
                {
                    correct_flag = false;
                }
            }
            if( correct_flag )
            {
                AjLuaInfo lua_info;
                lua_info.delay = delay_line + delay;
                lua_info.path = lua_path;
                scripts_line.append(lua_info);
                delay_line = 0;
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

bool AjParser::checkParam(QByteArray data, QString match, char sep)
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

void AjParser::printConf()
{
    for( int j=0; j<apps.size(); j++ )
    {
        qDebug() << "--------" << apps[j].app_func
                 << apps[j].app_name << "-------"
                 << "open:" << apps[j].is_open
                 << "check:" << apps[j].pcheck
                 << "workspace:" << apps[j].workspace
                 << "start-delay:" << apps[j].start_delay
                 << "open-delay:" << apps[j].open_delay
                 << "args:" << apps[j].args;
        for( int i=0; i<apps[j].start_scripts.size(); i++ )
        {
            qDebug() << "start_lua:"
                     << apps[j].start_scripts[i].path
                     << apps[j].start_scripts[i].delay;
        }
        for( int i=0; i<apps[j].open_scripts.size(); i++ )
        {
            qDebug() << "open_lua:"
                     << apps[j].open_scripts[i].path
                     << apps[j].open_scripts[i].path;
        }

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
            for( int k=0; k<acc_conf.scripts.size(); k++ )
            {
                qDebug() << "start_lua:"
                         << acc_conf.scripts[k].path
                         << acc_conf.scripts[k].delay;
            }
        }
    }
}

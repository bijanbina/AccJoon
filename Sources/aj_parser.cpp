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
        AjAppOptions new_app;
        parseApp(new_app);
    }
    conf_file->close();
}

void AjParser::parseApp(AjAppOptions app)
{
    QString line = readLine();
    while( line.length() && !end_of_app )
    {
        int type = getType(line);
        if( type==AJ_CMD_DELAY )
        {
            parseDelayCmd(&app, line);
        }
        else if( type==AJ_CMD_SCRIPT )
        {
            parseLuaCmd(&app, line);
        }
        else if( type==AJ_CMD_KEY )
        {
            parseKeyCmd(&app, line);
        }
        else if( type==AJ_CMD_ACC )
        {
            parseAccCmd(&app, line);
        }
        else if( type==AJ_CMD_OPEN )
        {
            parseOpenCmd(&app, line);
        }
        else if( type==AJ_CMD_APP )
        {
            if( app.app_name.length() ||
                app.commands.size()>0 )
            {
                apps.append(app);
            }
            AjAppOptions new_app;
            parseAppCmd(&new_app, line);
            parseApp(new_app);
            return;
        }
        line = readLine();
    }
    if( app.app_name.length() ||
        app.commands.size()>0 )
    {
        apps.append(app);
    }
}

void AjParser::parseAppCmd(AjAppOptions *app, QString data)
{
    QStringList data_list = data.split('=');
    if( data_list.size()<2 )
    {
        return;
    }
    app->app_func = data_list[0].trimmed();
    app->app_name = data_list[1].trimmed();
}

void AjParser::parseDelayCmd(AjAppOptions *app, QString line)
{
    QStringList word_list = line.split("=", QString::SkipEmptyParts);
    int delay;
    if( word_list.size()>1 )
    {
        delay = word_list[1].trimmed().toInt();
    }
    else
    {
        return;
    }
    AjCommand cmd;
    cmd.type = AJ_CMD_DELAY;
    cmd.delay = delay;
    app->commands.push_back(cmd);
}

void AjParser::parseLuaCmd(AjAppOptions *app, QString line)
{
    QStringList words = line.split(' ', QString::SkipEmptyParts);
    int delay = 0;
    QString lua_path;
    for( int i=0; i<words.size(); i++)
    {
        if( words[i].contains("lua") )
        {
            QStringList word_list = line.split('=');
            if( word_list.size()>1 )
            {
                lua_path = word_list[1].trimmed();
            }
            else
            {
                return;
            }
        }
        else if( words[i].contains("delay") )
        {
            QStringList word_list = line.split('=');
            if( word_list.size()>1 )
            {
                delay = word_list[1].trimmed().toInt();
            }
            else
            {
                return;
            }
        }
        else
        {
            return;
        }
    }

    AjCommand cmd;
    cmd.type = AJ_CMD_SCRIPT;
    cmd.delay = delay;
    cmd.path = lua_path;
    app->commands.push_back(cmd);
}

void AjParser::parseKeyCmd(AjAppOptions *app, QString line)
{
    QString key = "";
    int key_int = -1;
    int delay=0, alt_key=0, ctrl_key=0, shift_key=0, meta_key=0;

    QStringList word_list = line.trimmed().split(" ");

    for( int i=0; i<word_list.size(); i++)
    {
        if( checkParam(word_list[i], "key") )
        {
            key = word_list[i].split('=')[1];
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
                    return;
                }
            }
        }
        else if( checkParam(word_list[i], "delay") )
        {
            delay = word_list[i].split('=')[1].toInt();
        }
        else
        {
            return;
        }
    }

    AjCommand key_conf;
    key_conf.type = AJ_CMD_KEY;
    key_conf.key = key_int;
    key_conf.delay = delay;
    key_conf.alt_key = alt_key;
    key_conf.ctrl_key = ctrl_key;
    key_conf.shift_key = shift_key;
    key_conf.meta_key = meta_key;
    app->commands.push_back(key_conf);
    return;
}

void AjParser::parseAccCmd(AjAppOptions *app, QString line)
{
    QString acc_path, cmd="L", acc_name="";
    int delay=0, offset_x=0, offset_y=0, offset_id=0;

    QStringList word_list = line.trimmed().split(" ");

    for( int i=0; i<word_list.size(); i++ )
    {
        if( checkParam(word_list[i], "path") )
        {
            acc_path = word_list[i].split('=')[1];
        }
        else if( checkParam(word_list[i], "name") )
        {
            acc_name = word_list[i].split('=')[1];
        }
        else if( checkParam(word_list[i], "cmd") )
        {
            cmd = word_list[i].split('=')[1];
        }
        else if( checkParam(word_list[i], "delay") )
        {
            delay = word_list[i].split('=')[1].toInt();
        }
        else if( checkParam(word_list[i], "ox") )
        {
            offset_x = word_list[i].split('=')[1].toInt();
        }
        else if( checkParam(word_list[i], "oy") )
        {
            offset_y = word_list[i].split('=')[1].toInt();
        }
        else if( checkParam(word_list[i], "oid") )
        {
            offset_id = word_list[i].split('=')[1].toInt();
        }
        else
        {
            return;
        }
    }

    AjCommand acc_conf;
    acc_conf.type = AJ_CMD_ACC;
    acc_conf.acc_path = acc_path;
    acc_conf.acc_name = acc_name;
    acc_conf.action = cmd;
    acc_conf.delay = delay;
    acc_conf.offset_x = offset_x;
    acc_conf.offset_y = offset_y;
    acc_conf.offset_id = offset_id;
    acc_conf.key = -1;
    app->commands.push_back(acc_conf);
    return;
}

void AjParser::parseOpenCmd(AjAppOptions *app, QString line)
{
    int is_open = 0, open_delay = 0, workspace = 0;
    QString pcheck, args;

    // args with cotation
    if( line.contains("args") )
    {
        if( line.contains("\"") )
        {
            int first_cot = line.indexOf('\"');
            int last_cot = line.lastIndexOf('\"');
            if( first_cot>0 && last_cot>first_cot )
            {
                args = line.mid(first_cot+1,
                                last_cot-first_cot-1);
                int arg_index = line.indexOf("args");
                line.remove(arg_index, last_cot-arg_index+1);
            }
        }
    }

    QStringList word_list = line.split(' ', QString::SkipEmptyParts);
    if( word_list.size()<1 )
    {
        return;
    }

    for( int i=0 ; i<word_list.size() ; i++ )
    {
        if( checkParam(word_list[i], "open") )
        {
            QString value = word_list[i].split('=')[1];
            is_open = value.trimmed().toInt();
        }
        else if( checkParam(word_list[i], "delay") )
        {
            QString value = word_list[i].split('=')[1];
            open_delay = value.trimmed().toInt();
        }
        else if( checkParam(word_list[i], "workspace") )
        {
            QString value = word_list[i].split('=')[1];
            workspace = value.trimmed().toInt();
        }
        else if( checkParam(word_list[i], "check") )
        {
            QString value = word_list[i].split('=')[1];
            pcheck = value.trimmed();
        }
        // args without cotation
        else if( checkParam(word_list[i], "args") )
        {
            QString value = word_list[i].split('=')[1];
            args = value.trimmed();
        }
        else
        {
            return;
        }
    }
    app->args = args;
    app->pcheck = pcheck;
    app->workspace = workspace;
    app->open_delay = open_delay;
    app->is_open = is_open;
}

// get command type from line
int AjParser::getType(QString line)
{
    line = line.toLower().trimmed();
    if( line.startsWith("lua") )
    {
        return AJ_CMD_SCRIPT;
    }
    else if( line.startsWith("key") )
    {
        return AJ_CMD_KEY;
    }
    else if( line.startsWith("path") )
    {
        return AJ_CMD_ACC;
    }
    else if( line.startsWith("delay") )
    {
        return AJ_CMD_DELAY;
    }
    else if( line.startsWith("shortcut") ||
             line.startsWith("pid") ||
             line.startsWith("pname") ||
             line.startsWith("title") )
    {
        return AJ_CMD_APP;
    }
    else if( line.startsWith("open") )
    {
        return AJ_CMD_OPEN;
    }
    else
    {
        return 0;
    }
}

QString AjParser::readLine()
{
    end_of_app = false;
    while( !conf_file->atEnd() )
    {
        QString line = conf_file->readLine().trimmed();
        if( line.startsWith("--") )
        {
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

bool AjParser::checkParam(QString data, QString match, char sep)
{
    QStringList data_list = data.split(sep);
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
                 << "open-delay:" << apps[j].open_delay
                 << "args:" << apps[j].args << apps[j].commands.size();

        for( int i=0; i<apps[j].commands.size(); i++ )
        {
            AjCommand cmd_conf = apps[j].commands[i];
            if( cmd_conf.type==AJ_CMD_KEY )
            {
                qDebug() << i << ") KEY:" << cmd_conf.key
                         << cmd_conf.alt_key << cmd_conf.ctrl_key
                         << cmd_conf.shift_key << cmd_conf.meta_key
                         << cmd_conf.delay;
            }
            else if( cmd_conf.type==AJ_CMD_ACC )
            {
                qDebug() << i << ") ACC:" << cmd_conf.acc_path
                         << cmd_conf.acc_name << cmd_conf.action
                         << cmd_conf.offset_x << cmd_conf.offset_y
                         << cmd_conf.offset_id << cmd_conf.delay;
            }
            else if( cmd_conf.type==AJ_CMD_SCRIPT )
            {
                qDebug() << i << ") LUA:" << cmd_conf.path
                         << cmd_conf.delay;
            }
            else if( cmd_conf.type==AJ_CMD_DELAY )
            {
                qDebug() << i << ") DELAY:" << cmd_conf.delay;
            }
        }
    }
}

#include "aj_parser.h"
#include "aj_win32.h"
#include "aj_dllgen.h"
#include "aj_win_process.h"
#include "aj_keyboard.h"
#include <QDir>

AjParser::AjParser()
{
    eof = 0;
}

void AjParser::openFile(QString path)
{
    conf_path = path;
    eof = false;
    line_number = 0;
    conf_file = new QFile(conf_path);
//    qDebug() << "Working dir is" << QDir::current().path();
    if( !conf_file->open(QIODevice::ReadOnly |
                        QIODevice::Text) )
    {
        qDebug() << "Error: cannot open conf file" << conf_path;
        qDebug() << "Working dir is" << QDir::current().path();
        return;
    }
}

AjCommand AjParser::parseLine()
{
    // trimmed would remove withespace from start and end
    QString line = readLine();
    AjCommand ret;
    ret.flag_append = 0;

    if( line.length() )
    {
        if( line=="}" )
        {
            ret.command = "EOB"; // end of block "}"
        }
        else if( line.startsWith("if") )
        {
            parseCondition(line, &ret);
        }
        else if( line.startsWith("else") )
        {
            ret.command = "else";
        }
        else if( isAssignment(line) )
        {
            parseAssignment(line, &ret);
        }
        else
        {
            parseFunction(line, &ret);
        }
    }
    else if( eof )
    {
        ret.command = "EOF";
    }
    printCmd(&ret);
    return ret;
}

void AjParser::parseCondition(QString line, AjCommand *cmd)
{
    cmd->command = getCommand(line);
    int trim_len = cmd->command.length() + 1;
    line.remove(0, trim_len);
    if( line[line.length()-1]!=")" )
    {
        qDebug() << "Error 123: no \")\" found in"
                 << line_number << "line:" << line;
        return;
    }
    line.chop(1);// remove ) from end of line

    cmd->args = getCondition(line, cmd);
//    qDebug() << cmd->command << "->" << cmd->args;
    if( cmd->args.size()!=2 )
    {
        qDebug() << "Error 125: Unexpected conditional statement"
                 << ", in:" << line;
        exit(0);
    }

    for( int i=0 ; i<cmd->args.size() ; i++ )
    {
        cmd->args[i] = getVal(cmd->args[i]);
    }
    if( (cmd->command=="if_eq" &&
         cmd->args[0]==cmd->args[1]) ||
        (cmd->command=="if_ne" &&
         cmd->args[0]!=cmd->args[1]) )
    {
        cmd->command = "if_t";
    }
    else
    {
        cmd->command = "if_f";
    }
}

void AjParser::parseAssignment(QString line, AjCommand *cmd)
{
    cmd->output = getAssignOutput(line);
    int len = cmd->output.length();
    line.remove(0, len);
    len = line.indexOf("=") + 1;
    if( len>0 )
    {
        cmd->flag_append = ( line[len-1]=="+" );
    }
    line.remove(0, len);
    line = line.trimmed();

    if( isFunction(line) )
    {
        parseFunction(line, cmd);
    }
    else
    {
        cmd->command = "assign";
        cmd->args.push_back(getVal(line));
    }
}

void AjParser::parseFunction(QString line, AjCommand *cmd)
{
    cmd->command = getCommand(line);
    int trim_len = cmd->command.length() + 1;
    line.remove(0, trim_len);
    if( line[line.length()-1]!=")" )
    {
        qDebug() << "Error 123: no \")\" found in"
                 << line_number << "line:" << line;
        return;
    }
    line.chop(1);// remove ) from end of line

    cmd->args = getArguments(line);
    for( int i=0; i<cmd->args.length(); i++)
    {
        cmd->args[i] = getVal(cmd->args[i]);
    }
}

QString AjParser::getCommand(QString line)
{
    QString result;
    for( int i=0; i<line.length(); i++ )
    {
        if( line[i]=="(" )
        {
            return result;
        }
        result += line[i];
    }
    qDebug() << "Error 122: no \"(\" found in"
             << line_number << "line:" << line;
    return "";
}

QStringList AjParser::getCondition(QString line, AjCommand *cmd)
{
    QStringList arglist;
    int idq_flag = 0;//inside double qoute flag
    QString buffer;
    int len = line.length();

    for( int i=0; i<len; i++)
    {
        buffer += line[i];
        if( line[i]=="\"" )
        {
            if( idq_flag )
            {
                if( i>0 )
                {
                    if( line[i-1]!="\\" )
                    {
                        idq_flag = 0;
                    }
                }
            }
            else
            {
                idq_flag = 1;
            }
        }
        if( idq_flag==0 )
        {
            if( i>0 )
            {
                if( (line[i-1]=="=" && line[i]=="=") ||
                    (line[i-1]=="!" && line[i]=="=") )
                {
                    buffer.chop(2);
                    buffer = buffer.trimmed();
                    arglist.push_back(buffer);
                    buffer = "";
                    if( line[i-1]=="=" && line[i]=="=" )
                    {
                        cmd->command = "if_eq";
                    }
                    else
                    {
                        cmd->command = "if_ne";
                    }
                }
                else if( i==len-1 )
                {
                    buffer = buffer.trimmed();
                    arglist.push_back(buffer);
                    buffer = "";
                }
            }
        }
    }

    return arglist;
}

QStringList AjParser::getArguments(QString line)
{
    QStringList arglist;
    int idq_flag = 0;//inside double qoute flag
    QString buffer;
    int len = line.length();

    for( int i=0 ; i<len ; i++ )
    {
        buffer += line[i];
        if( line[i]=="\"" )
        {
            if( idq_flag )
            {
                if( i>0 )
                {
                    if( line[i-1]!="\\" )
                    {
                        idq_flag = 0;
                    }
                }
            }
            else
            {
                idq_flag = 1;
            }
        }
        if( idq_flag==0 )
        {
            if( line[i]=="," )
            {
                buffer.chop(1);
                buffer = buffer.trimmed();
                arglist.push_back(buffer);
                buffer = "";
            }
            else if( i==len-1 )
            {
                buffer = buffer.trimmed();
                arglist.push_back(buffer);
                buffer = "";
            }
        }
    }

    return arglist;
}

QString AjParser::getAssignOutput(QString line)
{
    QStringList word_list = line.split("=", QString::SkipEmptyParts);
    if( word_list.size()<2 )
    {
        qDebug() << "Error: Unexpected assignment statement"
                 << ", in:" << line_number << line;
        exit(0);
    }
    if( word_list[0].back()=="+" ) // for += case
    {
        word_list[0].chop(1);
    }
    return word_list[0].trimmed();
}

int AjParser::isString(QString arg)
{
    if( arg.isEmpty() )
    {
        return 1;
    }

    if( arg[0]=="\"" )
    {
        if( arg[arg.length()-1]=="\"" )
        {
            return 1;
        }
        qDebug() << "Error 124: no \" found in"
                 << line_number << "arg:" << arg;
    }
    else
    {
        return 0;
    }
    return 0;
}

int AjParser::isNumber(QString arg)
{
    if( arg.isEmpty() )
    {
        return 0;
    }
    bool ok;
    arg.toInt(&ok);
    return ok;
}

QString AjParser::readLine()
{
    eof = false;
    while( !conf_file->atEnd() )
    {
        QString line = conf_file->readLine().trimmed();
        line_number++;
        if( line.isEmpty() )
        {
            continue;
        }
        else if( line.startsWith("//") )
        {
            continue;
        }
        else if( line.startsWith("{") )
        {
            continue;
        }
        return line;
    }
    if( conf_file->atEnd() )
    {
        eof = true;
    }
    return "";
}

void AjParser::printCmd(AjCommand *cmd)
{
    qDebug() << "Cmd:" << cmd->command
             << "Output:" << cmd->output
             << "args:" << cmd->args;
}

bool AjParser::isAssignment(QString line)
{
    int len = line.length();
    for( int i=0; i<len; i++ )
    {
        if( line[i]=="\"" || line[i]=="(" )
        {
            return false;
        }
        else if( line[i]=="=" )
        {
            return true;
        }
    }
    return false;
}

bool AjParser::isFunction(QString line)
{
    int len = line.length();
    for( int i=0; i<len; i++ )
    {
        if( line[i]=="\"" )
        {
            return false;
        }
        else if( line[i]=="(" )
        {
            return true;
        }
    }
    return false;
}

QString AjParser::getVal(QString arg)
{
    if( isString(arg)==0 )
    {
        if( isNumber(arg)==0 )
        {
            arg = vars.getVal(arg);
        }
    }
    else if( arg.length() )
    {
        //remove double qoute from start and end
        arg.remove(0, 1);
        arg.chop(1);
    }
    return arg;
}

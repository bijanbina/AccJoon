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
    QString line = readLine().trimmed();
    AjCommand ret;
    line_number++;

    if( line.length() )
    {
        if( line=="}" )
        {
            ret.command = "EOB"; // end of block "}"
        }
        else if( line.contains("==") )
        {
            parseCondition(line, &ret);
        }
        else if( line.contains("=") )
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
    ret.command = ret.command.toLower();
    return ret;
}

void AjParser::parseCondition(QString line, AjCommand *cmd)
{
    QString args, command;
    QStringList arg_list;

    QStringList word_list = line.split("(", QString::SkipEmptyParts);
    if( word_list.size()!=2 )
    {
        qDebug() << "Error: Unexpected conditional statement"
                 << ", in:" << line;
        exit(0);
    }
    command = word_list[0];

    args = getArguments(line);
    word_list = args.split("==", QString::SkipEmptyParts);
    if( word_list.size()!=2 )
    {
        qDebug() << "Error: Unexpected conditional statement"
                 << ", in:" << line;
        exit(0);
    }

    for( int i=0 ; i<word_list.size() ; i++ )
    {
        arg_list.push_back(getVarValue(word_list[i]));
    }
    cmd->command = command;
    cmd->args = arg_list;
}

void AjParser::parseAssignment(QString line, AjCommand *cmd)
{
    QStringList word_list = line.split("=", QString::SkipEmptyParts);
    if( word_list.size()!=2 )
    {
        qDebug() << "Error: Unexpected assignment statement"
                 << ", in:" << line;
        exit(0);
    }
    cmd->output = word_list[0].trimmed();

    if( line.contains("(") )
    {
        parseFunction(word_list[1].trimmed(), cmd);
    }
    else
    {
        cmd->command = "assign";
        vars.addVar(cmd->output, getVarValue(word_list[1]));
    }
}

void AjParser::parseFunction(QString line, AjCommand *cmd)
{
    cmd->command = getCommand(line);
    int trim_len = cmd->command.length();
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
        if( isString(cmd->args[i])==0 )
        {
            if( isNumber(cmd->args[i])==0 )
            {
                QString value = getVarValue(cmd->args[i]);
                cmd->args[i] = value;
            }
        }
        else if( cmd->args[i].length() )
        {
            //remove double qoute from start and end
            cmd->args[i].remove(0, 1);
            cmd->args[i].chop(1);
        }
    }
}

QString AjParser::getCommand(QString line)
{
    QString result;
    for(int i=0; i<line.length(); i++)
    {
        if (line[i]=="(")
        {
            return result;
        }
        result += line[i];
    }
    qDebug() << "Error 122: no \"(\" found in"
             << line_number << "line:" << line;
    return "";
}

QStringList AjParser::getArguments(QString line)
{
    QStringList arglist;
    int idq_flag = 0;//inside double qoute flag
    QString buffer;

    for( int i=0; i<line.length(); i++)
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
        else if( idq_flag==0 )
        {
            if( line[i]=="," )
            {
                buffer.chop(1);
                buffer = buffer.trimmed();
                arglist.push_back(buffer);
                buffer = "";
            }
        }
    }

    return arglist;
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
        if( line.isEmpty() )
        {
            continue;
        }
        else if( line.startsWith("--") )
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

QString AjParser::getVarValue(QString word)
{
    word = word.trimmed();
    if( word.contains("\"") )
    {
        word.remove("\"");
    }
    else
    {
        bool conversion_ok;
        word.toInt(&conversion_ok);
        if( !conversion_ok )
        {
            word = vars.getVal(word);
        }
    }
    return word;
}

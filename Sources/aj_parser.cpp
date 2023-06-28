#include "aj_parser.h"
#include "aj_win32.h"
#include "aj_dllgen.h"
#include "aj_win_process.h"
#include "aj_keyboard.h"
#include <QDir>
#include <QRegularExpression>

AjParser::AjParser()
{
    eof = 0;
    start_t = clock();
}

AjCommand AjParser::parseLine(QString line)
{
    AjCommand ret;
    ret.flag_append = 0;

    if( isAssignment(line) )
    {
        parseAssignment(line, &ret);
    }
    else if( aj_isKeyword(line) )
    {
        aj_parseKeyword(line, &ret);
    }
    else
    {
        parseFunction(line, &ret);
    }
    printCmd(&ret);
    return ret;
}

int AjParser::parseCondition(AjCondOpt *cond)
{
    AjCommand cmd;
    QStringList args = aj_getCondition(cond->if_cond, &cmd);

    for( int i=0 ; i<args.size() ; i++ )
    {
        args[i] = getVal(args[i]);
    }

    if( (cmd.command=="if_eq" &&
         args[0]==args[1]) ||
        (cmd.command=="if_ne" &&
         args[0]!=args[1]) )
    {
        return 1;
    }

    return 0;
}

void AjParser::parseAssignment(QString line, AjCommand *cmd)
{
    cmd->output = getAssignOutput(line);
    int len = cmd->output.length();
    line.remove(0, len);
    len = line.indexOf("=") + 1;
    if( len>1 )
    {
        cmd->flag_append = ( line[len-2]=="+" );
    }
    line.remove(0, len);
    line = line.trimmed();

    if( aj_isFunction(line) )
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
    cmd->command = aj_getCommand(line);

    cmd->args = aj_getArguments(line);

    for( int i=0; i<cmd->args.length(); i++)
    {
        cmd->args[i] = getVal(cmd->args[i]);
    }
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
    qDebug() << clock()-start_t
             << cmd->command
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

QString AjParser::getVal(QString arg)
{
    if( isString(arg) )
    {
        arg.remove(0, 1);
        arg.chop(1);
        return parseString(arg);
    }
    else
    {
        //remove double qoute from start and end
        if( isNumber(arg)==0 )
        {
            arg = vars.getVal(arg);
        }
    }
    return arg;
}

QString AjParser::parseString(QString arg)
{
    QRegularExpression regex("\\$(\\d+)");
    QRegularExpressionMatch match = regex.match(arg);
    if( match.hasMatch() )
    {
        QString str_match = match.captured(1);
        int number = str_match.toInt();
        QString replace = "$" + str_match;

        arg.replace(replace, vars.getArg(number));
        return parseString(arg);
    }
    else
    {
        return arg;
    }
}

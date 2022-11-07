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
    QString line = readLine();
    AjCommand ret;

    if( line.length() )
    {
        if( line=="}" )
        {
            ret.command = "EOA"; // end of app
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
    QString args, command;
    QStringList arg_list;

    QStringList word_list = line.split("(", QString::SkipEmptyParts);
    if( word_list.size()!=2 )
    {
        qDebug() << "Error: Expect one ("
                 << ", in:" << line;
        exit(0);
    }
    command = word_list[0].trimmed();

    args = getArguments(line);

    word_list = args.split(",", QString::SkipEmptyParts);

    if( command.toLower()=="write" )
    {
        word_list[word_list.size()-1] = getVarValue(word_list.last());
    }
    for( int i=0 ; i<word_list.size() ; i++ )
    {
        arg_list.push_back(word_list[i].trimmed());
    }

    cmd->command = command;
    cmd->args = arg_list;
}

QString AjParser::getArguments(QString line)
{
    line = line.trimmed();
    if( line.back()!=")" )
    {
        qDebug() << "Error: Unexpected end of line,"
                 << "missing ')' in:" << line;
        exit(0);
    }
    line.remove(line.lastIndexOf(")"), 1);

    QStringList wordlist = line.split("(");
    if( wordlist.length()<2 )
    {
        qDebug() << "Error: missing '(' in:" << line;
        exit(0);
    }
    return wordlist[1];
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

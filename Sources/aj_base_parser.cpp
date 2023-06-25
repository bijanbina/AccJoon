#include "aj_base_parser.h"

QStringList sc_lines;

QString aj_getArgument(QString line, int arg_index)
{
    QStringList arglist = aj_getArguments(line);
    return arglist[arg_index];
}

QStringList aj_getArguments(QString line)
{
    QString gip = aj_getInPar(line);
    if( gip.isEmpty() )
    {
        return QStringList();
    }
    QStringList arglist;
    int idq_flag = 0; //inside double qoute flag
    QString buffer;

    int len = gip.length();
    for( int i=0 ; i<len ; i++ )
    {
        buffer += gip[i];
        if( gip[i]=="\"" )
        {
            if( idq_flag )
            {
                if( i>0 )
                {
                    if( gip[i-1]!="\\" )
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
            if( gip[i]=="," )
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

QStringList aj_getCondition(QString line, AjCommand *cmd)
{
    QStringList arglist;
    int idq_flag = 0; // inside double qoute flag
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

QString aj_getCommand(QString line)
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
    qDebug() << "Error 122: no \"(\" found in line:" << line;
    return "";
}

int aj_isFunction(QString line)
{
    int len = line.length();
    for( int i=0; i<len; i++ )
    {
        if( line[i]=="\"" )
        {
            return 0;
        }
        else if( line[i]=="(" )
        {
            return 1;
        }
    }
    return 0;
}

int aj_isKeyword(QString line)
{
    if( line==AJ_RET_CMD )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void aj_parseKeyword( QString line, AjCommand *cmd)
{
    if( line==AJ_RET_CMD )
    {
        cmd->command = line;
        cmd->flag_append = 0;
    }
}

int aj_isConditional(QString line)
{
    if( aj_isFunction(line)==0 )
    {
        return 0;
    }
    QString cmd = aj_getCommand(line);

    if( cmd=="if" || cmd=="else if" ||
        cmd=="else" || cmd=="while" ||
        cmd=="for" )
    {
        return 1;
    }
    return 0;
}

void aj_openScript(QString sc_path)
{
    QFile sc_file(sc_path);
    if( !sc_file.open(QIODevice::ReadOnly |
                        QIODevice::Text) )
    {
        qDebug() << "Error: cannot open script file" << sc_path;
        qDebug() << "Working dir is" << QDir::current().path();
        return;
    }
    sc_lines.clear();
    while( !sc_file.atEnd() )
    {
        QString line = sc_file.readLine().trimmed();
        sc_lines << line;
    }
    sc_file.close();
}

// get inside of parantheses
// ex: app("Qt") -> "Qt"
QString aj_getInPar(QString line)
{
    // remove before (
    QStringList line_split = line.split("(");
    if( line_split.size()<2 )
    {
        qDebug() << "Error split exceed, in line:" << line;
        return "";
    }
    // remove )
    line = line_split[1];
    if( line.back()!=")" )
    {
        qDebug() << "Error in line:" << line;
        return "";
    }
    line.chop(1);
    return line;
}

// SCRIPT LINES FUNCTIONS
QString aj_getScLine(int index)
{
    // lines for index is different from editor line by 1
    index--;
    if( index<sc_lines.size() && index>=0 )
    {
        return sc_lines[index];
    }
    else
    {
        qDebug() << "Error: index not in range, index:" << index;
        exit(0);
    }
}

int aj_getScLineSize()
{
    return sc_lines.size();
}

// get correspondant closed curly
int aj_findEnd(int line_number)
{
    // lines for index is different from editor line by 1
    line_number--;

    int len = aj_getScLineSize();
    int curly_counter = 1;
    while( line_number<len )
    {
        if( sc_lines[line_number]=="{" )
        {
            curly_counter++;
        }
        else if( sc_lines[line_number]=="}" )
        {
            curly_counter--;
        }
        if( curly_counter==0 )
        {
            // lines for index is different from editor line by 1
            return line_number+1;
        }
        line_number++;
    }
    return -1;
}

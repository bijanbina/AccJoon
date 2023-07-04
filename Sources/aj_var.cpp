#include "aj_var.h"
#include "aj_keyboard.h"

void AjVar::setVar(QString name, QString value)
{
    int len = vars_name.size();
    for( int i=0 ; i<len ; i++ )
    {
        if( vars_name[i]==name )
        {
            vars_value[i] = value;
            return;
        }
    }
    vars_name.push_back(name);
    vars_value.push_back(value);
}

QString AjVar::getVal(QString name)
{
    int len = vars_name.size();
    for( int i=0; i<len; i++ )
    {
        if( vars_name[i]==name )
        {
            return vars_value[i];
        }
    }

    qDebug() << "Warning: Coudn't find var" << name;
    return "";
}

void AjVar::setArg(int id, QString val)
{
    int len = args.length();
    if( id>=len )
    {
        args.resize(id+1);
    }
    args[id] = val;
}

QString AjVar::getArg(int id)
{
    id--; // args start from 1 -> $1 $2 ...
    int len = args.length();
    if( id<len && id>=0 )
    {
        return args[id];
    }
    else
    {
        qDebug() << "Error: you didnt enter argument" << id;
        return "";
    }
}

void AjVar::printVars()
{
    int len = vars_name.length();
    for( int i=0 ; i<len ; i++ )
    {
        qDebug() << vars_name[i] << vars_value[i];
    }
}

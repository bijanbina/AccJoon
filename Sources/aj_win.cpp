#include "aj_win.h"
#include "aj_keyboard.h"

void AjVar::addVar(QString name, QString value)
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
    return "";
}

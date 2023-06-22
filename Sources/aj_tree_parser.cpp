#include "aj_tree_parser.h"
#include "aj_base_parser.h"
#include <QDir>

AjTreeParser::AjTreeParser(QString path)
{
    sc_path = path;
    aj_openScript(sc_path);
    line_cntr = 0;
    line_size = aj_getScLineSize();
}

void AjTreeParser::parseApps()
{
    while( line_cntr<line_size )
    {
        line_cntr++;
        QString line = aj_getScLine(line_cntr);

        if( line.length()==0 )
        {
            continue;
        }
        else if( aj_isFunction(line) )
        {
            QString command = aj_getCommand(line);
            if( command==AJ_APP_CMD )
            {
                AjAppOpt *app = createApp(line);
                if( app!=NULL )
                {
                    apps.push_back(app);
                }
                else
                {
                    return;
                }
            }
        }
        else
        {
            qDebug() << "Error in line" << line_cntr
                     << "of file" << sc_path
                     << "content:" << line;
            apps.clear();
            return;
        }
    }
    checkApps();
}

AjAppOpt* AjTreeParser::createApp(QString line)
{
    QStringList app_args = aj_getArguments(line);
    if( app_args.size()==0 )
    {
        qDebug() << "Error: application needs appname" << line_cntr
                 << "->" << line;
        return NULL;
    }

    AjAppOpt *app = new AjAppOpt;
    app->app_name = app_args[0];
    if( app_args.size()>1 )
    {
        app->win_title = app_args[1];
    }

    // next line after curly, supposed curly is next line of app(..)
    line_cntr = line_cntr + 2;
    app->start_line = line_cntr;
    int end_index = aj_findEnd(line_cntr);
    if( end_index<0 )
    {
        qDebug() << "Error close curly not found, started" << line_cntr-1
                 << "of file" << sc_path;
        return NULL;
    }
    line_cntr = end_index;
    // app code block ends at the line before closed curly
    app->end_line = end_index - 1;
    return app;
}

// remove buggy apps
void AjTreeParser::checkApps()
{
    int len = apps.length();
    for( int i=0 ; i<len ; i++ )
    {
        if( apps[i]->start_line < 3 ||
            apps[i]->end_line <= apps[i]->start_line )
        {
            apps.remove(i);
            len--;
            i--;
        }
    }
}

void AjTreeParser::printApps()
{
    int len = apps.length();
    for( int i=0 ; i<len ; i++ )
    {
        QString args;
        qDebug() << "APP" << i << "-> "
                 << apps[i]->app_name << apps[i]->win_title
                 << "1st line" << apps[i]->start_line
                 << "last line" << apps[i]->end_line;
    }
}

void AjTreeParser::parseConditions()
{
    line_cntr = 0;
    int len = apps.size();
    for( int i=0 ; i<len ; i++ )
    {
        parseConditions(apps[i]);
    }
}

void AjTreeParser::parseConditions(AjAppOpt *app)
{
    line_cntr = app->start_line - 1;
    while( line_cntr<line_size )
    {
        line_cntr++;
        QString line = aj_getScLine(line_cntr);
        if( line.length()==0 )
        {
           continue;
        }
        else if( aj_isConditional(line) )
        {
            AjCondOpt *condition = createCondition(line);
            if( condition!=NULL )
            {
               app->conditions.push_back(condition);
            }
            else
            {
               return;
            }
        }
    }
}

AjCondOpt* AjTreeParser::createCondition(QString line)
{
    AjCommand *dummy_cmd = new AjCommand;
    QStringList arglist = aj_getCondition(line, dummy_cmd);
    if( arglist.length()==0 )
    {
        qDebug() << "Error in line" << line_cntr
                 << "of file" << sc_path
                 << "content:" << line;
        return NULL;
    }

    AjCondOpt *new_condition = new AjCondOpt;
    new_condition->args = arglist;
    // next line after curly, supposed curly is next line of if(..)
    line_cntr += 2;
    new_condition->first_line = line_cntr;

    int end_index = aj_findEnd(line_cntr);
    if( end_index<0 )
    {
        qDebug() << "Error close curly not found, started" << line_cntr-1
                 << "of file" << sc_path;
        return NULL;
    }
    // reading from file continues from line after closed curly
    line_cntr = end_index;
    // app code block ends at the line before closed curly
    new_condition->end_line = end_index - 1;
    return new_condition;
}

void AjTreeParser::printConditions()
{
    int len = apps.size();
    for( int i=0 ; i<len ; i++ )
    {
        QVector<AjCondOpt *> conditions = apps[i]->conditions;
        int cond_len = conditions.size();
        for( int j=0 ; j<cond_len ; j++ )
        {
            QString args;
            int arg_size = conditions[j]->args.size();
            for( int k=0 ; k<arg_size ; k++)
            {
                args += "arg " + QString::number(k) + ": " +
                        conditions[j]->args[k] + " ";
            }
            qDebug() << apps[i]->app_name << "-" << j << ")"
                     << args << "1st line:"
                     << conditions[j]->first_line << "end line"
                     << conditions[j]->end_line;

        }
    }
}

#include "aj_tree_parser.h"
#include <QDir>

AjTreeParser::AjTreeParser(QString path)
{
    sc_path = path;
    aj_openScript(sc_path);
    line_size = aj_getScLineSize();
}

QVector<AjApp *> AjTreeParser::parseApps()
{
    return parseObject(AJ_APP_CMD);
}

QVector<AjApp *> AjTreeParser::parseNpipes()
{
    return parseObject(AJ_NP_CMD);
}

QVector<AjApp *> AjTreeParser::parseObject(QString obj_name)
{
    line_cntr = 0;
    QVector<AjApp *> objs;
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
            if( command==obj_name )
            {
                AjApp *obj = createApp(line);
                if( obj!=NULL )
                {
                    objs.push_back(obj);
                }
                else
                {
                    return objs;
                }
            }
            else
            {
                skipToNext();
            }
        }
        else
        {
            qDebug() << "Error in line" << line_cntr
                     << "of file" << sc_path
                     << "content:" << line;
            objs.clear();
            return objs;
        }
    }
    checkApps(objs);
    return objs;
}

AjApp* AjTreeParser::createApp(QString line)
{
    QStringList app_args = aj_getArguments(line);
    if( app_args.size()==0 )
    {
        qDebug() << "Error: application needs appname" << line_cntr
                 << "->" << line;
        return NULL;
    }

    AjApp *app = new AjApp;
    app->app_name = app_args[0].remove("\"");
    if( app_args.size()>1 )
    {
        app->win_title = app_args[1].remove("\"");
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

void AjTreeParser::skipToNext()
{
    line_cntr++;
    QString line = aj_getScLine(line_cntr);
    if( line.trimmed()=="{" )
    {
        int end_index = aj_findEnd(line_cntr+1);
        line_cntr = end_index;
    }
    else
    {
        qDebug() << "Error 188: Cannot parse script in line"
                 << line_cntr-1;
    }
}

// remove buggy apps
void AjTreeParser::checkApps(QVector<AjApp *> apps)
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

void AjTreeParser::parseConditions(QVector<AjApp *> apps)
{
    line_cntr = 0;
    int len = apps.size();
    for( int i=0 ; i<len ; i++ )
    {
        parseConditions(apps[i]);
    }
}

void AjTreeParser::parseConditions(AjApp *app)
{
    line_cntr = app->start_line - 1;
    while( line_cntr<app->end_line )
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
                AjLine *line = new AjLine;
                line->cond = condition;
                app->lines.push_back(line);
            }
            else
            {
                return;
            }
        }
        else
        {
            AjLine *line_buf = new AjLine;
            line_buf->cond = NULL;
            line_buf->line = line;
            app->lines.push_back(line_buf);
        }
    }
}

AjCondOpt* AjTreeParser::createCondition(QString line)
{
    QString gip = aj_getInPar(line);
    if( gip.length()==0 )
    {
        qDebug() << "Error in line" << line_cntr
                 << "of file" << sc_path
                 << "content:" << line;
        return NULL;
    }

    AjCondOpt *condition = new AjCondOpt;
    condition->if_cond = gip;
    // next line after curly, supposed curly is next line of if(..)
    line_cntr += 2;
    condition->if_start = line_cntr;

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
    condition->if_end = end_index - 1;
    createElseIf(condition);
    return condition;
}

int AjTreeParser::createElseIf(AjCondOpt *condition)
{
    line_cntr++;
    QString line = aj_getScLine(line_cntr);
    if( line.startsWith("else if") )
    {
        line = aj_getInPar(line);
        if( line.length()==0 )
        {
            qDebug() << "Error in line" << line_cntr
                     << "of file" << sc_path
                     << "content:" << line;
            return NULL;
        }

        condition->elif_cond << line;
        // next line after curly, supposed curly is next line of if(..)
        line_cntr += 2;
        condition->elif_start << line_cntr;

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
        condition->elif_end << end_index - 1;
        createElseIf(condition);
    }
    else if( line.startsWith("else") )
    {
        // next line after curly, supposed curly is next line of if(..)
        line_cntr += 2;
        condition->else_start = line_cntr;

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
        condition->else_end = end_index - 1;
    }
    else
    {
        line_cntr = condition->if_end + 1;
    }
    return 0;
}

void AjTreeParser::printApps(QVector<AjApp *> apps)
{
    int len = apps.length();
    for( int i=0 ; i<len ; i++ )
    {
        qDebug() << "APP" << i << "-> "
                 << apps[i]->app_name << apps[i]->win_title
                 << "1st line" << apps[i]->start_line
                 << "last line" << apps[i]->end_line;
        int lines_size = apps[i]->lines.size();
        for( int j=0 ; j<lines_size ; j++ )
        {
            qDebug() << "line[" + QString::number(j) + "]"
                     << apps[i]->lines[j]->line;
        }
    }
}

//void AjTreeParser::printConditions(QVector<AjAppOpt *> apps)
//{
//    int len = apps.size();
//    for( int i=0 ; i<len ; i++ )
//    {
//        QVector<AjCondOpt *> conditions = apps[i]->conditions;
//        int cond_len = conditions.size();
//        for( int j=0 ; j<cond_len ; j++ )
//        {
//            QString args;
//            int arg_size = conditions[j]->cond.size();
//            for( int k=0 ; k<arg_size ; k++)
//            {
//                args += "arg " + QString::number(k) + ": " +
//                        conditions[j]->cond[k] + " ";
//            }
//            qDebug() << apps[i]->app_name << "-" << j << ")"
//                     << args << "1st line:"
//                     << conditions[j]->first_line << "end line"
//                     << conditions[j]->end_line;

//        }
//    }
//}

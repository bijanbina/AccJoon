#ifndef AJ_CONFPARSER_H
#define AJ_CONFPARSER_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "aj_launcher.h"
#include "aj_win.h"

typedef struct AjCmdOptions
{
    bool is_remote;
    bool is_open;
    QString conf_path;
    QString app_name;
    QString app_func;
    AjCommand cmd;
}AjCmdOptions;

class AjParser
{
public:
    AjParser(QString conf_path);

    QVector<AjAppOptions> apps;

private:
    void parseConf();
    void parseApp(AjAppOptions app);
    QString readLine();
    void parseAppCmd(AjAppOptions *app, QString data);
    void parseOpenCmd(AjAppOptions *app, QString line);
    void parseAccCmd(AjAppOptions *app, QString line);
    void parseKeyCmd(AjAppOptions *app, QString line);
    void parseDelayCmd(AjAppOptions *app, QString line);
    void parseLuaCmd(AjAppOptions *app, QString line);
    bool checkParam(QString data, QString match, char sep='=');
    void printConf();
    int getType(QString line);

    QFile *conf_file;
    QString conf_path;
    bool end_of_app; // end of app specification in conf
    bool end_of_file;
};

#endif // AJCONFPARSER_H

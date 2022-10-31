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
    void parseLine(AjAppOptions *app);
    bool atEnd(){ return end_of_file; }

private:
    void parseApp(AjAppOptions app);
    QString readLine();
    void parseAppCmd(QString data);
    void parseOpenCmd(QString line);
    void parseAccCmd(QString line);
    void parseKeyCmd(QString line);
    void parseDelayCmd(QString line);
    void parseLuaCmd(QString line);
    bool checkParam(QString data, QString match, char sep='=');
    void printConf();
    void clearCurrentApp();
    int getType(QString line);

    QFile *conf_file;
    QString conf_path;
    bool end_of_app; // end of app specification in conf
    bool end_of_file;
    AjAppOptions current_app;
};

#endif // AJCONFPARSER_H

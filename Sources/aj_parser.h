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
    int offset_x;
    int offset_y;
    int offset_id;
    QString conf_path;
    QString app_name;
    QString app_func;
    QString acc_path;
    QString acc_name;
    QString action;
}AjCmdOptions;

class AjParser
{
public:
    AjParser(QString conf_path);
    AjCommand parseLine();
    bool atEnd(){ return end_of_file; }

    AjVar vars;
    int condition_flag;

private:
    QString readLine();
    void parseCondition(QString line, AjCommand *cmd);
    void parseAssignment(QString line, AjCommand *cmd);
    void parseFunction(QString line, AjCommand *cmd);
    void printCmd(AjCommand *cmd);
    QString getArguments(QString line);
    QString getVarValue(QString word);

    QFile *conf_file;
    QString conf_path;
    bool end_of_file;
};

#endif // AJCONFPARSER_H

#ifndef AJ_CONFPARSER_H
#define AJ_CONFPARSER_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "aj_application.h"
#include "aj_var.h"
#include "aj_base_parser.h"

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
    AjParser();
    AjCommand parseLine(QString line);
    int parseCondition(AjCondOpt *cond);

    AjVar vars;
    int eof; //End of file
    int condition_flag;
    int line_number;

private:
    QString readLine();
    void parseAssignment(QString line, AjCommand *cmd);
    void parseFunction(QString line, AjCommand *cmd);
    QString parseString(QString arg);
    void printCmd(AjCommand *cmd);
    bool isAssignment(QString line);
    bool isFunction(QString line);
    QString getAssignOutput(QString line);
    QString getVal(QString arg);

    int isString(QString arg);
    int isNumber(QString arg);

    QFile *conf_file;
    QString conf_path;
    clock_t start_t;
};

#endif // AJCONFPARSER_H

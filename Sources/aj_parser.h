#ifndef AJ_CONFPARSER_H
#define AJ_CONFPARSER_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "aj_shortcut.h"
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
    AjParser();
    void openFile(QString path);
    AjCommand parseLine();

    AjVar vars;
    int eof; //End of file
    int condition_flag;
    int line_number;

private:
    QString readLine();
    void parseCondition(QString line, AjCommand *cmd);
    void parseAssignment(QString line, AjCommand *cmd);
    void parseFunction(QString line, AjCommand *cmd);
    void printCmd(AjCommand *cmd);
    bool isAssignment(QString line);
    bool isFunction(QString line);
    QStringList getArguments(QString line);
    QStringList getCondition(QString line);
    QString getAssignOutput(QString line);
    QString getVarValue(QString arg);

    QString getCommand(QString line);
    int isString(QString arg);
    int isNumber(QString arg);

    QFile *conf_file;
    QString conf_path;
};

#endif // AJCONFPARSER_H

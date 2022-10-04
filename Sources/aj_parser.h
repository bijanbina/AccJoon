#ifndef AJ_CONFPARSER_H
#define AJ_CONFPARSER_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "aj_win32_launcher.h"
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
    void addAppSpec();
    QByteArray readLine();
    bool setAppConf(QByteArray data);
    bool setOpenState(QByteArray data);
    bool addCmd(QByteArray data);
    bool addAcc(QByteArrayList data_list);
    bool addKey(QByteArrayList data_list);
    bool checkParam(QByteArray data, QString match, char sep='=');
    void appendApp();
    void printConf();

    QString app_name;
    QString app_func;
    QString pcheck; // process check
    int workspace;
    int is_open;
    int start_delay; // before opening application
    int open_delay; // after opening application
    QVector<AjCommand> commands;

    QFile *conf_file;
    QString conf_path;
    int delay_line;
    bool end_of_app; // end of app specification in conf
    bool end_of_file;
};

#endif // AJCONFPARSER_H

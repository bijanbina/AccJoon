#ifndef AJCONFPARSER_H
#define AJCONFPARSER_H

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

typedef struct AjAppOptions{
    QString app_name;
    QString app_func;
    QString pcheck; // process check
    int workspace;
    int is_open;
    int open_delay;
    int start_delay;
    QVector<AjCommand> commands;
}AjAppOptions;

class AjExecuter
{
public:
    AjExecuter(QString conf_path);
    void run();

private:
    void parseConf();
    void addAppSpec();
    void runApp(int i);
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
    QVector<AjAppOptions> apps;
};

#endif // AJCONFPARSER_H

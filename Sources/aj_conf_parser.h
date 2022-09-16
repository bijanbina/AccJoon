#ifndef AJCONFPARSER_H
#define AJCONFPARSER_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "aj_win32_launcher.h"
#include "aj_win.h"

#define AJ_ACC_PAR  7
#define AJ_KEY_PAR  2
#define AJ_OPEN_PAR 2

typedef struct AjCmdOptions
{
    bool is_remote;
    bool is_open;
    QString conf_path;
    QString app_name;
    QString app_func;
    AjCommand cmd;
}AjCmdOptions;

class AjExecuter
{
public:
    AjExecuter(QString conf_path);
    void run();

private:
    bool setAppConf(QByteArray data);
    bool setOpenState(QByteArray data);
    bool addCmd(QByteArray data);
    bool addAcc(QByteArrayList data_list);
    bool addKey(QByteArrayList data_list);
    bool checkParam(QByteArray data, QString match, char sep='=');
    void printConf();

    QString app_name;
    QString exe_name;
    QString app_func;
    int is_open;
    int open_delay;
    QVector<AjCommand> commands;
};

#endif // AJCONFPARSER_H

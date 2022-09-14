#ifndef AJCONFPARSER_H
#define AJCONFPARSER_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "aj_win32_launcher.h"

#define AJ_ACC_PAR 7

typedef struct AjAccOptions
{
    QString acc_path;
    QString cmd;
    QString acc_name;
    int offset_x;
    int offset_y;
    int offset_id;
    int delay;
}AjAccOptions;

typedef struct AjCmdOptions
{
    bool is_remote;
    bool is_open;
    QString conf_path;
    QString app_name;
    QString app_func;
    AjAccOptions cmd;
}AjCmdOptions;

class AjExecuter
{
public:
    AjExecuter(QString conf_path);
    void run();

private:
    bool setAppConf(QByteArray data);
    bool setOpenState(QByteArray data);
    bool addAccConf(QByteArray data);
    bool checkParam(QByteArray data, QString match, char sep='=');
    void printConf();

    QString app_name;
    QString exe_name;
    QString app_func;
    int is_open;
    QVector<AjAccOptions> acc_conf_list;
};

#endif // AJCONFPARSER_H

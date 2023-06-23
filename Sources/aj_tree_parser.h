#ifndef AJPREPARSER_H
#define AJPREPARSER_H

#include <QFile>
#include <QDebug>
#include "aj_base_parser.h"

class AjTreeParser
{
public:
    AjTreeParser(QString path);
    QVector<AjAppOpt *> parseApps();
    void parseConditions(QVector<AjAppOpt *> apps);
    void printApps(QVector<AjAppOpt *> apps);
    void printConditions(QVector<AjAppOpt *> apps);
    void parseConditions(AjAppOpt *shortcut);

private:

    AjAppOpt* createApp(QString line);
    QStringList extractShortcutArgs(QString line);
    void checkApps(QVector<AjAppOpt *> apps);
    AjCondOpt* createCondition(QString line);
    int createElseIf(AjCondOpt *condition);

    QString sc_path;
    int line_cntr;
    int line_size;
};

#endif // AJPREPARSER_H

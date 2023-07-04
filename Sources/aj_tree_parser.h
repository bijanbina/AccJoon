#ifndef AJPREPARSER_H
#define AJPREPARSER_H

#include <QFile>
#include <QDebug>
#include "aj_base_parser.h"

class AjTreeParser
{
public:
    AjTreeParser(QString path);
    QVector<AjApp *> parseApps();
    QVector<AjApp *> parseNpipes();
    void parseConditions(QVector<AjApp *> apps);
    void printApps(QVector<AjApp *> apps);
    void printConditions(QVector<AjApp *> apps);
    void parseConditions(AjApp *shortcut);

private:
    void skipToNext();
    QVector<AjApp *> parseObject(QString obj_name);
    AjApp* createApp(QString line);
    QStringList extractShortcutArgs(QString line);
    void checkApps(QVector<AjApp *> apps);
    AjCondOpt* createCondition(QString line);
    int createElseIf(AjCondOpt *condition);

    QString sc_path;
    int line_cntr;
    int line_size;
};

#endif // AJPREPARSER_H

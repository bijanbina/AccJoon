#ifndef AJPREPARSER_H
#define AJPREPARSER_H

#include <QFile>
#include <QDebug>

// conditional options structure
typedef struct AjCondOpt
{
    int first_line;
    int end_line;
    QStringList args;
}AjCondOpt;

// shortcut options structure
typedef struct AjAppOpt
{
    int start_line;
    int end_line;
    QString app_name;
    QString win_title;
    QVector<AjCondOpt *> conditions;
}AjAppOpt;

class AjTreeParser
{
public:
    AjTreeParser(QString path);
    void parseApps();
    void parseConditions();
    void printApps();
    void printConditions();

private:

    AjAppOpt* createApp(QString line);
    QStringList extractShortcutArgs(QString line);
    void checkApps();
    AjCondOpt* createCondition(QString line);
    void parseConditions(AjAppOpt *shortcut);

    QVector<AjAppOpt *> apps;
    QString sc_path;
    int line_cntr;
    int line_size;
};

#endif // AJPREPARSER_H

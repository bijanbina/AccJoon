#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#define AJ_CMD_LMB     0 //Left Mouse Button
#define AJ_CMD_RMB     1
#define AJ_CMD_MMB     2
#define AJ_CMD_DCLICK  3 // Double Click
#define AJ_CMD_CHILDID 4 // Show Child ID

void logMessage(QString msg);
int aj_clickType(QString click_short_name);
QString aj_click_name(int cmd_type);

#endif // BACKEND_H

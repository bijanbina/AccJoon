#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#define AJ_CMD_LMB     "L" // Left Mouse Button
#define AJ_CMD_RMB     "R"
#define AJ_CMD_MMB     "M"
#define AJ_CMD_DCLICK  "D" // Double Click
#define AJ_CMD_CHILDID "C" // Show Child ID

void logMessage(QString msg);

#endif // BACKEND_H

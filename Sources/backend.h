#ifndef BACKEND_H
#define BACKEND_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <wtypes.h>

#define AJ_CMD_LMB     "L" // Left Mouse Button
#define AJ_CMD_RMB     "R"
#define AJ_CMD_MMB     "M"
#define AJ_CMD_DCLICK  "D" // Double Click
#define AJ_CMD_CHILDID "C" // Show Child ID

void logMessage(QString msg);
QString getDiffTime(clock_t start);
QString getLDiffTime();

QString aj_toQString(BSTR input);
BSTR aj_toBSTR(QString input);

#endif // BACKEND_H

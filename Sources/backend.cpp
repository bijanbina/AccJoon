#include "backend.h"

int acc_debug = 1;

void logMessage(QString msg)
{
    QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString txt = QString("[%1] ").arg(dt);

    txt += QString("{Debug} \t\t %1").arg(msg);

    QFile outFile("LogFile.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);

    if( outFile.isOpen() )
    {

        QTextStream textStream(&outFile);
        textStream << txt << "\n";
        outFile.close();
    }
    else
    {
        "FUUUUUUUUUCK";
    }

    if( acc_debug )
    {
        qDebug() << msg;
    }

}

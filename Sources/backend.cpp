#include "backend.h"

int acc_debug = 1;
clock_t bt_last_clock;

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

    if( acc_debug )
    {
        qDebug() << msg;
    }

}

QString getDiffTime(clock_t start)
{
    QString ret;
    clock_t end = clock();
    bt_last_clock = end;
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    ret  = QString::number(qRound(cpu_time_used*1000));
    ret += "ms";
    return  ret;
}

// compare with last
QString getLDiffTime()
{
    QString ret;
    clock_t end = clock();
    double cpu_time_used = ((double) (end - bt_last_clock)) / CLOCKS_PER_SEC;
    ret  = QString::number(qRound(cpu_time_used*1000));
    ret += "ms";
    bt_last_clock = end;
    return  ret;
}

BSTR aj_toBSTR(QString input)
{
    BSTR result= SysAllocStringLen(0, input.length());
    input.toWCharArray(result);
    return result;
}

QString aj_toQString(BSTR input)
{
    return QString::fromUtf16(reinterpret_cast<ushort*>(input));
//    return QString::fromWCharArray(input); // same result
}

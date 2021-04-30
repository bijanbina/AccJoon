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

    if( acc_debug )
    {
        qDebug() << msg;
    }

}

QString aj_click_name(int cmd_type)
{
    if( cmd_type==AJ_CMD_LMB )
    {
        return "left click";
    }
    else if( cmd_type==AJ_CMD_RMB )
    {
        return "right click";
    }
    else if( cmd_type==AJ_CMD_MMB )
    {
        return "middle click";
    }
    else if( cmd_type==AJ_CMD_DCLICK )
    {
        return "double click";
    }
    else if( cmd_type==AJ_CMD_CHILDID )
    {
        return "child id";
    }
    else
    {
        qDebug() << "Error: click type not found, type:" << cmd_type;
        return "";
    }
}

int aj_clickType(QString click_short_name)
{
    if( click_short_name.compare("L", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_LMB;
    }
    else if( click_short_name.compare("R", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_RMB;
    }
    else if( click_short_name.compare("M", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_MMB;
    }
    else if( click_short_name.compare("D", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_DCLICK;
    }
    else if( click_short_name.compare("C", Qt::CaseInsensitive)==0 )
    {
        return AJ_CMD_CHILDID;
    }

    return -1;
}

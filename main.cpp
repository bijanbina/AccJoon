#include <iostream>
#include "aj_win.h"
#include <objbase.h>
#include <aj_client.h>
#include <QCoreApplication>

#define DEBUG_SLEEP 10000
//set PATH=%PATH%;C:\Qt\Qt5.12.10\5.12.10\mingw73_32\bin
//windeployqt O:\Projects\AccJoon\release

using namespace std;


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
    else
    {
        qDebug() << "Error: click" << click_short_name << "is not acceptable";
        return -1;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString path, cmd, acc_name;

    int offset_x = 0;
    int offset_y = 0;
    int offset_id = 0;

    if ( argc==1 )
    {
        path = "4.1.3.2.1.2.2.1.1";
        cmd = "D";
        acc_name = "aj_win.h";
        acc_name = "Headers";

        offset_x = -120;
        offset_y = 0;
        offset_id = 1;
    }

    if ( argc>2 )
    {
        cmd = argv[1];
        path = argv[2];
    }
    if ( argc>3 )
    {
        offset_x = QString(argv[3]).toInt();
    }
    if ( argc>4 )
    {
        offset_y = QString(argv[4]).toInt();
    }
    if ( argc>5 )
    {
        acc_name = argv[5];
    }
    if ( argc>6 )
    {
        offset_id = QString(argv[6]).toInt();;
    }

    CoInitialize(NULL);

    if ( cmd.length()>1 )
    {
//        Sleep(DEBUG_SLEEP);
        QString command = "";//"AccJoon ";
        command += cmd[1] + " ";
        command += path + " 0 0 ";
        command += acc_name;

        qDebug() << "Admin Mode";
        AjClient *client = new AjClient(command);

        return app.exec();
    }
    else
    {
        AjWin *aj_win = new AjWin(path, cmd, acc_name, offset_x, offset_y, offset_id);
        if( aj_win->setWinSpec()!=0 )
        {
            Sleep(DEBUG_SLEEP);
            return -1;
        }
        if( aj_win->setObjSpec()!=0 )
        {
            Sleep(DEBUG_SLEEP);
            return -1;
        }
        aj_win->doClick();

        Sleep(DEBUG_SLEEP);

        return 0;
    }
}

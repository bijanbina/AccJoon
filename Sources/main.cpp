#include <iostream>
#include <objbase.h>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QGuiApplication>
#include <QDir>
#include "aj_var.h"
#include "aj_client.h"
#include "aj_dllgen.h"
#include "aj_chapar.h"

#define DEBUG_SLEEP 5000
//set PATH=%PATH%;C:\Qt\Qt5.12.10\5.12.10\mingw73_32\bin
//windeployqt O:\Projects\AccJoon\release

using namespace std;

AjCmdOptions* parseClOptions(QCoreApplication *app);

void setCurrentDir()
{
    QString exe_dir = QCoreApplication::applicationDirPath();

    QDir::setCurrent(exe_dir);
}

int main(int argc, char *argv[])
{
    // this cannot change to core application as
    // QGuiApplication::primaryScreen() will stop working
    QGuiApplication app(argc, argv);
    CoInitialize(NULL);

    setCurrentDir();
    aj_dllGen();


    if( argc>1 )
    {
        QStringList arguments;
        for( int i=2 ; i<argc ; i++ )
        {
            arguments << argv[i];
        }
        AjChapar chapar(argv[1], arguments);
        if( chapar.hasNamedPipe() )
        {
            return app.exec();
        }
    }
    else
    {
        QStringList conf_list = aj_getConfList();
//        qDebug() << conf_list;
        AjChapar chapar(conf_list);
        if( chapar.hasNamedPipe() )
        {
            return app.exec();
        }
    }
    /*else if( opt->is_remote )
    {
//        QThread::msleep(DEBUG_SLEEP);
        QString command = "";//"AccJoon ";
        AjCommand acc_conf = opt->cmd;
        command += acc_conf.action[1] + " ";
        command += acc_conf.acc_path + " 0 0 ";
        command += acc_conf.acc_name;

        qDebug() << "Admin Mode";
        AjClient client(command);
        client.start();
        return app.exec();
    }
    else // execute on local computer
    {
        AjWin *aj_win = new AjWin();

        AjCommand acc_conf = opt->cmd;
        if( aj_win->doAction(acc_conf)!=0 )
        {
            QThread::msleep(DEBUG_SLEEP);
            return -1;
        }
    }*/

    return 0;
}

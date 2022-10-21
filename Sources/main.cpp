#include <iostream>
#include <objbase.h>
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QGuiApplication>
#include <QDir>
#include "aj_win.h"
#include "aj_client.h"
#include "aj_parser.h"
#include "aj_dllgen.h"
#include "aj_executer.h"

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

    AjCmdOptions *opt = parseClOptions(&app);

    if( opt->conf_path.length() )
    {
        AjParser conf(opt->conf_path); // value stored in parser
        aj_execute(conf.apps);
        return app.exec();
    }
    else
    {
        QStringList conf_list = aj_getConfList();
        qDebug() << conf_list;
        for( int i=0; i<conf_list.size(); i++)
        {
            AjParser conf(conf_list[i]);
            aj_execute(conf.apps);
        }
        return app.exec();
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

AjCmdOptions* parseClOptions(QCoreApplication *app)
{
    AjCmdOptions *ret_opt = new AjCmdOptions;
    QCommandLineParser parser;

    // -c conf
    QStringList option_conf_list;
    option_conf_list << "c" << "conf";
    QCommandLineOption conf_option(option_conf_list,
                       "Set Config File", "Conf path");
    parser.addOption(conf_option);

    // -a acc-path - default 4.1.3.2.1.2.2.1.1
    QStringList option_accpath_list;
    option_accpath_list << "a" << "acc-path";
    QCommandLineOption accpath_option(option_accpath_list,
                       "Set Acc Path", "Acc Path", "4.1.3.2.1.2.2.1.1");
    parser.addOption(accpath_option);

    // -m mouse command - default D
    QStringList option_cmd_list;
    option_cmd_list << "m" << "cmd";
    QCommandLineOption cmd_option(option_cmd_list,
                       "Set Mouse Cmd", "Cmd", "D");
    parser.addOption(cmd_option);

    // -n acc_name - default Headers
    QStringList option_accname_list;
    option_accname_list << "n" << "acc_name";
    QCommandLineOption accname_option(option_accname_list,
                       "Set Acc Name", "Acc Name", "Headers");
    parser.addOption(accname_option);

    // -ox offset_x - default -120
    QStringList option_offsetx_list;
    option_offsetx_list << "ox" << "offset_x";
    QCommandLineOption offsetx_option(option_offsetx_list,
                       "Set Offset X", "Offset X", "-120");
    parser.addOption(offsetx_option);

    // -oy offset_y - default 0
    QStringList option_offsety_list;
    option_offsety_list << "oy" << "offset_y";
    QCommandLineOption offsety_option(option_offsety_list,
                       "Set Offset Y", "Offset Y", "0");
    parser.addOption(offsety_option);

    // -oi offset_id - default 1
    QStringList option_offsetid_list;
    option_offsetid_list << "oi" << "offset_id";
    QCommandLineOption offsetid_option(option_offsetid_list,
                       "Set Offset ID", "Offset ID", "1");
    parser.addOption(offsetid_option);

    // -r remote
    QCommandLineOption remote_option("r", "Execute command on a remote server");
    parser.addOption(remote_option);

    // Process the actual command line arguments given by the user
    parser.process(*app);

    ret_opt->conf_path = parser.value(conf_option);
    ret_opt->is_remote = parser.isSet(remote_option);
    ret_opt->cmd.acc_path = parser.value(accpath_option);
    ret_opt->cmd.action = parser.value(cmd_option);
    ret_opt->cmd.acc_name = parser.value(accname_option);
    ret_opt->cmd.offset_x = parser.value(offsetx_option).toInt();
    ret_opt->cmd.offset_y = parser.value(offsety_option).toInt();
    ret_opt->cmd.offset_id = parser.value(offsetid_option).toInt();

    return ret_opt;
}

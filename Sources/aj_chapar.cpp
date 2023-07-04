#include "aj_chapar.h"

AjChapar::AjChapar(QString path, QStringList arguments,
                   QObject *parent) : QObject(parent)
{
    test_timer = new QTimer();
    connect(test_timer, SIGNAL(timeout()), this, SLOT(testTimeout()));
    test_timer->start(2000);

    execScript(path, arguments);
    if( nps.size() )
    {
        channel = new AjChannel();
        channel_thread = new QThread();
        channel->moveToThread(channel_thread);
        connect(this, SIGNAL(startChannel()), channel, SLOT(ListenPipe()));
        connect(channel, SIGNAL(npReceived(QString, QStringList)),
                this, SLOT(execNPipe(QString, QStringList)));
        channel_thread->start();
        emit startChannel();
    }
}

AjChapar::AjChapar(QStringList paths,
                   QObject *parent) : QObject(parent)
{
    for( int i=0; i<paths.size(); i++)
    {
        execScript(paths[i]);
    }
}

void AjChapar::testTimeout()
{
    channel->testTimeout();
}

int AjChapar::hasNamedPipe()
{
    return nps.size();
}

void AjChapar::execScript(QString path, QStringList arguments)
{
    tree_parser = new AjTreeParser(path);
    apps = tree_parser->parseApps();
    nps  = tree_parser->parseNpipes();
    tree_parser->parseConditions(apps);
    tree_parser->parseConditions(nps);
//    tree_parser->printApps(apps);
//    tree_parser->printConditions(apps);
    AjExec exec(tree_parser, arguments);
    exec.execApps(apps);
}

void AjChapar::execNPipe(QString np_name, QStringList arguments)
{
    int len = nps.size();
    for( int i=0 ; i<len ; i++ )
    {
        if( nps[i]->app_name==np_name )
        {
            AjExec exec(tree_parser, arguments);
            exec.execApps(nps);
            return;
        }
    }
}

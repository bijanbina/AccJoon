#include "aj_channel.h"
#include <QDebug>

AjChannel::AjChannel(QObject *parent) : QObject(parent)
{
    createPipe();
}

void AjChannel::createPipe()
{
    // To create an instance of a named pipe by using CreateNamedPipe,
    // the user must have FILE_CREATE_PIPE_INSTANCE access to the named pipe object.
    hPipe = CreateNamedPipe(TEXT(PIPE_PATH),
                            PIPE_ACCESS_INBOUND,            // dwOpenMode. The flow of data in the pipe goes from client to server only
                            PIPE_TYPE_BYTE | PIPE_WAIT,     // dwPipeMode
                            1,                              // nMaxInstances
                            BUFFER_SIZE,                    // nOutBufferSize
                            BUFFER_SIZE,                    // nInBufferSize
                            NMPWAIT_WAIT_FOREVER,           // nDefaultTimeOut
                            nullptr);                       // lpSecurityAttributes

    if( hPipe==INVALID_HANDLE_VALUE )
    {
        qDebug(PIPE_PATH"Failed");
    }
    qDebug() << PIPE_PATH << "pipe Created";
}

void AjChannel::ListenPipe()
{
    char buffer[BUFFER_SIZE];
    DWORD dwRead;
    while( hPipe!=INVALID_HANDLE_VALUE )
    {
        // wait for someone to connect to the pipe
        if( ConnectNamedPipe(hPipe, nullptr)!=FALSE )
        {
            qDebug() << "Connect client";
            while( ReadFile(hPipe, buffer, sizeof(buffer)-1,
                            &dwRead, nullptr)!=FALSE )
            {
                // add terminating zero
                buffer[dwRead] = 0;
                QString input(buffer);

                QStringList lines = input.split("\n",
                                                QString::SkipEmptyParts);

                for(int i=0 ; i<lines.length() ; i++)
                {
                    processLine(lines[i]);
                }
            }
        }

        qDebug() << "Client Disconnected";
        DisconnectNamedPipe(hPipe);
    }
}

void AjChannel::testTimeout()
{
    QString np_name = "Altium";
    QStringList fields = {"Vias", "bb", "cc"};
    emit npReceived(np_name, fields);
}

// Altium, arg1, arg2, ...
void AjChannel::processLine(QString line)
{
    line = line.trimmed();
    QStringList fields = line.split(AJ_NP_SEPARATOR,
                               QString::SkipEmptyParts);
    int len = fields.size();

    QString np_name;
    if( fields.length()==0 )
    {
        qDebug() << "Error 128: wrong field length, data=`"
                    + line + "`";
        return;
    }
    else if( len>0 )
    {
        np_name = fields[0].trimmed();
    }
    for( int i=1 ; i<len ; i++ )
    {
        fields[i] = fields[i].trimmed();
    }
    emit npReceived(np_name, fields.mid(1));
}

#include "aj_win_process.h"
#include "aj_win32.h"

int  aj_isProcOpen(QString name)
{
    DWORD pid_list[1024], byte_len;

    if( !EnumProcesses(pid_list, sizeof(pid_list), &byte_len) )
    {
        return 0;
    }

    int len = byte_len / sizeof(DWORD);
    for( int i=0 ; i<len ; i++ )
    {
        if( pid_list[i]!=0 )
        {
            QString pname = aj_getPName(pid_list[i]);
            if( pname.toLower()==name.toLower() )
            {
                qDebug() << "aj_isProcOpen"
                         << pname << pid_list[i];
                return 1;
            }
        }
    }

    return 0;
}

void aj_waitOpen(QString p_name)
{
    while( 1 )
    {
        QThread::msleep(10);
        if( aj_isProcOpen(p_name) )
        {
            break;
        }
    }
}

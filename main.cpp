#include <iostream>
#include "aj_win.h"
#include <objbase.h>

using namespace std;

int main(int argc, char *argv[])
{
    QString path, cmd, acc_name;

    if ( argc==1 )
    {
        path = "4.1.3.2.1.2.2.1.1.6";
        cmd = "D";
    }
    else if ( argc==3 )
    {
        path = argv[1];
        cmd = argv[2];
    }
    else if ( argc==3 )
    {
        path = argv[1];
        cmd = argv[2];
    }
    else if ( argc==4 )
    {
        path = argv[1];
        cmd = argv[2];
        acc_name = argv[3];
    }
    else
    {
        qDebug() << "Input arguments not supported argc:" << argc;
    }

    CoInitialize(NULL);

    AjWin *aj_win = new AjWin(path, cmd, acc_name);
    if( aj_win->setWinSpec()!=0 )
    {
        return -1;
    }
    if( aj_win->setObjSpec()!=0 )
    {
        return -1;
    }
    aj_win->doClick();

    return 0;
}

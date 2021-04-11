#include <iostream>
#include "aj_win.h"
#include <objbase.h>

using namespace std;

int main(int argc, char *argv[])
{
    QString path, cmd, acc_name;

    int offset_x = 0;
    int offset_y = 0;

    if ( argc==1 )
    {
        path = "4.1.3.2.1.2.2.1.1";
        cmd = "D";
        acc_name = "Headers";
        acc_name = "aj_win.h";

        offset_x = -120;
        offset_y = 0;
    }

    if ( argc>2 )
    {
        path = argv[1];
        cmd = argv[2];
    }
    if ( argc>3 )
    {
        acc_name = argv[3];
    }
    if ( argc>4 )
    {
        offset_x = QString(argv[4]).toInt();
    }
    if ( argc>5 )
    {
        offset_y = QString(argv[5]).toInt();
    }

    CoInitialize(NULL);

    AjWin *aj_win = new AjWin(path, cmd, acc_name, offset_x, offset_y);
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

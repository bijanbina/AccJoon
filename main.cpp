#include <iostream>
#include "aj_win.h"
#include <objbase.h>

using namespace std;

int main(/*int argc, char *argv[]*/)
{
    QString path = "3021011005";//"4132122119
    QString cmd = "D";

    CoInitialize(NULL);

    AjWin *aj_win = new AjWin(path, cmd);
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

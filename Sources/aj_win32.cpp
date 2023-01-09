#include "aj_win32.h"
#include <QFileInfo>
#include <QGuiApplication>
#include <QScreen>
//#include "aj_acc_prop.h"

int win_debug = 0;
int win_offset = 0;
DWORD pid_g;
HWND hwnd_g = NULL;
#define MAX_TITLE_LEN 200

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    AjApplication *app = (AjApplication *)lParam; // requested pname
    QString win_title = aj_getWinTitle(hwnd);

    if( win_title.length() )
    {
        long pid = aj_getPid(hwnd);
        QString pname = aj_getPName(pid);
        pname = QFileInfo(pname).completeBaseName();
        if( pname==app->exe_name )
        {
//            qDebug() << "EnumWindowsProc find HWND"
//                     << pname << app->exe_name << hwnd
//                     << win_title;
            if( win_title.contains(app->win_title) )
            {
                hwnd_g = hwnd;
                return FALSE;
            }
        }
    }
    return TRUE;
}

BOOL CALLBACK EnumWindowsPid(HWND hwnd, LPARAM lParam)
{
    DWORD enum_pid;
    AjApplication *req_win = (AjApplication *)lParam;
    GetWindowThreadProcessId(hwnd,&enum_pid);
    if( pid_g==enum_pid )
    {
        qDebug() << "found one!" << pid_g;
        char buffer[128];
        GetWindowTextA(hwnd, buffer, 128);
        req_win = new AjApplication;
        req_win->hwnd = hwnd;
        req_win->pid = pid_g;
        req_win->pname = aj_getPPath(pid_g);
        req_win->win_title = buffer;
        return FALSE;
    }
    return TRUE;
}

long aj_getPid(HWND hWnd)
{
    // get allegro pid of window handle
    DWORD dwProcessId;
    GetWindowThreadProcessId(hWnd, &dwProcessId);
    if(long(dwProcessId) < 0)
    {
        qDebug() <<"Warning: couldn't get pid of allegro from window handle";
        return -1;
    }
    return dwProcessId;
}

QString aj_getPPath(long pid)
{
    HANDLE processHandle = NULL;
//    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    processHandle = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if(processHandle == NULL)
    {
        return "";
    }

    // get name of process handle
    char filename[MAX_PATH];
    if(GetProcessImageFileNameA(processHandle, filename, MAX_PATH) == 0)
    {
//        qDebug() << "Error" << GetLastError() << " : Fail to get Pname of " << pid;
        return "";
    }
    return QString(filename);
}

QString aj_getPName(long pid)
{
    QString name = aj_getPPath(pid);
    QString process_name = QFileInfo(name).fileName();
    return process_name;
}

HWND aj_getHWND(AjApplication *app)
{
    HWND hwnd = aj_getFocusedHWND(app);
    if( hwnd )
    {
        return hwnd;
    }
    //else
    EnumWindows(EnumWindowsProc, (LPARAM) app);
    return hwnd_g;
}

void aj_setActiveWindow(HWND hWnd)
{
    DWORD dwCurrentThread = GetCurrentThreadId();
    DWORD dwFGThread = GetWindowThreadProcessId(GetForegroundWindow(), NULL);
    AttachThreadInput(dwCurrentThread, dwFGThread, TRUE);

    SetForegroundWindow(hWnd);
    SetActiveWindow(hWnd);

    // If window is minimzed
    if( IsIconic(hWnd) )
    {
        ShowWindow(hWnd, SW_RESTORE);
    }

    AttachThreadInput(dwCurrentThread, dwFGThread, FALSE);
}

void aj_findWindowByPid(DWORD pid, AjApplication *app)
{
    int cntr=0;
    pid_g = pid;
    app->hwnd = NULL;
    while( app->hwnd )
    {
        cntr++;
        EnumWindows(EnumWindowsPid, (LPARAM) app);
        QThread::msleep(50);
        if( cntr%100==0 )
        {
//            qDebug() << "Info: searching for HWND with pid:" << pid;
            cntr = 0;
        }
    }
}

void aj_setMouse(int x, int y)
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));
    input.type = INPUT_MOUSE;

    //convert to abs cords(required for send input)
    QScreen *p_screen = QGuiApplication::primaryScreen();
    QRect screen = p_screen->geometry();
    long abs_x = x*65536;
    long abs_y = y*65536;
    abs_x /= screen.width();
    abs_y /= screen.width();

    input.mi.dx = abs_x;
    input.mi.dy = abs_y;

    // set move cursor directly
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

    SendInput(1, &input, sizeof(INPUT));
}

QString aj_getWinTitle(HWND hwnd)
{
    char buffer[MAX_TITLE_LEN];
    int written = GetWindowTextA(hwnd, buffer, MAX_TITLE_LEN);
    if( written==0 )
    {
        return "";
    }

    QString ret = buffer;
    return ret;
}
//return focused HWND if it match exe_name
HWND aj_getFocusedHWND(AjApplication *app)
{
    HWND hwnd = GetForegroundWindow();
    QString pname = aj_getPName(aj_getPid(hwnd));

    if( pname.contains(app->exe_name) )
    {
//        qDebug() << "exe_name" << app->exe_name;
        return hwnd;
    }
    else
    {
        return NULL;
    }
}

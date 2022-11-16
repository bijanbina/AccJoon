#include "aj_win32.h"
#include <QFileInfo>
#include <QGuiApplication>
#include <QScreen>

int win_debug = 0;
int win_offset = 0;
int win_current = 0;
DWORD pid_g;
HWND hwnd_g = NULL;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    char *req_pname = (char *)lParam; // requested pname
    int written = GetWindowTextA(hwnd, buffer, 128);
    if( written && strlen(buffer)!=0 )
    {
        long pid = aj_getPid(hwnd);
        QString pname = aj_getPName(pid);
        pname = QFileInfo(pname).completeBaseName();
//        qDebug() << pname << req_pname;
        if( pname == req_pname )
        {
            hwnd_g = hwnd;
            return FALSE;
        }
    }
    return TRUE;
}

BOOL CALLBACK EnumWindowsPid(HWND hwnd, LPARAM lParam)
{
    DWORD enum_pid;
    AjWindow *req_win = (AjWindow *)lParam;
    GetWindowThreadProcessId(hwnd,&enum_pid);
    if( pid_g==enum_pid )
    {
        qDebug() << "found one!" << pid_g;
        char buffer[128];
        GetWindowTextA(hwnd, buffer, 128);
        req_win = new AjWindow;
        req_win->hWnd = hwnd;
        req_win->pid = pid_g;
        req_win->pname = aj_getPPath(pid_g);
        req_win->title = buffer;
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

HWND aj_getHWND(QString exe_name)
{
    char exe_name_c[200];
    strcpy(exe_name_c, exe_name.toStdString().c_str());
    win_current = 0;
    EnumWindows(EnumWindowsProc, (LPARAM) exe_name_c);
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

void aj_findWindowByPid(DWORD pid, AjWindow *window)
{
    int cntr=0;
    pid_g = pid;
    window->hWnd = NULL;
    while( window->hWnd )
    {
        cntr++;
        EnumWindows(EnumWindowsPid, (LPARAM) window);
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

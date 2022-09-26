#include "aj_win32.h"
#include <QFileInfo>

int win_debug = 0;
int win_offset = 0;
int win_current = 0;
AjWindow *req_win = NULL;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    char *win_name = (char *)lParam;
    int written = GetWindowTextA(hwnd, buffer, 128);
    if( written && strlen(buffer)!=0 )
    {
        QString buff_s = buffer;
        if( buff_s.contains(win_name) )
        {
            win_current++;
            if( win_offset>win_current )
            {
                aj_setActiveWindow(hwnd);
            }
        }
    }
    return TRUE;
}

BOOL CALLBACK EnumWindowsFind(HWND hwnd, LPARAM lParam)
{
    char buffer[128];
    int written = GetWindowTextA(hwnd, buffer, 128);
    if( written && strlen(buffer)!=0 )
    {
        QString buff_s = buffer;
        long pid = aj_getPid(hwnd);
        QString pname = aj_getPPath(pid);
        QString exe_name = *(QString *)lParam;
        if( pname.contains(exe_name) )
        {
            if( aj_fillWinSpec(hwnd, buff_s, exe_name) )
            {
                return FALSE;
            }

        }
    }
    return TRUE;
}

BOOL CALLBACK EnumWindowsPid(HWND hwnd, LPARAM lParam)
{
    DWORD enum_pid, pid;
    pid = *(DWORD *)lParam;
    GetWindowThreadProcessId(hwnd,&enum_pid);
    if( pid==enum_pid )
    {
        qDebug() << "found one!" << pid;
        char buffer[128];
        GetWindowTextA(hwnd, buffer, 128);
        req_win = new AjWindow;
        req_win->hWnd = hwnd;
        req_win->pid = pid;
        req_win->pname = aj_getPPath(pid);
        req_win->title = buffer;
        return FALSE;
    }
    return TRUE;
}

//Add a new Hwnd to wins_title vector
void aj_AddHwnd(HWND hwnd, AjListW *list_w)
{
    char buffer[128];
    RECT rc;

    if(IsWindowVisible(hwnd))
    {
        int cloaked;
        DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, 4);

        HWND shell_window = GetShellWindow();
        GetWindowRect(hwnd, &rc);
        int width = rc.right - rc.left;

        if((hwnd!=shell_window) && (width>100) ) //&& (rc.bottom>0)
        {
            int success = GetWindowTextA(hwnd, buffer, 128); //get title

            if ( success==0 )
            {
                qDebug() << hwnd << "Failed to GetWindowTextA";
            }


            AjWindow current_win;
            current_win.hWnd = hwnd;
            current_win.title = buffer;
            current_win.pname = aj_getPPath(aj_getPid(hwnd));
            current_win.verify = 1; //always new windows are verified
//                current_win.title = thread_w->cleanTitle(current_win.title);

            aj_InsertWindow(list_w, current_win);
        }
    }
}

void aj_InsertWindow(AjListW *thread_w, AjWindow win)
{
    //Get clover child
    aj_getType(&win);

    //push active window to front
    if ( win.hWnd == thread_w->win_active.hWnd )
    {
        if ( thread_w->windows.size()>0 )
        {
            if ( thread_w->windows[0].hWnd != win.hWnd )
            {
                thread_w->windows.push_front(win);
                qDebug() << "Active Changed" << win.title;
            }
            else
            {
                thread_w->windows[0].verify = 1;
                thread_w->windows[0].title = win.title;
            }
        }
        else
        {
            thread_w->windows.push_front(win);
            qDebug() << "First Time" << win.title;
            return;
        }
    }

    for( int i=1 ; i<thread_w->windows.size() ; i++ )
    {
        if ( thread_w->windows[i].hWnd==thread_w->win_active.hWnd )
        {
            thread_w->windows.remove(i);
            i--;
        }
        else if ( thread_w->windows[i].hWnd==win.hWnd )
        {
            thread_w->windows[i].verify = 1;
            thread_w->windows[i].title = win.title;
//            qDebug() << "Ver Window" << i << win.title;
            return;
        }
    }

    if ( win.hWnd != thread_w->win_active.hWnd )
    {
        thread_w->windows.push_back(win);
        qDebug() << "New Window" << win.title;
    }

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
    QFileInfo fi(name);
    return fi.fileName();
}

void aj_getType(AjWindow *win)
{
    char buffer[128];
    GetClassNameA(win->hWnd, buffer, 128);
    QString class_name = buffer;

    if( class_name.contains("Qt") && class_name.contains("QWindowIcon") )
    {
        win->type = RE_WIN_QT;

        if ( win->title.contains(" - Qt Creator"))
        {
            QString title = "Qt Cre: ";
            title += win->title.split(" (").at(0);
            win->title = title;
        }
    }
    else if( class_name.contains("Chrome_WidgetWin") )
    {
        if ( win->pname.contains("Spotify.exe") )
        {
            win->type = RE_WIN_SPOTIFY;

            QString title = "Spotiy: ";
            title += win->title;
            win->title = title;
        }
        else if ( win->pname.contains("atom.exe") )
        {
            win->type = RE_WIN_TEXTEDITOR;

            QString title = "Atom : ";
            title += win->title.split("\ufffd").at(0);
            win->title = title;
        }
        else
        {
            win->type = RE_WIN_UNKNOWN;
            if( win_debug )
            {
                qDebug() << class_name << win->pname;
            }
        }
    }
    else if( class_name.contains("MozillaWindowClass") )
    {
        win->type = RE_WIN_FIREFOX;
        if ( win->title.contains(" - YouTube"))
        {
            win->type = RE_WIN_YOUTUBE;
        }

        QString title = "Firef : ";
        title += win->title.split("\ufffd").at(0);
        win->title = title;
    }
    else if( class_name.contains("ConsoleWindowClass") )
    {
        win->type = RE_WIN_TERMINAL;

        QString title = "CMD  : ";
        title += win->title.split("\ufffd").at(0);
//        win->title = title;

    }
    else
    {
        win->type = RE_WIN_UNKNOWN;
        if( win_debug )
        {
            qDebug() << class_name << win->pname;
        }
    }
}

void aj_setActiveWindow(QString win_name)
{
    char buffer[200];
    strcpy(buffer, win_name.toStdString().c_str());
    win_current = 0;
    EnumWindows(EnumWindowsProc, (LPARAM) buffer);
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

bool aj_fillWinSpec(HWND hwnd, QString title, QString exe_name)
{
    RECT rc;

    if(IsWindowVisible(hwnd))
    {
        HWND shell_window = GetShellWindow();
        GetWindowRect(hwnd, &rc);
        int width = rc.right - rc.left;

        if((hwnd!=shell_window) && (width>100) ) //&& (rc.bottom>0)
        {
            long pid = aj_getPid(hwnd);
            QString pname = aj_getPPath(pid);
            QFileInfo fi(pname);
            pname = fi.completeBaseName();
            if( exe_name==pname )
            {
                qDebug() << "title" << title << "|" << exe_name << "|" << pname;
                req_win = new AjWindow;
                req_win->hWnd = hwnd;
                req_win->title = title;
                req_win->pname = pname;
                req_win->pid = pid;
                return true;
            }
        }
        else
        {
//                int success = GetWindowTextA(hwnd, buffer, 128); //get title
//                qDebug() << "----------" << buffer << rc.bottom << width;
        }
    }
    else
    {
//        int success = GetWindowTextA(hwnd, buffer, 128); //get title
//        qDebug() << "not vis" << buffer << IsWindowVisible(hwnd);
    }
    return false;
}

AjWindow* aj_findAppByName(QString exe_name)
{
    if( req_win!=NULL )
    {
        delete req_win;
        req_win = NULL;
    }
    EnumWindows(EnumWindowsFind, (LPARAM) &exe_name);

    return req_win;
}

AjWindow* aj_findAppByPid(DWORD pid)
{
    if( req_win!=NULL )
    {
        delete req_win;
        req_win = NULL;
    }
    int cntr=0;
    while( req_win==NULL )
    {
        cntr++;
        EnumWindows(EnumWindowsPid, (LPARAM) &pid);
        QThread::msleep(50);
        if( cntr%100==0 )
        {
            qDebug() << "Info: searching for HWND with pid:" << pid;
            cntr = 0;
        }
    }

    return req_win;
}

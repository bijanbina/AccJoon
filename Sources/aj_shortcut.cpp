#include "aj_shortcut.h"
#include <shobjidl.h>
#include <shlguid.h>
#include <QFileInfo>

QString getLinkLongPath(QString shortcut_name)
{
    QString link_path = getLinkPath(shortcut_name);
    if( link_path=="" )
    {
        qDebug() << "Error: get link path failed"
                 << shortcut_name;
        return "";
    }
    char buffer[200];
    GetLongPathNameA(link_path.toStdString().c_str(),
                     buffer, 200);
    return buffer;
}

AjApplication getApplication(QString shortcut_name)
{
    AjApplication app;
    app.shortcut_name = shortcut_name;
    app.exe_path = getLinkLongPath(shortcut_name);
    QFileInfo fi(app.exe_path);
    app.exe_name = fi.completeBaseName();
    app.hwnd = aj_getHWND(app.exe_name);
    return app;
}

void launchApp(AjApplication *app, QString arg)
{
    QString path = app->exe_path + " " + arg;

    PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter
    STARTUPINFOA StartupInfo; //This is an [in] parameter

    ZeroMemory( &StartupInfo, sizeof(StartupInfo) );
    StartupInfo.cb = sizeof(StartupInfo);
    ZeroMemory( &ProcessInfo, sizeof(ProcessInfo) );

    char app_cmd[200];
    strcpy(app_cmd, path.toStdString().c_str());

    int ret = CreateProcessA(NULL, app_cmd, NULL,
                             NULL, FALSE, 0, NULL,
                             NULL, &StartupInfo,
                             &ProcessInfo);
    if( ret==0 )
    {
        long last_error = GetLastError();
        qDebug() << "CreateProcess failed" << last_error;
        return;
    }

    app->pid = ProcessInfo.dwProcessId;
}

QString getLinkPath(QString name)
{
    QString ret = getLinkPathA(name);
    if( ret.isEmpty() )
    {
        ret = getLinkPathB(name);
    }
    return ret;
}

QString getLinkPathA(QString name)
{
    char target[MAX_PATH];

    QString lnk = getenv("APPDATA");
    lnk += "\\Microsoft\\Windows\\Start Menu\\Programs\\";
    lnk = findAppPath(lnk, name);

    resolveIt(lnk.toStdString().c_str(), target);

    return target;
}

//retreive link from ProgramData instead of user account
QString getLinkPathB(QString name)
{
    char target[MAX_PATH];

    QString lnk = getenv("PROGRAMDATA");
    lnk += "\\Microsoft\\Windows\\Start Menu\\Programs\\";
    lnk = findAppPath(lnk, name);

    resolveIt(lnk.toStdString().c_str(), target);

    return target;
}

QString findAppPath(QString path, QString pattern)
{
    QDir directory(path);
    directory.setFilter(QDir::Files | QDir::NoDot | QDir::NoDotDot);
    QRegExp pattern_reg("^" + pattern.toLower());
    QRegExp lnk_reg(".lnk$");

    if( directory.exists() )
    {
        QFileInfoList file_list = directory.entryInfoList();

        for( int i=0 ; i<file_list.size() ; i++ )
        {
            if( file_list[i].fileName().toLower().contains(pattern_reg) &&
                file_list[i].fileName().contains(lnk_reg))
            {
                return file_list[i].absoluteFilePath().replace("/", "\\");
            }
        }
        directory.setFilter(QDir::Dirs | QDir::NoSymLinks |
                            QDir::NoDot | QDir::NoDotDot);

        QFileInfoList dir_list = directory.entryInfoList();

        for( int i=0 ; i<dir_list.size() ; i++ )
        {
            if( dir_list[i].fileName().toLower().contains(pattern_reg) )
            {
                return findAppPath(dir_list[i].absoluteFilePath()
                                   .replace("/", "\\"),  pattern);
            }
        }
        return "";
    }
    else
    {
        qDebug() << "Error: Directory doesnt exist.";
        return "";
    }
}

HRESULT resolveIt(LPCSTR lnk_path, char *target)
{
    HRESULT hres;
    IShellLink* psl;
    WCHAR szGotPath[MAX_PATH];
    WCHAR szDescription[MAX_PATH];
    WIN32_FIND_DATA wfd;

    *target = 0; // Assume failure

    // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
    // has already been called.
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
    if( SUCCEEDED(hres) )
    {
        IPersistFile* ppf;

        // Get a pointer to the IPersistFile interface.
        hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);

        if (SUCCEEDED(hres))
        {
            WCHAR wsz[MAX_PATH];

            // Ensure that the string is Unicode.
            MultiByteToWideChar(CP_ACP, 0, lnk_path, -1, wsz, MAX_PATH);

            // Add code here to check return value from MultiByteWideChar
            // for success.

            // Load the shortcut.
            hres = ppf->Load(wsz, STGM_READ);

            if (SUCCEEDED(hres))
            {
                // Resolve the link.
                HWND hwnd = GetActiveWindow();
                hres = psl->Resolve(hwnd, 0);

                if (SUCCEEDED(hres))
                {
                    // Get the path to the link target.
                    hres = psl->GetPath(szGotPath, MAX_PATH, (WIN32_FIND_DATA*)&wfd, SLGP_SHORTPATH);

                    if (SUCCEEDED(hres))
                    {
                        // Get the description of the target.
                        hres = psl->GetDescription(szDescription, MAX_PATH);

                        if (SUCCEEDED(hres))
                        {
                            hres = wcstombs(target, szGotPath, wcslen(szGotPath) + 1);
                            if (SUCCEEDED(hres))
                            {
                                // Handle success
                            }
                            else
                            {
                                // Handle the error
                            }
                        }
                    }
                }
            }

            // Release the pointer to the IPersistFile interface.
            ppf->Release();
        }

        // Release the pointer to the IShellLink interface.
        psl->Release();
    }
    return hres;
}

#include "aj_virt.h"
#include <initguid.h>
#include <windows.h>
#include <QDebug>
#include <QThread>
#include "mm_win32_guid.h"

AjVirt::AjVirt(QObject *parent): QObject(parent)
{
    manager_int = NULL;
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    IServiceProvider* services = NULL;
    HRESULT hr = CoCreateInstance(
                        CLSID_ImmersiveShell, NULL, CLSCTX_LOCAL_SERVER,
                        __uuidof(IServiceProvider), (PVOID*)&services);

    hr = services->QueryService(CLSID_VirtualDesktopManager,
                                        IID_IVirtualDesktopManager,
                                        (void **)&pDesktopManager);

    win_ver = mm_getWinVer();
    if( win_ver==MM_WIN10 )
    {
        initInternal_Win10(services);
    }
    else if( win_ver==MM_WIN11_21H2 )
    {
        initInternal_Win11_21H2(services);
    }

    services->Release();

    current_desktop = getCurrDesktop();
    last_desktop = -1;
}

AjVirt::~AjVirt()
{
    if( win_ver==MM_WIN10 )
    {
        manager_int->Release();
    }
    else if( win_ver==MM_WIN11_21H2 )
    {
        manager_int_win11_21H2->Release();
    }
}

void AjVirt::initInternal_Win10(IServiceProvider* service)
{
    IObjectArray *desktops = NULL;
    IVirtualDesktop *c_desktop;
    HRESULT hr;

    hr = service->QueryService(CLSID_VirtualDesktopAPI_Unknown,
                               IID_IVirtualDesktopManagerInternal_Win10,
                               (void **)&manager_int);
    if( hr )
    {
        qDebug() << "IVirtualDesktopManagerInternal Failed" << hr;
    }

    hr = manager_int->GetDesktops(&desktops);
    UINT count;
    desktops->GetCount(&count);

    GUID buffer;
    for( unsigned int i=0 ; i<count ; i++ )
    {
        desktops->GetAt(i, UUID_IVirtualDesktop_Win10,
                        (void**)&c_desktop);

        c_desktop->GetID(&buffer);
        vd_guids << buffer;
        vd_desks << c_desktop;
    }

    desktops->Release();
}

void AjVirt::initInternal_Win11_21H2(IServiceProvider* service)
{
    IObjectArray *desktops = NULL;
    IVirtualDesktop_Win11_21H2 *c_desktop_win11_21H2;
    HRESULT hr;

    hr = service->QueryService(CLSID_VirtualDesktopAPI_Unknown,
                        IID_IVirtualDesktopManagerInternal_Win11_21H2,
                        (void **)&manager_int_win11_21H2);
    if( hr )
    {
        qDebug() << "IVirtualDesktopManagerInternal Failed" << hr;
    }

    hr = manager_int_win11_21H2->GetDesktops(NULL, &desktops);
    UINT count;
    desktops->GetCount(&count);

    GUID buffer;

    for( unsigned int i=0 ; i<count ; i++ )
    {
        desktops->GetAt(i, UUID_IVirtualDesktop_Win11_21H2,
                        (void**)&c_desktop_win11_21H2);


        c_desktop_win11_21H2->GetID(&buffer);
        vd_guids << buffer;
        vd_desks_win11_21H2 << c_desktop_win11_21H2;
    }

    desktops->Release();
}

void AjVirt::setDesktop(int id)
{
    if( win_ver==MM_WIN10 )
    {
        if( id>vd_desks.length()-1 || id<0 )
        {
            return;
        }
    }
    else if( win_ver==MM_WIN11_21H2 )
    {
        if( id>vd_desks_win11_21H2.length()-1 || id<0 )
        {
            return;
        }
    }
    current_desktop = getCurrDesktop();
    if( current_desktop==id+1 )
    {
        return;
    }
    if( win_ver==MM_WIN10 )
    {
        manager_int->SwitchDesktop(vd_desks[id]);
    }
    else if( win_ver==MM_WIN11_21H2 )
    {
        manager_int_win11_21H2->SwitchDesktop(NULL,
                                              vd_desks_win11_21H2[id]);
    }
//        qDebug() << "setDesktop" << res;
    last_desktop = current_desktop;
    current_desktop = id + 1;
}

int AjVirt::isCurrentActive()
{
    return false;
}

void AjVirt::setFocus()
{
    QThread::msleep(100);

    if( isCurrentActive()==0 )
    {
        pressKey(VK_LMENU); //ALT
        sendKey(VK_TAB);
        releaseKey(VK_LMENU);
    }
}

int AjVirt::getCurrDesktop()
{
    GUID curr_desktop_GUID = getCurrDesktopGuid();

    for( int i=0 ; i<vd_guids.length() ; i++ )
    {
        if( curr_desktop_GUID==vd_guids[i] )
        {
            current_desktop = i+1;
            return current_desktop;
        }
    }

    return 1;
}

GUID AjVirt::getCurrDesktopGuid()
{
    HRESULT hr;
    GUID curr_desktop_GUID;

    if( win_ver==MM_WIN10 )
    {
        IVirtualDesktop *currDesktop;

        hr = manager_int->GetCurrentDesktop(&currDesktop);

        if( currDesktop==NULL )
        {
            qDebug() << "Error 21: Mom is not movable!";
        }
        currDesktop->GetID(&curr_desktop_GUID);
        currDesktop->Release();
    }
    else if( win_ver==MM_WIN11_21H2 )
    {
        IVirtualDesktop_Win11_21H2 *currDesktop;

        hr = manager_int_win11_21H2->GetCurrentDesktop(NULL,
                                                       &currDesktop);

        if( currDesktop==NULL )
        {
            qDebug() << "Error 21: Mom is not movable!";
        }
        currDesktop->GetID(&curr_desktop_GUID);
        currDesktop->Release();
    }
    return curr_desktop_GUID;
}


void AjVirt::sendKey(int key_val)
{
    pressKey(key_val);
    releaseKey(key_val);
}

void AjVirt::pressKey(int key_val)
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key_val;

    SendInput(1, &input, sizeof(INPUT));
}

void AjVirt::releaseKey(int key_val)
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key_val;
    input.ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}

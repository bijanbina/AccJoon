#include "aj_virt.h"
#include <initguid.h>
#include <windows.h>
#include <inspectable.h> // IInspectable, HSTRING, TrustLevel
#include <shobjidl.h> // IObjectArray, ObjectArray, IVirtualDesktopManager, VirtualDesktopManager
#include <strsafe.h> // StringCbPrintf
#include <tlhelp32.h> // to get pid
#include <psapi.h> // For access to GetModuleFileNameEx
#include <QDebug>
#include <QThread>

AjVirt::AjVirt(QObject *parent): QObject(parent)
{
    pDesktopManagerInt = NULL;
    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    IServiceProvider* pServiceProvider = NULL;
    HRESULT hr = CoCreateInstance(
                        CLSID_ImmersiveShell, NULL, CLSCTX_LOCAL_SERVER,
                        __uuidof(IServiceProvider), (PVOID*)&pServiceProvider); 

    hr = pServiceProvider->QueryService(CLSID_VirtualDesktopManager,
                                        IID_IVirtualDesktopManager,
                                        (void **)&pDesktopManager);

    hr = pServiceProvider->QueryService(CLSID_VirtualDesktopAPI_Unknown,
                                        IID_IVirtualDesktopManagerInternal,
                                        (void **)&pDesktopManagerInt);
    pServiceProvider->Release();

    updateGUID();

    current_desktop = getCurrDesktop();
    last_desktop = -1;
}

AjVirt::~AjVirt()
{
    pDesktopManagerInt->Release();
}

void AjVirt::updateGUID()
{
    IObjectArray *desktops;
    IVirtualDesktop *c_desktop;

    pDesktopManagerInt->GetDesktops(&desktops);
    UINT count;
    desktops->GetCount(&count);

    for( unsigned int i=0 ; i<count ; i++ )
    {
        desktops->GetAt(i, UUID_IVirtualDesktop, (void**)&c_desktop);

        GUID buffer;
        c_desktop->GetID(&buffer);
        vd_guids << buffer;
        vd_desks << c_desktop;
    }

    desktops->Release();
}

void AjVirt::setDesktop(int id)
{
    if( id<vd_desks.length() && id>=0 )
    {
        current_desktop = getCurrDesktop();
        if( current_desktop==id+1 )
        {
            return;
        }
        int res = pDesktopManagerInt->SwitchDesktop(vd_desks[id]);
//        qDebug() << "setDesktop" << res;
        setFocus();
        last_desktop = current_desktop;
        current_desktop = id + 1;
    }
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
    IVirtualDesktop *currDesktop;

    pDesktopManagerInt->GetCurrentDesktop(&currDesktop);
    GUID curr_DesktopGUID;
    currDesktop->GetID(&curr_DesktopGUID);
    currDesktop->Release();

    for( int i=0 ; i<vd_guids.length() ; i++ )
    {
        if( curr_DesktopGUID==vd_guids[i] )
        {
            return i+1;
        }
    }

    return -1;
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

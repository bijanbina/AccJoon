#ifndef MM_WIN32_GUID_H
#define MM_WIN32_GUID_H

#include <QDebug>
#include <windows.h>
#include <initguid.h>

#define MM_REG_CURRVER  "HKLM\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"
#define MM_REG_DISPVER  "DisplayVersion"
#define MM_REG_BUILDNUM "CurrentBuildNumber"

#define MM_WIN10        0
#define MM_WIN11_21H2   1

const IID IID_IVirtualDesktopManagerInternal_Win10 = {
    0xf31574d6, 0xb682, 0x4cdc, {0xbd, 0x56, 0x18, 0x27, 0x86, 0x0a, 0xbe, 0xc6} };

const IID IID_IVirtualDesktopManagerInternal_Win11_21H2 = {
    0xB2F925B9, 0x5A0F, 0x4D2E, {0x9F, 0x4D, 0x2B, 0x15, 0x07, 0x59, 0x3C, 0x10} };

const GUID UUID_IVirtualDesktop_Win10 = {
    0xFF72FFDD, 0xBE7E, 0x43FC, {0x9C, 0x03, 0xAD, 0x81, 0x68, 0x1E, 0x88, 0xE4} };

const GUID UUID_IVirtualDesktop_Win11_21H2 = {
    0x536D3495, 0xB208, 0x4CC9, {0xAE, 0x26, 0xDE, 0x81, 0x11, 0x27, 0x5B, 0xF8} };

QString mm_getReg(QString reg_path, QString reg_name);
int mm_getWinVer();

#endif // MM_WIN32_GUID_H

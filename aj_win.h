#ifndef AJWIN_H
#define AJWIN_H

#include <QString>
#include <QtDebug>

#include <oleacc.h>
#include <winbase.h>
#include <windows.h>
#include <psapi.h> // For access to GetModuleFileNameEx
#include <tlhelp32.h> // to get application pid
#include <tchar.h> // to get application file path

#define AJ_CMD_LMB     0 //Left Mouse Button
#define AJ_CMD_RMB     1
#define AJ_CMD_MMB     2
#define AJ_CMD_DCLICK  3 // Double Click
#define AJ_CMD_CHILDID 4 // Show Child ID

#define AJ_MOUSE_DELAY   10
#define AJ_DOUBLE_DELAY  3

class AjWin
{
public:
    AjWin(QString acc_path, QString cmd, QString accName, int o_x, int o_y);
    int setWinSpec();
    int setObjSpec();
    void doClick();

private:
    QString getAccName(IAccessible *pAcc, long childId);
    long getChildCount(IAccessible *pAcc);
    IAccessible* getActiveWinPAcc();
    IAccessible* getAcc(QStringList varpath, IAccessible *pAcc);
    IAccessible* getAccName(QString name, IAccessible *pAcc);

    void listChildren(IAccessible *pAcc, QString path);

    HWND active_window;
    IAccessible *active_win_pAcc;
    QString window_title;
    QString acc_name;
    QStringList path;
    int cmd_type;
    int obj_center_y;
    int obj_center_x;

    int offset_x;
    int offset_y;
    POINT cursor_last;
};

int aj_clickType(QString click_short_name);
QString aj_click_name(int cmd_type);

#endif // AJWIN_H

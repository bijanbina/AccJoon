#include "mm_win32_guid.h"
#include <QSettings>

QString mm_getReg(QString reg_path, QString reg_name)
{
    QSettings reg(reg_path, QSettings::Registry64Format);
    QString val = reg.value(reg_name).toString();
    return val;
}

int mm_getWinVer()
{
    QString display_ver = mm_getReg(MM_REG_CURRVER, MM_REG_DISPVER);
    QString build_num   = mm_getReg(MM_REG_CURRVER, MM_REG_BUILDNUM);

    if( display_ver=="22H2" && build_num=="19045" )
    {
        return MM_WIN10;
    }
    else if( display_ver=="21H2" && build_num=="22000" )
    {
        return MM_WIN11_21H2;
    }
    else
    {
        return -1;
    }
}

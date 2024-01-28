#include "aj_scheduler.h"
#include <QDir>

int aj_isExistTsk(QString name)
{
    QString cmd = "schtasks /Query /TN \"" + name + "\" >nul 2>&1";
    int ret = system(cmd.toStdString().c_str());
    return ret;
}

void aj_createTsk(QString name)
{
    QString xml_path = QDir::currentPath();
    xml_path += "/Resources/Mom.xml";
    xml_path.replace("/", QDir::separator());
    QString cmd = "schtasks /Create /XML \"" + xml_path + "\" /TN \"" +
            name + "\" >nul 2>&1";
    system(cmd.toStdString().c_str());
}

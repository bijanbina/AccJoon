#include "aj_dllgen.h"
#include <QDir>
#include <QDebug>

AjDllGen::AjDllGen(QString bat_name)
{
    QString project_path = QDir::currentPath();
    project_path.replace("/", "\\");
#ifdef QT_DEBUG
    project_path += "\\debug";
#else
    project_path += "\\release";
#endif

    QDir directory(project_path);
    QStringList dll_files = directory.entryList(QStringList() << "*.dll", QDir::Files);
    if( dll_files.size()>0 )
    {
        qDebug() << "Info: DLLs are already generated";
        return;
    }

    project_path += "\\" + bat_name;
    bat_file = new QFile(project_path);
    if( !bat_file->open(QIODevice::WriteOnly |
                        QIODevice::Text) )
    {
        qDebug() << "Error: cannot open conf file" << bat_file;
        return;
    }
    fillBatFile();
    bat_file->close();
}

void AjDllGen::fillBatFile()
{
    QString qt_compiler_path = getQtCompiler();
    bat_file->write("set PATH=%PATH%;");
    bat_file->write(qt_compiler_path.toStdString().c_str());
    bat_file->write("\nwindeployqt ");
    QString project_path = QDir::currentPath();
    project_path.replace("/", "\\");
//    bat_file->write(project_path.toStdString().c_str());
//    bat_file->write("\\Sources ");
#ifdef QT_DEBUG
    project_path += "\\debug";
#else
    project_path += "\\release";
#endif
    bat_file->write(project_path.toStdString().c_str());
}

QString AjDllGen::getQtCompiler()
{
    // C:\Qt
    QString qt_compiler = getQtPath();
    // Qt5.7.0
    QString qt_dir = findDir("Qt", qt_compiler);
    // C:\Qt\Qt5.7.0\ -
    qt_compiler += "\\" + qt_dir + "\\";
    // 5.7.0
    qt_dir = qt_dir.mid(2);
    // C:\Qt\Qt5.7.0\5.7.0
    qt_compiler += qt_dir;
    // C:\Qt\Qt5.7.0\5.7\mingw53_32\bin
    qt_compiler += "\\" + findDir("mingw", qt_compiler) + "\\bin";
    return qt_compiler;
}

QString AjDllGen::getQtPath()
{
    QString qt_path;
    // get qt creator path
    AjWin32Launcher *win_launcher = new AjWin32Launcher(SHORTCUT_QT);
    qt_path = win_launcher->link_path;
    if( qt_path.isEmpty() )
    {
        return "";
    }
    // 2-level parent dir
    int index = qt_path.lastIndexOf("\\");
    qt_path = qt_path.mid(0, index);
    index = qt_path.lastIndexOf("\\");
    qt_path = qt_path.mid(0, index);
    index = qt_path.lastIndexOf("\\");
    qt_path = qt_path.mid(0, index);

    return qt_path;
}

QString AjDllGen::findDir(QString pattern, QString dirname)
{
    QDir dir(dirname);
    dir.setFilter(QDir::Dirs | QDir::NoSymLinks |
                  QDir::NoDot | QDir::NoDotDot);

    foreach(QFileInfo fileInfo, dir.entryList()) {
        if( fileInfo.filePath().size()>1 )
        {
            if( fileInfo.filePath().mid(0, pattern.size())==pattern )
            {
                return fileInfo.filePath();
            }
        }
    }
    return "";
}

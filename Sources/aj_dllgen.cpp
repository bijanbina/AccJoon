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
    qDebug() << "ending" << project_path;
}

void AjDllGen::fillBatFile()
{
    QString qt_compiler_path = getQtCompiler();
    if( qt_compiler_path.isEmpty() )
    {
        qDebug() << "Error: Cannot retreive compiler path";
        return;
    }
    bat_file->write("set PATH=%PATH%;");
    bat_file->write(qt_compiler_path.toStdString().c_str());
    bat_file->write("\nwindeployqt ");
    project_path = QDir::currentPath();
    project_path.replace("/", "\\");
//    bat_file->write(project_path.toStdString().c_str());
//    bat_file->write("\\Sources ");
#ifdef QT_DEBUG
    project_path += "\\debug";
#else
    project_path += "\\release";
#endif
    bat_file->write(project_path.toStdString().c_str());

    tools_path = makeToolsPath();
    if( tools_path.isEmpty() )
    {
        qDebug() << "Error: Cannot retreive "
                    "cp path from compiler path";
        return;
    }
    addToolsLib("libgcc_s_dw2-1.dll");
    addToolsLib("libstdc++-6.dll");
    addToolsLib("libwinpthread-1.dll");
}

QString AjDllGen::getQtCompiler()
{
    // C:\Qt\Qt5.7.0
    QString qt_compiler = getQtPath();
    if( qt_compiler.isEmpty() )
    {
        return "";
    }
    // 5.7.0
    QString qt_dir = getFirstDir(qt_compiler);
    if( qt_dir.isEmpty() )
    {
        return "";
    }
    // C:\Qt\Qt5.7.0\5.7.0
    qt_compiler += "\\" + qt_dir;
    // mingw53_32
    QString compiler = findCompiler("mingw", qt_compiler);
    if( compiler.isEmpty() )
    {
        return "";
    }
    // C:\Qt\Qt5.7.0\5.7.0\mingw53_32\bin
    qt_compiler += "\\" + compiler + "\\bin";
    return qt_compiler;
}

void AjDllGen::addToolsLib(QString lib)
{
    bat_file->write("\ncopy \"");
    bat_file->write(tools_path.toStdString().c_str());
    bat_file->write(lib.toStdString().c_str());
    bat_file->write("\" ");
    bat_file->write(project_path.toStdString().c_str());
}

QString AjDllGen::makeToolsPath()
{
    // D:\Qt\Qt5.13.1\Tools\QtCreator\bin\qtcreator.exe
    int index = creator_path.lastIndexOf("\\");
    QString lib_path = creator_path.mid(0, index);
    // D:\Qt\Qt5.13.1\Tools\QtCreator\bin
    index = lib_path.lastIndexOf("\\");
    lib_path = lib_path.mid(0, index);
    // D:\Qt\Qt5.13.1\Tools\QtCreator
    index = lib_path.lastIndexOf("\\");
    lib_path = lib_path.mid(0, index);
    // D:\Qt\Qt5.13.1\Tools
    QString compiler = findCompiler("mingw", lib_path);
    if( compiler.isEmpty() )
    {
        return "";
    }
    lib_path += "\\" + compiler + "\\bin\\";
    return lib_path;
}

QString AjDllGen::getQtPath()
{
    QString qt_path;
    // get qt creator path
    qt_path = getQtCreator();
    if( qt_path.isEmpty() )
    {
        return "";
    }
    AjWin32Launcher *win_launcher = new AjWin32Launcher(qt_path);
    creator_path = win_launcher->link_path;
    if( creator_path.isEmpty() )
    {
        return "";
    }
    // 3-level parent dir
    // D:\Qt\Qt5.13.1\Tools\QtCreator\bin\qtcreator.exe
    int index = creator_path.lastIndexOf("\\");
    qt_path = creator_path.mid(0, index);
    // D:\Qt\Qt5.13.1\Tools\QtCreator\bin
    index = qt_path.lastIndexOf("\\");
    qt_path = qt_path.mid(0, index);
    // D:\Qt\Qt5.13.1\Tools\QtCreator
    index = qt_path.lastIndexOf("\\");
    qt_path = qt_path.mid(0, index);
    // D:\Qt\Qt5.13.1\Tools
    index = qt_path.lastIndexOf("\\");
    qt_path = qt_path.mid(0, index);
    // D:\Qt\Qt5.13.1

    return qt_path;
}

QString AjDllGen::getQtCreator()
{
    QString start_menu = getenv("APPDATA");
    start_menu += "\\Microsoft\\Windows\\Start Menu\\Programs\\";
    QString qt_shortcut = findQtShortcut(start_menu);
    if( qt_shortcut.isEmpty() )
    {
        start_menu = getenv("PROGRAMDATA");
        start_menu += "\\Microsoft\\Windows\\Start Menu\\Programs\\";
        qt_shortcut = findQtShortcut(start_menu);
    }
    return qt_shortcut;
}

QString AjDllGen::findCompiler(QString pattern, QString dirname)
{
    QDir dir(dirname);
    dir.setFilter(QDir::Dirs | QDir::NoSymLinks |
                  QDir::NoDot | QDir::NoDotDot);

    QString reg_exp;
#ifdef Q_PROCESSOR_X86_64
    reg_exp = "64$";
#else
    reg_exp = "32$";
#endif

    QRegExp ver_reg(reg_exp);

    QFileInfoList file_list = dir.entryInfoList();
    for( int i=0 ; i<file_list.size() ; i++ )
    {
        QFileInfo fileInfo = file_list[i];
        if( fileInfo.fileName().contains(pattern) &&
            fileInfo.fileName().contains(ver_reg) )
        {
            return fileInfo.fileName();
        }
    }
    return "";
}

QString AjDllGen::findQtShortcut(QString dirname)
{
    QDir menu_dir(dirname);
    QRegExp Qt_reg("^Qt");
    menu_dir.setFilter(QDir::Dirs | QDir::NoSymLinks |
                       QDir::NoDot | QDir::NoDotDot);

    QFileInfoList dir_list = menu_dir.entryInfoList();
    for( int i=0 ; i<dir_list.size() ; i++ )
    {
        if( dir_list[i].fileName().contains(Qt_reg) )
        {
//            qDebug() << "find qt" << dir_list[i].fileName();
            QDir qt_dir(dirname + "\\" + dir_list[i].fileName());
            QRegExp creator_reg("^Qt Creator");
            QFileInfoList qt_dir_list = qt_dir.entryInfoList();
            for( int j=0 ; j<qt_dir_list.size() ; j++ )
            {
                if( qt_dir_list[j].fileName().contains(creator_reg) )
                {
//                    qDebug() << "find creator" << qt_dir_list[i].completeBaseName();
                    QString ret = dir_list[i].fileName() + "\\" +
                                  qt_dir_list[j].completeBaseName();
                    return ret;
                }
            }
        }
    }
    return "";
}

QString AjDllGen::getFirstDir(QString path)
{
    QDir menu_dir(path);
    menu_dir.setFilter(QDir::Dirs | QDir::NoSymLinks |
                       QDir::NoDot | QDir::NoDotDot);
    QFileInfoList dir_list = menu_dir.entryInfoList();
    return dir_list[0].fileName();
}

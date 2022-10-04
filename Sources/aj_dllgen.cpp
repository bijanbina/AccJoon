#include "aj_dllgen.h"
#include <QDebug>

void aj_dllGen()
{
    QString project_path = QDir::currentPath();
    project_path.replace("/", "\\");
    QDir directory(project_path);
    QStringList dll_files = directory.entryList(QStringList() << "*.dll", QDir::Files);
    if( dll_files.size()>0 )
    {
        // DLLs are already generated
        return;
    }

    project_path += "\\dll_gen.bat";
    QFile *bat_file = new QFile(project_path);
    if( !bat_file->open(QIODevice::WriteOnly |
                        QIODevice::Text) )
    {
        qDebug() << "Error: cannot open dll_gen file" << bat_file;
        return;
    }
    aj_fillBatFile(bat_file);
    bat_file->close();
//    qDebug() << "ending" << project_path;
}

void aj_fillBatFile(QFile *bat_file)
{
    QString qt_compiler_path = aj_getQtCompiler();
    if( qt_compiler_path.isEmpty() )
    {
        qDebug() << "Error: Cannot retreive compiler path";
        return;
    }
    bat_file->write("set PATH=%PATH%;");
    bat_file->write(qt_compiler_path.toStdString().c_str());
    bat_file->write("\nwindeployqt ");
    QString bin_path = QDir::currentPath();
    bin_path.replace("/", "\\");
//    bat_file->write(project_path.toStdString().c_str());
//    bat_file->write("\\Sources ");
    bat_file->write(bin_path.toStdString().c_str());

    QString tools_path = aj_makeToolsPath();
    if( tools_path.isEmpty() )
    {
        qDebug() << "Error: Cannot retreive "
                    "cp path from compiler path";
        return;
    }
    QStringList libs;
    libs << "libstdc++-6.dll" << "libwinpthread-1.dll";
    libs += aj_listGccCompilers(tools_path);
    for( int i=0 ; i<libs.size() ; i++ )
    {
        bat_file->write("\ncopy \"");
        bat_file->write(tools_path.toStdString().c_str());
        bat_file->write(libs[i].toStdString().c_str());
        bat_file->write("\" ");
        bat_file->write(bin_path.toStdString().c_str());
    }
}

QString aj_getQtCompiler()
{
    // C:\Qt\Qt5.7.0
    QString qt_compiler = aj_getQtPath();
    if( qt_compiler.isEmpty() )
    {
        return "";
    }
    // 5.7.0
    QString qt_dir = aj_getFirstDir(qt_compiler);
    if( qt_dir.isEmpty() )
    {
        return "";
    }
    // C:\Qt\Qt5.7.0\5.7.0
    qt_compiler += "\\" + qt_dir;
    // mingw53_32
    QString compiler = aj_findCompiler("mingw", qt_compiler);
    if( compiler.isEmpty() )
    {
        return "";
    }
    // C:\Qt\Qt5.7.0\5.7.0\mingw53_32\bin
    qt_compiler += "\\" + compiler + "\\bin";
    return qt_compiler;
}

QString aj_makeToolsPath()
{
    QString creator_path = aj_getQtCreator();
    if( creator_path.isEmpty() )
    {
        return "";
    }
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
    QString compiler = aj_findCompiler("mingw", lib_path);
    if( compiler.isEmpty() )
    {
        return "";
    }
    lib_path += "\\" + compiler + "\\bin\\";
    return lib_path;
}

QString aj_getQtPath()
{
    QString creator_path = aj_getQtCreator();
    if( creator_path.isEmpty() )
    {
        return "";
    }
    // 3-level parent dir
    // D:\Qt\Qt5.13.1\Tools\QtCreator\bin\qtcreator.exe
    int index = creator_path.lastIndexOf("\\");
    QString qt_path = creator_path.mid(0, index);
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

QString aj_getQtShortCut()
{
    QString start_menu = getenv("APPDATA");
    start_menu += "\\Microsoft\\Windows\\Start Menu\\Programs\\";
    QString qt_shortcut = aj_findQtShortcut(start_menu);
    if( qt_shortcut.isEmpty() )
    {
        start_menu = getenv("PROGRAMDATA");
        start_menu += "\\Microsoft\\Windows\\Start Menu\\Programs\\";
        qt_shortcut = aj_findQtShortcut(start_menu);
    }
    return qt_shortcut;
}

QString aj_getQtCreator()
{
    QString qt_path;
    // get qt creator path
    qt_path = aj_getQtShortCut();
    if( qt_path.isEmpty() )
    {
        return "";
    }
    AjWin32Launcher *win_launcher = new AjWin32Launcher(qt_path);
    QString creator_path = win_launcher->link_path;
    return creator_path;
}

QStringList aj_listGccCompilers(QString tools_path)
{
    QStringList compilers;
    QFileInfoList file_list = aj_searchDir(tools_path, "^libgcc_",
                                   QDir::Files | QDir::NoSymLinks |
                                   QDir::NoDot | QDir::NoDotDot);

    for( int i=0 ; i<file_list.size() ; i++ )
    {
        compilers.push_back(file_list[i].fileName());
    }
    return compilers;
}

QString aj_findCompiler(QString pattern, QString dirname)
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

QString aj_findQtShortcut(QString dirname)
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
            QDir qt_dir(dirname + "\\" + dir_list[i].fileName());
            QRegExp creator_reg("^Qt Creator");
            QFileInfoList qt_dir_list = qt_dir.entryInfoList();
            for( int j=0 ; j<qt_dir_list.size() ; j++ )
            {
                if( qt_dir_list[j].fileName().contains(creator_reg) )
                {
                    QString ret = dir_list[i].fileName() + "\\" +
                                  qt_dir_list[j].completeBaseName();
                    return ret;
                }
            }
        }
    }
    return "";
}

QString aj_getFirstDir(QString path)
{
    QDir menu_dir(path);
    menu_dir.setFilter(QDir::Dirs | QDir::NoSymLinks |
                       QDir::NoDot | QDir::NoDotDot);
    QFileInfoList dir_list = menu_dir.entryInfoList();
    return dir_list[0].fileName();
}

QStringList aj_getConfList()
{
    QStringList ret;

    QString project_path = QDir::currentPath();
    // D:\Work\bijan\AccJoon\release
    project_path.replace("/", "\\");
    project_path += "\\Conf";
    // D:\Work\bijan\AccJoon\conf

    QFileInfoList conf_list = aj_searchDir(project_path, ".acc$",
                 QDir::Files | QDir::NoSymLinks |
                 QDir::NoDot | QDir::NoDotDot);
    for( int i=0; i<conf_list.size(); i++ )
    {
        ret.push_back(conf_list[i].absoluteFilePath().replace("/", "\\"));
    }
    return ret;
}

QFileInfoList aj_searchDir(QString path, QString pattern,
                           QDir::Filters filter)
{
    QFileInfoList ret;
    QDir directory(path);
    QRegExp Qt_reg(pattern);

    if( directory.exists() )
    {
        directory.setFilter(filter);
        QFileInfoList file_list = directory.entryInfoList();

        for( int i=0 ; i<file_list.size() ; i++ )
        {
            if( file_list[i].fileName().contains(Qt_reg) )
            {
                ret.push_back(file_list[i]);
            }
        }
    }
    else
    {
        qDebug() << "Error: Directory doesnt exist.";
    }
    return ret;
}

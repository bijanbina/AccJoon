#include "aj_lua.h"
#include <QtDebug>
#include <QDir>
#include <QThread>

AjLua::AjLua()
{
    lst = luaL_newstate();
    luaL_openlibs(lst);
}

void AjLua::run(QList<AjLuaInfo> lua_list)
{
    for( int i=0; i<lua_list.size(); i++ )
    {
        QThread::msleep(lua_list[i].delay);
        this->run(lua_list[i].path);
    }
}

void AjLua::run(QString path)
{
    if(path.isEmpty())
    {
        return;
    }
    QString name;
    QString current_dir = QDir::currentPath();
    // split name from path
    int index_name = path.lastIndexOf("\\")+1;
    if( index_name>=0 )
    {
        name = path.mid(index_name);
        path.remove(index_name-1, path.size()-index_name);
    }
    // .lua file is in same dir with .exe
    else
    {
        name = path;
        path = "";
    }
    QDir::setCurrent(current_dir+path);

    qDebug() << "path" << current_dir+path << "filename" << name;

    luaL_loadfile(lst, name.toStdString().c_str());
    lua_pcall(lst, 0, LUA_MULTRET, 0);

    QDir::setCurrent(current_dir);
}

AjLua::~AjLua()
{
    lua_close(lst);
}

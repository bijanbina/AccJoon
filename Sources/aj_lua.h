#ifndef AJ_LUA_H
#define AJ_LUA_H

#include <QString>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

typedef struct AjLuaInfo
{
    QString path;
    int delay;
}AjLuaInfo;

class AjLua
{
public:
    explicit AjLua();
    void run(QList<AjLuaInfo> lua_list);
    void run(QString path);
    ~AjLua();

private:
    lua_State *lst;
};

#endif // AJ_LUA_H

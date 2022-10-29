#ifndef AJ_LUA_H
#define AJ_LUA_H

#include <QString>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

class AjLua
{
public:
    explicit AjLua();
    void run(QString path);
    ~AjLua();

private:
    lua_State *lst;
};

#endif // AJ_LUA_H

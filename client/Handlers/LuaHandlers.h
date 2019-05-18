#pragma once
#include "../NovusTypes.h"
#include "../FunctionTypeDefs.h"

namespace LuaHandlers
{
    int Debug_ToggleTerrain(WowFunc::Lua::lua_State* state)
    {
        bool result = WowFunc::Graphics::ToggleTerrain();
        WowFunc::Lua::PushNumber(state, result);
        return 1;
    }
    int Debug_ToggleTriangles(WowFunc::Lua::lua_State* state)
    {
        bool result = WowFunc::Graphics::ToggleTriangles();
        WowFunc::Lua::PushNumber(state, result);
        return 1;
    }

    int GetGuidByToken(WowFunc::Lua::lua_State* state)
    {
        std::string token(WowFunc::Lua::GetString(state, 1, 0));
        u64 targetGuid = WowFunc::Script::GetGuidByToken(token.c_str());

        WowFunc::Lua::PushNumber(state, static_cast<f64>(targetGuid));
        return 1;
    }

    int SetFocusByToken(WowFunc::Lua::lua_State* state)
    {
        std::string token(WowFunc::Lua::GetString(state, 1, 0));
        WowFunc::RunLua("FocusUnit(\"" + token + "\")");
        return 1;
    }
}
#pragma once
#include "../NovusTypes.h"
#include "../FunctionTypeDefs.h"
#include "../WowStructs/DataStore.h"

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

    int GM_SetSpeed(WowFunc::Lua::lua_State* state)
    {
        f32 result = static_cast<f32>(WowFunc::Lua::GetNumber(state, 1));

        if (result < 1)
        {
            result = 1;
        }
        else if (result > 50)
        {
            result = 50;
        }

        DataStore* dataStore = new DataStore(Opcode::MSG_MOVE_SET_ALL_SPEED_CHEAT);
        dataStore->PutFloat(result);
        dataStore->SendPacket();

        return 1;
    }
    int GM_ToggleFlying(WowFunc::Lua::lua_State* state)
    {
        bool result = WowFunc::Lua::GetBool(state, 1);

        DataStore* dataStore = new DataStore(result ? Opcode::CMSG_MOVE_START_SWIM_CHEAT : Opcode::CMSG_MOVE_STOP_SWIM_CHEAT);
        dataStore->SendPacket();

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
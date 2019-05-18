#pragma once
#include "../NovusTypes.h"
#include "../Hook/FunctionHook.h"
#include "../FunctionTypeDefs.h"
#include "../Utils/StringUtils.h"
#include "CommandHandlers.h"
#include "LuaHandlers.h"

#include <string>
#include <vector>

FunctionHook<void(*)()>* GameClientCommandsInstallHook = nullptr;
FunctionHook<void(*)()>* GameClientCommandsUninstallHook = nullptr;
FunctionHook<i32(*)(char*, i32, i32)>* SendChatMessageHook = nullptr;
FunctionHook<i32(*)()>* LoadScriptFunctionsHook = nullptr;
FunctionHook<i32(*)()>* UnloadScriptFunctionsHook = nullptr;

namespace FunctionHandlers
{
    void GMClientHooksInstall()
    {
        GameClientCommandsInstallHook->Hook();
        GameClientCommandsUninstallHook->Hook();
        LoadScriptFunctionsHook->Hook();
        UnloadScriptFunctionsHook->Hook();
    }
    void GMClientHooksUninstall()
    {
        GameClientCommandsInstallHook->Unhook();
        GameClientCommandsUninstallHook->Unhook();
        SendChatMessageHook->Unhook();
        LoadScriptFunctionsHook->Unhook();
        UnloadScriptFunctionsHook->Unhook();
    }

    void GameClientCommandsInstall()
    {
        GameClientCommandsInstallHook->Unhook();
        GameClientCommandsInstallHook->OriginalFunction();
        GameClientCommandsInstallHook->Hook();

        CommandHandlers::Install();
        SendChatMessageHook->Hook();
    }
    void GameClientCommandsUninstall()
    {
        GameClientCommandsUninstallHook->Unhook();
        GameClientCommandsUninstallHook->OriginalFunction();
        GameClientCommandsUninstallHook->Hook();

        CommandHandlers::Uninstall();
        SendChatMessageHook->Unhook();
    }

    i32 SendChatMessage(char* message, i32 unk, i32 textSize)
    {
        i32 result = 0;
        if (message[0] == '!')
        {
            std::vector<std::string> splitCommandString = StringUtils::SplitString(message);
            if (splitCommandString[0] == "!bug")
            {
                if (splitCommandString.size() > 1)
                {
                    std::string description = "";
                    for (size_t i = 1; i < splitCommandString.size(); i++)
                    {
                        description += splitCommandString[i];

                        if (i != splitCommandString.size() - 1)
                            description += " ";
                    }

                    CommandHandlers::SendBug("bug", description.c_str());
                }
                else
                {
                    WowFunc::Print("Failed to send Bug Report, you must provide a description.");
                }
                return result;
            }
            else if (splitCommandString[0] == "!getposition")
            {
                CommandHandlers::GetPosition();
                return result;
            }
        }

        SendChatMessageHook->Unhook();
        result = SendChatMessageHook->OriginalFunction(message, unk, textSize);
        SendChatMessageHook->Hook();

        return result;
    }

    i32 LoadScriptFunctions()
    {
        LoadScriptFunctionsHook->Unhook();
        LoadScriptFunctionsHook->OriginalFunction();
        LoadScriptFunctionsHook->Hook();

        WowFunc::Lua::RegisterFunction("Debug_ToggleTerrain", LuaHandlers::Debug_ToggleTerrain);
        WowFunc::Lua::RegisterFunction("Debug_ToggleTriangles", LuaHandlers::Debug_ToggleTriangles);
        WowFunc::Lua::RegisterFunction("SetFocusByToken", LuaHandlers::SetFocusByToken);

        return 1;
    }

    i32 UnloadScriptFunctions()
    {
        UnloadScriptFunctionsHook->Unhook();
        UnloadScriptFunctionsHook->OriginalFunction();
        UnloadScriptFunctionsHook->Hook();

        WowFunc::Lua::UnregisterFunction("Debug_ToggleTerrain");
        WowFunc::Lua::UnregisterFunction("Debug_ToggleTriangles");
        WowFunc::Lua::UnregisterFunction("SetFocusByToken");

        return 1;
    }

    void HandleQueryObjectPosition(void* param, Opcode opcode, u32 time, DataStore* dataStore)
    {
        f32 x = 0, y = 0, z = 0;

        dataStore->GetFloat(x);
        dataStore->GetFloat(y);
        dataStore->GetFloat(z);

        char str[256];
        i32 length = StringUtils::FormatString(str, sizeof(str), "Object Position(%f, %f, %f)", x, y, z);
        WowFunc::Print(str);
    }

    void Setup()
    {
        GameClientCommandsInstallHook = new FunctionHook<void(*)()>(WowFunc::Console::InstallCommands, FunctionHandlers::GameClientCommandsInstall);
        GameClientCommandsUninstallHook = new FunctionHook<void(*)()>(WowFunc::Console::UninstallCommands, FunctionHandlers::GameClientCommandsUninstall);
        SendChatMessageHook = new FunctionHook<i32(*)(char*, i32, i32)>(WowFunc::SendChatMessage, FunctionHandlers::SendChatMessage);
        LoadScriptFunctionsHook = new FunctionHook<i32(*)()>(WowFunc::FrameScript::LoadScriptFunctions, FunctionHandlers::LoadScriptFunctions);
        UnloadScriptFunctionsHook = new FunctionHook<i32(*)()>(WowFunc::FrameScript::UnloadScriptFunctions, FunctionHandlers::UnloadScriptFunctions);

        FunctionHandlers::GMClientHooksInstall();
        WowFunc::ClientService::SetMessageHandler(Opcode::SMSG_QUERY_OBJECT_POSITION, FunctionHandlers::HandleQueryObjectPosition, 0);

        WowFunc::Console::Printf("NovusCore Initialized\n");
    }
}
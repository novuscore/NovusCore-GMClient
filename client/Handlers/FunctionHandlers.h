#pragma once
#include "../NovusTypes.h"
#include "../Hook/FunctionHook.h"
#include "../FunctionTypeDefs.h"
#include "../Utils/StringUtils.h"
#include "CommandHandlers.h"

#include <string>
#include <vector>

FunctionHook<void(*)()>* GameClientCommandsInstallHook = nullptr;
FunctionHook<void(*)()>* GameClientCommandsUninstallHook = nullptr;
FunctionHook<int(*)(char*, i32, i32)>* SendChatMessageHook = nullptr;

namespace FunctionHandlers
{
    void GameInstallHooks()
    {
        GameClientCommandsInstallHook->Hook();
        GameClientCommandsUninstallHook->Hook();
    }
    void GMClientHooksUninstall()
    {
        GameClientCommandsInstallHook->Unhook();
        GameClientCommandsUninstallHook->Unhook();
        SendChatMessageHook->Unhook();
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

    int SendChatMessage(char* message, i32 unk, i32 textSize)
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
                    WowFunc::ChatConsolePrint("Failed to send Bug Report, you must provide a description.");
                }
            }
            else if (splitCommandString[0] == "!getposition")
            {
                CommandHandlers::GetPosition();
            }
        }
        else
        {
            SendChatMessageHook->Unhook();
            result = SendChatMessageHook->OriginalFunction(message, unk, textSize);
            SendChatMessageHook->Hook();
        }

        return result;
    }

    void HandleQueryObjectPosition(void* param, Opcode opcode, u32 time, DataStore* dataStore)
    {
        f32 x = 0, y = 0, z = 0;

        dataStore->GetFloat(x);
        dataStore->GetFloat(y);
        dataStore->GetFloat(z);


        char str[256];
        i32 length = StringUtils::FormatString(str, sizeof(str), "Object Position(%f, %f, %f)", x, y, z);
        WowFunc::ChatConsolePrint(str);
    }

    void Setup()
    {
        GameClientCommandsInstallHook = new FunctionHook<void(*)()>(WowFunc::GameClientCommandsInstall, FunctionHandlers::GameClientCommandsInstall);
        GameClientCommandsUninstallHook = new FunctionHook<void(*)()>(WowFunc::GameClientCommandsUninstall, FunctionHandlers::GameClientCommandsUninstall);
        SendChatMessageHook = new FunctionHook<i32(*)(char*, i32, i32)>(WowFunc::SendChatMessage, FunctionHandlers::SendChatMessage);

        FunctionHandlers::GameInstallHooks();

        WowFunc::SetMessageHandler(Opcode::SMSG_QUERY_OBJECT_POSITION, FunctionHandlers::HandleQueryObjectPosition, 0);
        WowFunc::ConsolePrint("NovusCore Initialized\n");
    }
}
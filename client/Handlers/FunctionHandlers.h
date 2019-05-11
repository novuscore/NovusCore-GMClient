#pragma once
#include "NovusTypes.h"
#include "Hook/FunctionHook.h"
#include "FunctionTypeDefs.h"
#include "CommandHandlers.h"

FunctionHook<void(*)()>* _GameClientCommandsInstalling = nullptr;
FunctionHook<void(*)()>* _GameClientCommandsUninstalling = nullptr;

namespace FunctionHandlers
{
    void GameClientCommandsInstalling()
    {
        _GameClientCommandsInstalling->Unhook();
        _GameClientCommandsInstalling->OriginalFunction();
        _GameClientCommandsInstalling->Hook();

        CommandHandlers::Install();
    }
    void GameClientCommandsUninstalling()
    {
        _GameClientCommandsUninstalling->Unhook();
        _GameClientCommandsUninstalling->OriginalFunction();
        _GameClientCommandsUninstalling->Hook();

        CommandHandlers::Uninstall();
    }

    void Handle_QueryObjectPosition(void* param, Opcode opcode, u32 time, DataStore* dataStore)
    {
        f32 x = 0, y = 0, z = 0;

        dataStore->GetFloat(x);
        dataStore->GetFloat(y);
        dataStore->GetFloat(z);

        WowFunc::ConsolePrint("Object Position (%f, %f, %f)", x, y, z);
    }

    void Setup()
    {
        _GameClientCommandsInstalling = new FunctionHook<void(*)()>(WowFunc::GameClientCommandsInstall, GameClientCommandsInstalling);
        _GameClientCommandsUninstalling = new FunctionHook<void(*)()>(WowFunc::GameClientCommandsUninstall, GameClientCommandsUninstalling);

        _GameClientCommandsInstalling->Hook();
        _GameClientCommandsUninstalling->Hook();

        WowFunc::SetMessageHandler(Opcode::SMSG_QUERY_OBJECT_POSITION, Handle_QueryObjectPosition, 0);

        WowFunc::ConsolePrint("NovusCore Initialized\n");
    }
}
#pragma once
#include "../NovusTypes.h"
#include "FunctionHook.h"
#include "FunctionTypeDefs.h"
#include <stdio.h>

FunctionHook<void(*)()>* _GameClientCommandsInstalling = nullptr;
FunctionHook<void(*)()>* _GameClientCommandsUninstalling = nullptr;

namespace ConsoleCommandHandlers
{
    void GetPosition()
    {
        DataStore* dataStore = new DataStore(Opcode::CMSG_QUERY_OBJECT_POSITION);
        dataStore->SendPacket();
    }
}

namespace FunctionHandlers
{
    void GameClientCommandsInstalling()
    {
        WowFunc::ConsolePrint("Called GameClientCommandsInstalling\n");

        _GameClientCommandsInstalling->Unhook();
        _GameClientCommandsInstalling->OriginalFunction();
        _GameClientCommandsInstalling->Hook();

        WowFunc::RegisterConsoleCommand("GetPosition", ConsoleCommandHandlers::GetPosition, CATEGORY_DEBUG, "request Player position from Server");
    }
    void GameClientCommandsUninstalling()
    {
        WowFunc::ConsolePrint("Called GameClientCommandsUninstalling\n");

        _GameClientCommandsUninstalling->Unhook();
        _GameClientCommandsUninstalling->OriginalFunction();
        _GameClientCommandsUninstalling->Hook();

        WowFunc::UnregisterConsoleCommand("GetPosition");
    }

    void SMSG_QUERY_OBJECT_POSITION(void* param, Opcode opcode, u32 time, DataStore* dataStore)
    {
        f32 x = 0, y = 0, z = 0;

        dataStore->GetFloat(x);
        dataStore->GetFloat(y);
        dataStore->GetFloat(z);

        WowFunc::ConsolePrint("Object Position (%f, %f, %f)", x, y, z);
    }

    void Initialize()
    {
        _GameClientCommandsInstalling = new FunctionHook<void(*)()>(WowFunc::GameClientCommandsInstall, GameClientCommandsInstalling);
        _GameClientCommandsUninstalling = new FunctionHook<void(*)()>(WowFunc::GameClientCommandsUninstall, GameClientCommandsUninstalling);

        _GameClientCommandsInstalling->Hook();
        _GameClientCommandsUninstalling->Hook();

        WowFunc::SetMessageHandler(Opcode::SMSG_QUERY_OBJECT_POSITION, SMSG_QUERY_OBJECT_POSITION, 0);
        WowFunc::ConsolePrint("NovusCore Initialized\n");
    }
}
#pragma once
#include "../NovusTypes.h"
#include "../NovusEnums.h"
#include "WowStructs/DataStore.h"

namespace CommandHandlers
{
    void GetPosition()
    {
        DataStore* dataStore = new DataStore(Opcode::CMSG_QUERY_OBJECT_POSITION);
        dataStore->SendPacket();
    }

    void SendBug(const char* command, const char* description)
    {
        WowFunc::SendBug(0, description);
    }


    void Install()
    {
        WowFunc::RegisterConsoleCommand("GetPosition", GetPosition, CATEGORY_DEBUG, "request client position from server");
        WowFunc::RegisterConsoleCommand("bug", SendBug, CATEGORY_DEBUG, "reports a bug to the server");
    }
    void Uninstall()
    {
        WowFunc::UnregisterConsoleCommand("GetPosition");
    }
}
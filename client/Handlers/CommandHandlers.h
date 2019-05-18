#pragma once
#include "../NovusTypes.h"
#include "../NovusEnums.h"
#include "../WowStructs/DataStore.h"

#include <algorithm>

namespace CommandHandlers
{
    void GetPosition()
    {
        DataStore* dataStore = new DataStore(Opcode::CMSG_QUERY_OBJECT_POSITION);
        dataStore->SendPacket();
    }

    void SendBug(const char* command, const char* description)
    {
        std::string desc(description);
        desc.erase(std::remove_if(desc.begin(), desc.end(), ::isspace), desc.end());

        if (desc.length() > 0)
        {

            WowFunc::SendBug(0, description);
            WowFunc::Chat::Print("Sent bug Report to server.");
        }
        else
        {
            WowFunc::Chat::Print("Failed to send Bug Report, you must provide a description.");
        }
    }

    void RunLua(const char* command, const char* description)
    {
        WowFunc::RunLua(description);
    }

    void Install()
    {
        WowFunc::Console::RegisterCommand("GetPosition", GetPosition, CATEGORY_DEBUG, "request client position from server");
        WowFunc::Console::RegisterCommand("Bug", SendBug, CATEGORY_DEBUG, "reports a bug to the server with a specified description");

        /* Development Purposes */
        WowFunc::Console::RegisterCommand("RunLua", RunLua, CATEGORY_DEBUG, "run a lua string");
    }
    void Uninstall()
    {
        WowFunc::Console::UnregisterCommand("GetPosition");
        WowFunc::Console::UnregisterCommand("Bug");
        WowFunc::Console::UnregisterCommand("RunLua");
    }
}
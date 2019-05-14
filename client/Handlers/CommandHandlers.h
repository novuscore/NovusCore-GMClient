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
            WowFunc::ChatConsolePrint("Sent bug Report to server.");
        }
        else
        {
            WowFunc::ChatConsolePrint("Failed to send Bug Report, you must provide a description.");
        }
    }

    void CastBlink()
    {
        WowFunc::RunLua("CastSpellByID(1953)");
    }

    void Install()
    {
        WowFunc::RegisterConsoleCommand("GetPosition", GetPosition, CATEGORY_DEBUG, "request client position from server");
        WowFunc::RegisterConsoleCommand("Bug", SendBug, CATEGORY_DEBUG, "reports a bug to the server with a specified description");

        /* Development Purposes */
        WowFunc::RegisterConsoleCommand("Blink", CastBlink, CATEGORY_DEBUG, "cast blink");
    }
    void Uninstall()
    {
        WowFunc::UnregisterConsoleCommand("GetPosition");
        WowFunc::UnregisterConsoleCommand("Bug");
        WowFunc::UnregisterConsoleCommand("Blink");
    }
}
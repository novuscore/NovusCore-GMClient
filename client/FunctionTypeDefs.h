#pragma once
#include "NovusTypes.h"
#include "NovusEnums.h"
#include "Offsets.h"

#include <string>

namespace WowFunc
{
    typedef void FuncSendBug(i32 type, const char* description);
    typedef int FuncSendChatMessage(char* message, i32 unk, i32 textSize);

    FuncSendBug* SendBug = (FuncSendBug*)Offsets::SendBugOpcode;
    FuncSendChatMessage* SendChatMessage = (FuncSendChatMessage*)Offsets::SendChatMessage;

    namespace Console
    {
        DWORD* IsActive = reinterpret_cast<DWORD*>(Offsets::IsConsoleActive);
        DWORD OriginalActiveState = *IsActive;

        typedef void FuncConsoleScreenInitialize();
        typedef int FuncConsoleCommandRegister(const char* command, void* handler, CommandCategory category, char const* help);
        typedef int FuncConsoleCommandUnregister(const char* command);
        typedef void FuncGameClientCommandsInstall();
        typedef void FuncGameClientCommandsUninstall();
        typedef void FuncConsolePrintF(const char* text, ...);

        FuncConsoleScreenInitialize* Initialize = (FuncConsoleScreenInitialize*)Offsets::ConsoleScreenInitialize;
        FuncConsoleCommandRegister* RegisterCommand = (FuncConsoleCommandRegister*)Offsets::RegisterConsoleCommand;
        FuncConsoleCommandUnregister* UnregisterCommand = (FuncConsoleCommandUnregister*)Offsets::UnregisterConsoleCommand;
        FuncGameClientCommandsInstall* InstallCommands = (FuncGameClientCommandsInstall*)Offsets::GameClientCommandsInstall;
        FuncGameClientCommandsUninstall* UninstallCommands = (FuncGameClientCommandsUninstall*)Offsets::GameClientCommandsUninstall;
        FuncConsolePrintF* Printf = (FuncConsolePrintF*)Offsets::ConsolePrint;

        void SetActive(bool state)
        {
            *reinterpret_cast<DWORD*>(Offsets::IsConsoleActive) = state;
        }
        void SetKey(char key)
        {
            *reinterpret_cast<DWORD*>(Offsets::ConsoleKey) = key;
        }
    }

    namespace FrameScript
    {
        char* Gamestate = reinterpret_cast<char*>(Offsets::Gamestate);
        DWORD TextSectionMinimumValue = 0;
        DWORD TextSectionMaximumValue = 0;

        typedef i32 FuncFrameScriptExecute(const char* message1, const char* message2, DWORD unk);
        typedef i32 FuncLoadScriptFunctions();
        typedef i32 FuncUnloadScriptFunctions();

        FuncFrameScriptExecute* Execute = (FuncFrameScriptExecute*)Offsets::FrameScriptExecute;
        FuncLoadScriptFunctions* LoadScriptFunctions = (FuncLoadScriptFunctions*)Offsets::LoadScriptFunctions;
        FuncUnloadScriptFunctions* UnloadScriptFunctions = (FuncUnloadScriptFunctions*)Offsets::UnloadScriptFunctions;

        void PatchInvalidPointerCheck()
        {
            TextSectionMinimumValue = *reinterpret_cast<DWORD*>(Offsets::TextSectionMinimumAddress);
            TextSectionMaximumValue = *reinterpret_cast<DWORD*>(Offsets::TextSectionMaximumAddress);

            *reinterpret_cast<DWORD*>(Offsets::TextSectionMinimumAddress) = 1;
            *reinterpret_cast<DWORD*>(Offsets::TextSectionMaximumAddress) = 0x7FFFFFFF;
        }
        void RestoreInvalidPointerCheck()
        {
            *reinterpret_cast<DWORD*>(Offsets::TextSectionMinimumAddress) = TextSectionMinimumValue;
            *reinterpret_cast<DWORD*>(Offsets::TextSectionMaximumAddress) = TextSectionMaximumValue;
        }

        bool IsLoginScreen()
        {
            return !strcmp(Gamestate, "login");
        }
    }

    namespace Lua
    {
        typedef struct lua_State lua_State;
        typedef int FuncFrameScriptRegisterFunction(const char* function, void* handler);
        typedef int FuncFrameScriptUnregisterFunction(const char* function);
        typedef int FuncFrameScriptPushNumber(lua_State* luaState, f64 number);
        typedef int FuncFrameScriptPushString(lua_State* luaState, const char* value);
        typedef char* FuncFrameScriptGetString(lua_State* luaState, i32 stackPosition, i32 unk);

        FuncFrameScriptRegisterFunction* RegisterFunction = (FuncFrameScriptRegisterFunction*)Offsets::FrameScriptRegisterFunction;
        FuncFrameScriptUnregisterFunction* UnregisterFunction = (FuncFrameScriptUnregisterFunction*)Offsets::FrameScriptUnregisterFunction;
        FuncFrameScriptPushNumber* PushNumber = (FuncFrameScriptPushNumber*)Offsets::FrameScriptPushNumber;
        FuncFrameScriptPushString* PushString = (FuncFrameScriptPushString*)Offsets::FrameScriptPushString;
        FuncFrameScriptGetString* GetString = (FuncFrameScriptGetString*)Offsets::FrameScriptGetString;
    }

    namespace ClientService
    {
        typedef void FuncClientServicesSetMessageHandler(u16 opcode, void* handler, DWORD param);

        FuncClientServicesSetMessageHandler* SetMessageHandler = (FuncClientServicesSetMessageHandler*)Offsets::ClientServicesSetMessageHandler;
    }

    namespace Script
    {
        typedef u64 FuncGetGuidByToken(const char* token);
        typedef void FuncSetFocusByToken(Lua::lua_State* state);
        typedef i32 FuncSetFocus();

        FuncGetGuidByToken* GetGuidByToken = (FuncGetGuidByToken*)Offsets::GetGuidByToken;
        FuncSetFocusByToken* SetFocusByToken = (FuncSetFocusByToken*)Offsets::SetFocusByToken;
    }

    int RunLua(std::string script)
    {
        return WowFunc::FrameScript::Execute(script.c_str(), "", 0);
    }

    namespace Chat
    {
        void Print(std::string message)
        {
            RunLua("print(\"" + message + "\")");
        }
    }

    void Print(std::string message)
    {
        Chat::Print(message);
        WowFunc::Console::Printf(message.c_str());
    }

    namespace Graphics
    {
        /* Render Flags: 
            1 - Show M2's
            2 - Render Terrain
            3 - Terrain LOD
            5 - Terrain shadows
            6 - Terrain culling / Don't Render WMO's not in LOS
            9 - Show WMO / Toon
            10 - Lights
            11 - Foot prints
            12 - Indoor Light
            13 - Show Portals
            15 - Object distance fade
            16 - Object distance fade ZFill pass
            21 - Render Ground Props (detail doodads)
            22 - Collision Test
            25 - Render Water
            26 - Particulates
            27 - Terrain low detail
            28 - Specular
            30 - WireFrame
            31 - WMO Normals
        */
        enum RenderFlags : u32
        {
            RENDERFLAG_SHOW_M2 = 1 << 0,
            RENDERFLAG_TERRAIN = 1 << 1,
            RENDERFLAG_COLLISION_TEST = 1 << 21,
            RENDERFLAG_TRIANGLES = 1 << 29,
            RENDERFLAG_SHOW_WMO_NORMALS = 1 << 30,
        };
        DWORD* RenderFlags = reinterpret_cast<DWORD*>(Offsets::RenderFlags);

        bool ToggleTerrain()
        {
            if (*RenderFlags & RENDERFLAG_TERRAIN)
            {
                WowFunc::Print("Disabling Terrain");
                *RenderFlags &= ~RENDERFLAG_TERRAIN;
                return false;
            }
            else
            {
                WowFunc::Print("Enabling Terrain");
                *RenderFlags |= RENDERFLAG_TERRAIN;
                return true;
            }
        }
        bool ToggleTris()
        {
            if (*RenderFlags & RENDERFLAG_TRIANGLES)
            {
                WowFunc::Print("Disabling Triangle View");
                *RenderFlags &= ~RENDERFLAG_TRIANGLES;
                return false;
            }
            else
            {
                WowFunc::Print("Enabling Triangle View");
                *RenderFlags |= RENDERFLAG_TRIANGLES;
                return true;
            }
        }
    }
}
#pragma once
#include "NovusTypes.h"
#include "NovusEnums.h"
#include "Offsets.h"

#include <string>

typedef int ConsoleCommandRegister(const char* command, void* handler, CommandCategory category, char const* help);
typedef int ConsoleCommandUnregister(const char* command);
typedef void _GameClientCommandsInstall();
typedef void _GameClientCommandsUninstall();
typedef void ConsolePrintF(const char* text, ...);
typedef int FrameScript_Reload();
typedef void ClientServices_SetMessageHandler(u16 opcode, void* handler, DWORD param);
typedef void _ConsoleScreenInitialize();
typedef void _SendBug(i32 type, const char* description);
typedef int _SendChatMessage(char* message, i32 unk, i32 textSize);
typedef int _FrameScriptExecute(const char* message1, const char* message2, DWORD unk);

namespace WowFunc
{
    ConsoleCommandRegister* RegisterConsoleCommand = (ConsoleCommandRegister*)Offsets::RegisterConsoleCommand;
    ConsoleCommandUnregister* UnregisterConsoleCommand = (ConsoleCommandUnregister*)Offsets::UnregisterConsoleCommand;
    _GameClientCommandsInstall* GameClientCommandsInstall = (_GameClientCommandsInstall*)Offsets::GameClientCommandsInstall;
    _GameClientCommandsUninstall* GameClientCommandsUninstall = (_GameClientCommandsUninstall*)Offsets::GameClientCommandsUninstall;
    ConsolePrintF* ConsolePrint = (ConsolePrintF*)Offsets::ConsolePrint;
    FrameScript_Reload* ReloadUI = (FrameScript_Reload*)Offsets::ReloadUI;
    ClientServices_SetMessageHandler* SetMessageHandler = (ClientServices_SetMessageHandler*)Offsets::ClientServicesSetMessageHandler;
    _ConsoleScreenInitialize* ConsoleScreenInitialize = (_ConsoleScreenInitialize*)Offsets::ConsoleScreenInitialize;
    _SendBug* SendBug = (_SendBug*)Offsets::SendBugOpcode;
    _SendChatMessage* SendChatMessage = (_SendChatMessage*)Offsets::SendChatMessage;
    _FrameScriptExecute* FrameScriptExecute = (_FrameScriptExecute*)Offsets::FrameScriptExecute;

    int RunLua(std::string script)
    {
        return FrameScriptExecute(script.c_str(), "", 0);
    }
    
    void SetConsoleKey(char key)
    {
        *reinterpret_cast<DWORD*>(Offsets::ConsoleKey) = key;
    }
    void ChatPrint(std::string message)
    {
        RunLua("print(\"" + message + "\")");
    }
    void ChatConsolePrint(std::string message)
    {
        ChatPrint(message);
        ConsolePrint(message.c_str());
    }
}
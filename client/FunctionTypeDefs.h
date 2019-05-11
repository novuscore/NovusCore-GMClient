#pragma once
#include "NovusTypes.h"
#include "NovusEnums.h"
#include "Offsets.h"

typedef int ConsoleCommandRegister(const char* command, void* handler, CommandCategory category, char const* help);
typedef int ConsoleCommandUnregister(const char* command);
typedef void _GameClientCommandsInstall();
typedef void _GameClientCommandsUninstall();
typedef void ConsolePrintF(const char* text, ...);
typedef int FrameScript_Reload();
typedef void ClientServices_SetMessageHandler(u16 opcode, void* handler, DWORD param);
typedef void _ConsoleScreenInitialize();
typedef void _SendBug(i32 type, const char* description);

namespace WowFunc
{
    ConsoleCommandRegister* RegisterConsoleCommand = (ConsoleCommandRegister*)Offsets::RegisterConsoleCommandAddress;
    ConsoleCommandUnregister* UnregisterConsoleCommand = (ConsoleCommandUnregister*)Offsets::UnregisterConsoleCommandAddress;
    _GameClientCommandsInstall* GameClientCommandsInstall = (_GameClientCommandsInstall*)Offsets::GameClientCommandsInstallAddress;
    _GameClientCommandsUninstall* GameClientCommandsUninstall = (_GameClientCommandsUninstall*)Offsets::GameClientCommandsUninstallAddress;
    ConsolePrintF* ConsolePrint = (ConsolePrintF*)Offsets::ConsolePrintAddress;
    FrameScript_Reload* ReloadUI = (FrameScript_Reload*)Offsets::ReloadUIAddress;
    ClientServices_SetMessageHandler* SetMessageHandler = (ClientServices_SetMessageHandler*)Offsets::ClientServicesSetMessageHandlerAddress;
    _ConsoleScreenInitialize* ConsoleScreenInitialize = (_ConsoleScreenInitialize*)Offsets::ConsoleScreenInitializeAddress;
    _SendBug* SendBug = (_SendBug*)Offsets::SendBugOpcodeAddress;
}
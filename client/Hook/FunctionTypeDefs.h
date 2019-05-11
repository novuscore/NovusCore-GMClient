#pragma once
#include "../NovusTypes.h"
#include "../WowStructs/DataStore.h"

const u32 RegisterConsoleCommandAddress = 0x769100;
const u32 UnregisterConsoleCommandAddress = 0x7689E0;
const u32 GameClientCommandsInstallAddress = 0x407870;
const u32 GameClientCommandsUninstallAddress = 0x406EF0;
const u32 ConsolePrintAddress = 0x7653B0;
const u32 ReloadUIAddress = 0x401B00;
const u32 ClientServicesSetMessageHandlerAddress = 0x6B0B80;
const u32 ConsoleScreenInitializeAddress = 0x766140;

enum CommandCategory
{
    CATEGORY_DEBUG = 0x0,
    CATEGORY_GRAPHICS = 0x1,
    CATEGORY_CONSOLE = 0x2,
    CATEGORY_COMBAT = 0x3,
    CATEGORY_GAME = 0x4,
    CATEGORY_DEFAULT = 0x5,
    CATEGORY_NET = 0x6,
    CATEGORY_SOUND = 0x7,
    CATEGORY_GM = 0x8,
};
typedef int ConsoleCommandRegister(const char* command, void* handler, CommandCategory category, char const* help);
typedef int ConsoleCommandUnregister(const char* command);
typedef void _GameClientCommandsInstall();
typedef void _GameClientCommandsUninstall();
typedef void ConsolePrintF(const char* text, ...);
typedef int FrameScript_Reload();
typedef void ClientServices_SetMessageHandler(u16 opcode, void* handler, DWORD param);
typedef void _ConsoleScreenInitialize();

namespace WowFunc
{
    ConsoleCommandRegister* RegisterConsoleCommand = (ConsoleCommandRegister*)RegisterConsoleCommandAddress;
    ConsoleCommandUnregister* UnregisterConsoleCommand = (ConsoleCommandUnregister*)UnregisterConsoleCommandAddress;
    _GameClientCommandsInstall* GameClientCommandsInstall = (_GameClientCommandsInstall*)GameClientCommandsInstallAddress;
    _GameClientCommandsUninstall* GameClientCommandsUninstall = (_GameClientCommandsUninstall*)GameClientCommandsUninstallAddress;
    ConsolePrintF* ConsolePrint = (ConsolePrintF*)ConsolePrintAddress;
    FrameScript_Reload* ReloadUI = (FrameScript_Reload*)ReloadUIAddress;
    ClientServices_SetMessageHandler* SetMessageHandler = (ClientServices_SetMessageHandler*)ClientServicesSetMessageHandlerAddress;
    _ConsoleScreenInitialize* ConsoleScreenInitialize = (_ConsoleScreenInitialize*)ConsoleScreenInitializeAddress;
}
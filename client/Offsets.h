#pragma once
#include "NovusTypes.h"

namespace Offsets
{
    const u32 RegisterConsoleCommandAddress = 0x769100;
    const u32 UnregisterConsoleCommandAddress = 0x7689E0;
    const u32 GameClientCommandsInstallAddress = 0x407870;
    const u32 GameClientCommandsUninstallAddress = 0x406EF0;
    const u32 ConsolePrintAddress = 0x7653B0;
    const u32 ReloadUIAddress = 0x401B00;
    const u32 CDataStoreGenPacketAddress = 0x401050;
    const u32 CDataStorePutI8Address = 0x47AFE0;
    const u32 CDataStorePutI16Address = 0x47B040;
    const u32 CDataStorePutI32Address = 0x47B0A0;
    const u32 CDataStorePutI64Address = 0x47B100;
    const u32 CDataStorePutF32Address = 0x47B160;
    const u32 CDataStorePutStringAddress = 0x47B300;
    const u32 CDataStorePutBytesAddress = 0x47B1C0;
    const u32 CDataStoreGetI8Address = 0x47B340;
    const u32 CDataStoreGetI16Address = 0x47B380;
    const u32 CDataStoreGetI32Address = 0x47B3C0;
    const u32 CDataStoreGetI64Address = 0x47B400;
    const u32 CDataStoreGetF32Address = 0x47B440;
    const u32 CDataStoreGetStringAddress = 0x47B480;
    const u32 CDataStoreGetBytesAddress = 0x47B560;
    const u32 CDataStoreFinalizeAddress = 0x401130;
    const u32 CDataStoreDestroyAddress = 0x403880;
    const u32 ClientServices_SendPacketAddress = 0x6B0B50;
    const u32 ClientServicesSetMessageHandlerAddress = 0x6B0B80;
    const u32 ConsoleScreenInitializeAddress = 0x766140;
    const u32 SendBugOpcodeAddress = 0x6B22A0;
}
#pragma once
#include "NovusTypes.h"

namespace Offsets
{
    // Function Offsets
    const u32 RegisterConsoleCommand = 0x769100;
    const u32 UnregisterConsoleCommand = 0x7689E0;
    const u32 GameClientCommandsInstall = 0x407870;
    const u32 GameClientCommandsUninstall = 0x406EF0;
    const u32 ConsolePrint = 0x7653B0;
    const u32 CDataStoreGenPacket = 0x401050;
    const u32 CDataStorePutI8 = 0x47AFE0;
    const u32 CDataStorePutI16 = 0x47B040;
    const u32 CDataStorePutI32 = 0x47B0A0;
    const u32 CDataStorePutI64 = 0x47B100;
    const u32 CDataStorePutF32 = 0x47B160;
    const u32 CDataStorePutString = 0x47B300;
    const u32 CDataStorePutBytes = 0x47B1C0;
    const u32 CDataStoreGetI8 = 0x47B340;
    const u32 CDataStoreGetI16 = 0x47B380;
    const u32 CDataStoreGetI32 = 0x47B3C0;
    const u32 CDataStoreGetI64 = 0x47B400;
    const u32 CDataStoreGetF32 = 0x47B440;
    const u32 CDataStoreGetString = 0x47B480;
    const u32 CDataStoreGetBytes = 0x47B560;
    const u32 CDataStoreFinalize = 0x401130;
    const u32 CDataStoreDestroy = 0x403880;
    const u32 ClientServicesSendPacket = 0x6B0B50;
    const u32 ClientServicesSetMessageHandler = 0x6B0B80;
    const u32 ConsoleScreenInitialize = 0x766140;
    const u32 SendBugOpcode = 0x6B22A0;
    const u32 SendChatMessage = 0x577D00;
    const u32 FrameScriptExecute = 0x819210;
    const u32 FrameScriptRegisterFunction = 0x817F90;
    const u32 FrameScriptUnregisterFunction = 0x817FD0;
    const u32 FrameScriptPushNumber = 0x84E2A0;
    const u32 FrameScriptPushString = 0x84E350;
    const u32 FrameScriptGetNumber = 0x84E030;
    const u32 FrameScriptGetString = 0x84E0E0;
    const u32 FrameScriptGetBool = 0x84E0B0;
    const u32 GetGuidByToken = 0x60C1C0;
    const u32 SetFocusByToken = 0x522480;
    const u32 LoadScriptFunctions = 0x5120E0;
    const u32 UnloadScriptFunctions = 0x512280;
    const u32 ShaUpdate2 = 0x6CA180;

    // Variable Offsets
    const u32 TextSectionMinimumAddress = 0xD415B8;
    const u32 TextSectionMaximumAddress = 0xD415BC;
    const u32 IsConsoleActive = 0xCABCC4;
    const u32 ConsoleKey = 0xADBAC4;
    const u32 RenderFlags = 0xCD774C;
    const u32 Gamestate = 0xB6A9E0;
}
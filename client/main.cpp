#include "NovusTypes.h"
#include "Offsets.h"
#include "Utils/ConfigUtils.h"
#include "Handlers/FunctionHandlers.h"

#include <Windows.h>
#include <io.h>
#include <thread>
#include <fcntl.h>
#include <cassert>
#include <Psapi.h>

HMODULE dllModule;
HWND processWindow;
WNDPROC processWndProc;

DWORD TextSectionMinimumValue = 0;
DWORD TextSectionMaximumValue = 0;
DWORD IsConsoleActiveValue = 0;

void Unload(bool cleanup = true)
{
    if (cleanup)
    {
        /* Uninstall all hooks and commands */
        FunctionHandlers::GMClientHooksUninstall();
        CommandHandlers::Uninstall();

        /* Restore original FrameScript__InvalidPtrCheck */
        *reinterpret_cast<DWORD*>(Offsets::TextSectionMinimumAddress) = TextSectionMinimumValue;
        *reinterpret_cast<DWORD*>(Offsets::TextSectionMinimumAddress) = TextSectionMaximumValue;

        /* Restore original active console state */
        *reinterpret_cast<DWORD*>(Offsets::IsConsoleActive) = 1;
    }

    /* 
        Currently we are unable to use FreeLibrary as it appears it has changed in >= c++ 11
        The Wow.exe for the patch 3.3.5a (12340) is using an older c++ versus, and calling FreeLibrary(dllModule)
        will cause the exe to hang for a second and then close itself.

        We either need to find a way to unload the DLL through other means, or simply live with the fact that
        the dll is loaded into the current session and never fully unloaded despite calling unload.

        The GM Client itself is not malicious and should not trigger any anti-cheat regardless of it being
        active or inactive, so this shouldn't be a problem, however it is a bit annoying.
    */
    FreeConsole();
}

void Initialize()
{
    AllocConsole();
    SetConsoleTitleA("GM Client Console");
    typedef struct { char* _ptr; int _cnt; char* _base; int _flag; int _file; int _charbuf; int _bufsiz; char* _tmpfname; } FILE_COMPLETE;
    *(FILE_COMPLETE*)stdout = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "w");
    *(FILE_COMPLETE*)stderr = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT), "w");
    *(FILE_COMPLETE*)stdin = *(FILE_COMPLETE*)_fdopen(_open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r");
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    printf("Console Allocated\n\n");

    if (!ConfigHandler::Load("GMClient.json"))
    {
        Unload(false);
        return;
    }

    printf("Patching FrameScript_InvalidPtrCheck\n");
    /* FrameScript__InvalidPtrCheck patched */
    TextSectionMinimumValue = *reinterpret_cast<DWORD*>(Offsets::TextSectionMinimumAddress);
    TextSectionMaximumValue = *reinterpret_cast<DWORD*>(Offsets::TextSectionMaximumAddress);
    *reinterpret_cast<DWORD*>(Offsets::TextSectionMinimumAddress) = 1;
    *reinterpret_cast<DWORD*>(Offsets::TextSectionMaximumAddress) = 0x7FFFFFFF;

    /* Enable console and set console key */
    IsConsoleActiveValue = *reinterpret_cast<DWORD*>(Offsets::IsConsoleActive);
    *reinterpret_cast<DWORD*>(Offsets::IsConsoleActive) = 1;

    u32 consoleKey = ConfigHandler::ConfigFile["key"].get<u32>();
    WowFunc::SetConsoleKey(consoleKey);
    WowFunc::ConsoleScreenInitialize();
    
    printf("Registering Console Commands\n");
    FunctionHandlers::Setup();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_TIMER:
        {
            if (wParam == 0x100)
            {
                Initialize();
            }
            break;
        }
    }

    return CallWindowProc(processWndProc, hwnd, msg, wParam, lParam);
}

DWORD WINAPI CheckAttach(LPVOID lpParameter)
{
    processWindow = FindWindowA(NULL, "World of Warcraft");
    while (processWindow == NULL)
    {
        processWindow = FindWindowA(NULL, "World of Warcraft");
    }

    processWndProc = (WNDPROC)SetWindowLongPtrA(processWindow, (ULONG)GWLP_WNDPROC, (ULONG_PTR)& WndProc);
    assert(processWndProc != NULL);

    SendMessage(processWindow, WM_TIMER, 0x100, NULL);
    return 0;
}

void Attach()
{
    DWORD threadId = 0;
    CreateThread(0, 0, CheckAttach, 0, 0, &threadId);
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        dllModule = hModule;
        Attach();
        break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#include "NovusTypes.h"
#include "Hook/FunctionHandlers.h"
#include <thread>

#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <cstdio>
#include <functional>
#include <cassert>

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

    printf("Patching FrameScript_InvalidPtrCheck\n");
    /* FrameScript__InvalidPtrCheck patched */
    *reinterpret_cast<DWORD*>(0xD415B8) = 1;
    *reinterpret_cast<DWORD*>(0xD415BC) = 0x7FFFFFFF;

    /* Enable console */
    *reinterpret_cast<DWORD*>(0x00CABCC4) = 1;
    WowFunc::ConsoleScreenInitialize();

    printf("Registering Console Commands\n");
    FunctionHandlers::Initialize();
}

HWND gameWindow;
WNDPROC originalWndProc;
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

    return CallWindowProc(originalWndProc, hwnd, msg, wParam, lParam);
}

DWORD WINAPI CheckAttach(LPVOID lpParameter)
{
    HWND gameWindow = FindWindowA(NULL, "World of Warcraft");
    while (gameWindow == NULL)
    {
        gameWindow = FindWindowA(NULL, "World of Warcraft");
    }

    originalWndProc = (WNDPROC)SetWindowLongPtrA(gameWindow, (ULONG)GWLP_WNDPROC, (ULONG_PTR)& WndProc);
    assert(originalWndProc != NULL);

    SendMessage(gameWindow, WM_TIMER, 0x100, NULL);

    return 0;
}

void Attach()
{
    DWORD threadId = 0;
    CreateThread(0, 0, CheckAttach, 0, 0, &threadId);
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        Attach();
        break;
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
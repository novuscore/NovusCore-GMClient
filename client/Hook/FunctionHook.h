#pragma once
#include "../NovusTypes.h"
#include <Windows.h>

const u32 HOOK_SIZE_X86 = 7;

template<class T1>
class FunctionHook
{
public:
    FunctionHook(T1 originalFunction, T1 hookedFunction)
    {
        OriginalFunction = originalFunction;
        HookedFunction = hookedFunction;
    }

    void Hook()
    {
        if (hooked)
            return;

        DWORD oldProtection = 0;
        VirtualProtect(OriginalFunction, HOOK_SIZE_X86, 0x40, &oldProtection);

        u8* bytePtr = reinterpret_cast<u8*>(OriginalFunction);
        for (i32 i = 0; i < HOOK_SIZE_X86; i++)
        {
            _originalBytes[i] = bytePtr[i];
        }

        // mov eax, address
        // jmp eax
        *bytePtr = 0xB8;
        *(intptr_t*)(bytePtr + 1) = (int)HookedFunction;
        *(bytePtr + 5) = 0xFF;
        *(bytePtr + 6) = 0xE0;

        VirtualProtect(OriginalFunction, HOOK_SIZE_X86, oldProtection, &oldProtection);
        hooked = true;
    }

    void Unhook()
    {
        if (!hooked)
            return;

        DWORD oldProtection = 0;
        VirtualProtect(OriginalFunction, HOOK_SIZE_X86, 0x40, &oldProtection);

        u8* bytePtr = reinterpret_cast<u8*>(OriginalFunction);
        for (i32 i = 0; i < HOOK_SIZE_X86; i++)
        {
            bytePtr[i] = _originalBytes[i];
        }

        VirtualProtect(OriginalFunction, HOOK_SIZE_X86, oldProtection, &oldProtection);
        hooked = false;
    }

    T1 OriginalFunction = nullptr;
    T1 HookedFunction = nullptr;
private:
    bool hooked = false;
    u8 _originalBytes[HOOK_SIZE_X86] = { 0 };
};
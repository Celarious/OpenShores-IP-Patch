#include "pch.h"
#include <windows.h>
#include <mutex>
#include <fstream>
#include "ClientInterface.h"
#include "ClientStateProcessing.h"

static int g_state = 0; // Global state variable
static std::mutex g_mutex; // Mutex for safely modifying the variable
HMODULE hGame = GetModuleHandleW(nullptr);

ReadEntryFn ReadEntry = reinterpret_cast<ReadEntryFn>( // Calls SoH's own AuSettings::ReadEntry()
    GetProcAddress(
        GetModuleHandleW(L"auglobal13.dll"),
        "?readEntry@AuSettings@@QEBA?AVQString@@AEBV2@0@Z"
    )
);

WriteEntryFn WriteEntry = reinterpret_cast<WriteEntryFn>(
    GetProcAddress(
        GetModuleHandleW(L"auglobal13.dll"),
        "?writeEntry@AuSettings@@QEAAXAEBVQString@@0@Z"
    )
);

extern "C" __declspec(dllexport)
void SetState(int state, void* context = nullptr) // 2nd parameter is optional, used whenever a state needs an extra object
{
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_state = state;
    }
    ProcessState(state, context); // This might be temporary (there is nothing more permanent than a temporary software solution), used to migrate the core asm functionality to C++
}

extern "C" __declspec(dllexport)
int GetState() // Could be used in the future by other C++ or even Lua modules to fetch the current state
{
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_state;
}

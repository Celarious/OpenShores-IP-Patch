#include "pch.h"
#include <windows.h>
#include <string>
#include <mutex>

static std::wstring g_serverAddress;
static std::string  g_serverAddressAscii;
static std::mutex   g_mutex;

extern "C" __declspec(dllexport)
void SetServerAddress(const wchar_t* address)
{
    if (!address)
        return;

    std::lock_guard<std::mutex> lock(g_mutex);

    g_serverAddress = address;
    g_serverAddressAscii.clear();

    while (*address)
    {
        g_serverAddressAscii.push_back(static_cast<char>(*address));
        ++address;
    }
}

extern "C" __declspec(dllexport)
const char* GetServerAddressAscii()
{
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_serverAddressAscii.c_str();
}

extern "C" __declspec(dllexport)
int GetServerAddressAsciiLength()
{
    std::lock_guard<std::mutex> lock(g_mutex);
    return static_cast<int>(g_serverAddressAscii.length());
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD reason,
    LPVOID lpReserved
)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        break;

    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}
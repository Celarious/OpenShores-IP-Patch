#include "pch.h"
#include <windows.h>
#include <mutex>
#include <fstream>
#include "ClientInterface.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>

static int g_state = 0; // Global state variable
static std::mutex g_mutex; // Mutex for safely modifying the variable
HMODULE hGame = GetModuleHandleW(nullptr);

using ReadEntryFn = void(__cdecl*)(
    void* settings,
    QString& result,
    const QString& key,
    QString* resultStorage
);

auto ReadEntry = reinterpret_cast<ReadEntryFn>( // Calls SoH's own AuSettings::ReadEntry()
    GetProcAddress(
        GetModuleHandleW(L"auglobal13.dll"),
        "?readEntry@AuSettings@@QEBA?AVQString@@AEBV2@0@Z"
    )
);

static void tempLog(int state) {
    std::ofstream("ClientInterface.log", std::ios::app) << "SetState(" << state << ") received!\n";
}

static void ProcessState(int state, QVBoxLayout* layout)
{
    switch (state)
    {
    case 0: // Default, nothing should happen here
        break;

    case 1: // Early startup, right after entry point
        tempLog(state);
        break;

    case 2: // Qt+Au initialization after CRT setup
        tempLog(state);
        break;

    case 3: // Game launch argument processing, right after QCoreApplication::arguments()
        tempLog(state);
        break;

    case 4: // Right after AuGlobal is initialized
        tempLog(state);
        break;

    case 5: // Login UI
        tempLog(state);
        {
            auto pAuGlobal = reinterpret_cast<uintptr_t*>(
                reinterpret_cast<uintptr_t>(hGame) + 0x8243F0
                );
            auto gpAuGlobal = *pAuGlobal;
            auto auGlobal = *reinterpret_cast<uintptr_t*>(gpAuGlobal);
            void* settings = reinterpret_cast<void*>(auGlobal + 0x238);
            QString key("/Account/Host"); // Sets the key to check
            QString host; // This is used as the return variable
            ReadEntry(settings, host, key, &host); // Actually reads the key's value
            auto* ipEdit = new QLineEdit(host); // Creates a QLineEdit with the host prefilled if it exists
            ipEdit->setToolTip(QStringLiteral("<html><b>IP address</b><br>Enter OpenShores IP</html>"));
            ipEdit->setPlaceholderText(QStringLiteral("Enter IP address"));
            layout->addWidget(ipEdit); // Adds the widget to the UI
        }
        break;

    case 6:
        tempLog(state);
        break;

    case 7:
        tempLog(state);
        break;

    case 8:
        tempLog(state);
        break;

    case 9:
        tempLog(state);
        break;
    }
}

extern "C" __declspec(dllexport)
void SetState(int state, QVBoxLayout* layout = nullptr) // 2nd parameter is optional, currently only used for case 5 to pass the login layout from RDI to the interface
{
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_state = state;
    }
    ProcessState(state, layout);
}

extern "C" __declspec(dllexport)
int GetState()
{
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_state;
}

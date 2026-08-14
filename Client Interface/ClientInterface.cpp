#include "pch.h"
#include <windows.h>
#include <mutex>
#include <fstream>
#include "ClientInterface.h"
#include <QtWidgets/QVBoxLayout>

static int g_state = 0;
static std::mutex g_mutex;

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

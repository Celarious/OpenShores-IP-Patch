#include "pch.h"
#include <windows.h>
#include <mutex>
#include <fstream>
#include "ClientInterface.h"

static int g_state = 0;
static std::mutex g_mutex;

static void tempLog(int state) {
    std::ofstream("ClientInterface.log", std::ios::app) << "SetState(" << state << ") received!\n";
}

static void ProcessState(int state)
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

    case 4:
        tempLog(state);
        break;

    case 5:
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
void SetState(int state)
{
    {
        std::lock_guard<std::mutex> lock(g_mutex);
        g_state = state;
    }
    ProcessState(state);
}

extern "C" __declspec(dllexport)
int GetState()
{
    std::lock_guard<std::mutex> lock(g_mutex);
    return g_state;
}

#include "pch.h"
#include "ClientInterface.h"
#include "ClientStateProcessing.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <fstream>

static QLineEdit* g_ipEdit = nullptr; // Our inserted IP input field
static bool g_state7Fired = false;
static uintptr_t g_auGlobal = 0; // Storage for AuGlobal to avoid repeat lookups
static void* g_settings = nullptr; // AuGlobal + 0x238

static void tempLog(int state) { // Temporary log function for checking if the states are called
    std::ofstream("ClientInterface.log", std::ios::app) << "SetState(" << state << ") received!\n";
}

void ProcessState(int state, void* context)
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

    case 5: // Login UI setup
        tempLog(state);
        {
            QVBoxLayout* layout = static_cast<QVBoxLayout*>(context);
            auto pAuGlobal = reinterpret_cast<uintptr_t*>(
                reinterpret_cast<uintptr_t>(hGame) + 0x8243F0 // RVA of AuGlobal
                );
            auto gpAuGlobal = *pAuGlobal;
            g_auGlobal = *reinterpret_cast<uintptr_t*>(gpAuGlobal);
            g_settings = reinterpret_cast<void*>(g_auGlobal + 0x238); // Stores the existing AuSettings variable, since it needs to be provided when calling any AuSettings function
            QString key("/Account/Host"); // Sets the key to check
            QString host; // This is used as the return variable
            ReadEntry(g_settings, host, key, &host); // Actually reads the key's value
            g_ipEdit = new QLineEdit(host); // Prefills the input field if the Host key exists
            g_ipEdit->setToolTip(QStringLiteral("<html><b>IP address</b><br>Enter OpenShores IP</html>"));
            g_ipEdit->setPlaceholderText(QStringLiteral("Enter IP address"));
            layout->addWidget(g_ipEdit); // Adds the widget to the UI
        }
        break;

    case 6: // Background image loading and rendering
        tempLog(state);
        {
            QImage* image = static_cast<QImage*>(context); // Converts the passed context to a qimage
            image->load(QString::fromLatin1("assets/Background.png"));
        }
        break;

    case 7: // Login UI ready, painting started
        if (!g_state7Fired) // Prevents state 7 from repeatedly firing
        {
            g_state7Fired = true;
            tempLog(state);
        }
        break;

    case 8: // Immediate post-login click
        tempLog(state);
        {
            QString key("/Account/Host");
            QString host = g_ipEdit->text();
            WriteEntry(g_settings, key, host); // Writes the user's entered host to the registry for prefilling
        }
        break;

    case 9: // Login comms begin
        tempLog(state);
        {
            QString host = g_ipEdit->text();
            *reinterpret_cast<QString*>(
                (g_auGlobal) + 0x150 // Login host
                ) = host;

            *reinterpret_cast<QString*>(
                (g_auGlobal) + 0x160 // Mail host
                ) = host;

            *reinterpret_cast<QString*>(
                (g_auGlobal) + 0x218 // Scene host
                ) = host;
        }
        break;
    }
}

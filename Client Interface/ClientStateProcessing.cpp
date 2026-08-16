#include "pch.h"
#include "ClientInterface.h"
#include "ClientStateProcessing.h"
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <fstream>

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

    case 5: // Login UI
        tempLog(state);
        {
            QVBoxLayout* layout = static_cast<QVBoxLayout*>(context);
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
        {
            QImage* image = static_cast<QImage*>(context);
            image->load(QString::fromLatin1("assets/Background.png"));
        }
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

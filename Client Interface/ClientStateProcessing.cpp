#include "pch.h"
#include <fstream>

#include "ClientInterface.h"
#include "ClientStateProcessing.h"
#include "AuFunctions.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtWidgets/QPushButton>
#include <QtCore/QMetaObject>

static QLineEdit* g_ipEdit = nullptr; // Our inserted IP input field
static bool g_state8Fired = false;
static uintptr_t g_auGlobal = 0; // Storage for AuGlobal to avoid repeat lookups
static void* g_settings = nullptr; // AuGlobal + 0x238

static void tempLog(int state) { // Temporary log function for checking if the states are called
    static bool initialized = false;
    if (!initialized) {
        std::ofstream("ClientInterface.log", std::ios::trunc).close(); // Wipes itself on every program start so it doesn't fill forever
        std::ofstream("ClientInterface.log", std::ios::app) << "==== Logging started! ====\n";
        initialized = true;
    }
    std::ofstream("ClientInterface.log", std::ios::app) << "SetState(" << state << ") received!\n";
}

bool CheckLaunchArguments() // Function that handles the OS launcher's custom args
{
    const QStringList args = QCoreApplication::arguments();
    bool noLogin = args.contains(QStringLiteral("-nologin")); // Checks if -nologin was passed
    std::ofstream log("ClientInterface.log", std::ios::app);
    log << "-nologin = "
        << (noLogin ? "true" : "false") << '\n';
    return noLogin;
}

void ProcessState(int state, void* context, void* aux)
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

    case 5: // Scrolling text state, called early in UI setup
        tempLog(state);
        {
            if (!context)
                return;

            QList<QString>* textList =
                reinterpret_cast<QList<QString>*>(
                    static_cast<char*>(context) + 0x30 // RSI register passed through RDX (win x64 convention)
                    );

            textList->clear(); // Clears the original scrolling text list

            textList->append(QString::fromLatin1("*OpenShores")); // The * at the start of the string is a marker that the game checks for, and if present, removes it and centers + boldens the line
            textList->append(QString::fromLatin1("Welcome to OpenShores"));
            textList->append(QString::fromLatin1("V0.0.7 (2026)"));
        }
        break;

    case 6: // Login UI setup
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
            Au::ReadEntry(g_settings, host, key, &host); // Actually reads the key's value
            g_ipEdit = new QLineEdit(host); // Prefills the input field if the Host key exists
            g_ipEdit->setToolTip(QStringLiteral("<html><b>IP address</b><br>Enter OpenShores IP</html>"));
            g_ipEdit->setPlaceholderText(QStringLiteral("Enter IP address"));
            layout->addWidget(g_ipEdit); // Adds the widget to the UI
            if (CheckLaunchArguments())
            {
                QPushButton* loginButton =
                    *reinterpret_cast<QPushButton**>(
                        static_cast<char*>(aux) + 0x50
                        );
                if (loginButton)
                {
                    QMetaObject::invokeMethod( // Automatically logs in if the launcher passes -nologin by simulating a click
                        loginButton,
                        "click",
                        Qt::QueuedConnection
                    );
                }
            }
        }
        break;

    case 7: // Background image loading and rendering
        tempLog(state);
        {
            QImage* image = static_cast<QImage*>(context); // Converts the passed context to a qimage
            image->load(QString::fromLatin1("assets/Background.png"));
        }
        break;

    case 8: // Login UI ready, painting started
        if (!g_state8Fired) // Prevents state from repeatedly firing
        {
            g_state8Fired = true;
            tempLog(state);
        }
        break;

    case 9: // Immediate post-login click
        tempLog(state);
        {
            QString key("/Account/Host");
            QString host = g_ipEdit->text();
            Au::WriteEntry(g_settings, key, host); // Writes the user's entered host to the registry for prefilling
        }
        break;

    case 10: // Login comms begin
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

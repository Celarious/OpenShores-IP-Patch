#include "pch.h"
#include "ClientFeatures.h"
#include <QList>
#include <QString>

void ConfigureScrollingText(void* scrollingText)
{
    if (!scrollingText)
        return;

    QList<QString>* textList =
        reinterpret_cast<QList<QString>*>(
            static_cast<char*>(scrollingText) + 0x30 // RSI register passed through RCX (win x64 convention)
            );

    textList->clear(); // Clears the original scrolling text list

    textList->append(QString::fromLatin1("*OpenShores")); // The * at the start of the string is a marker that the game checks for, and if present, removes it and centers + boldens the line
    textList->append(QString::fromLatin1("Welcome to OpenShores"));
    textList->append(QString::fromLatin1("V0.0.5 (2026)"));
}

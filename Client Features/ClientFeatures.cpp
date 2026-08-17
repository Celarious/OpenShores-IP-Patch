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
            static_cast<char*>(scrollingText) + 0x30
            );

    textList->clear();

    textList->append(QString::fromLatin1("*OpenShores"));
    textList->append(QString::fromLatin1("Welcome to OpenShores"));
    textList->append(QString::fromLatin1("V0.0.5 (2026)"));
}
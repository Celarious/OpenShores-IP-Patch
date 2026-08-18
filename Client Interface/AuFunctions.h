#pragma once

#include <QString>

using ReadEntryFn = void(__cdecl*)(
    void* settings,
    QString& result,
    const QString& key,
    QString* resultStorage
    );

using WriteEntryFn = void(__cdecl*)(
    void* settings,
    const QString& key,
    const QString& value
    );

namespace Au {
    extern ReadEntryFn ReadEntry;
    extern WriteEntryFn WriteEntry;

    void Initialize();
}
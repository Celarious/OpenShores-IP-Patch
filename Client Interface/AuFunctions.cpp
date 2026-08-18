#include "pch.h"
#include "ClientInterface.h"
#include "AuFunctions.h"

// This file is used to centralize the game's existing exported Au functions

namespace Au {
    ReadEntryFn ReadEntry = nullptr;
    WriteEntryFn WriteEntry = nullptr;

    void Initialize()
    {
        HMODULE hGameModule = GetModuleHandleW(nullptr);

        ReadEntry =
            *reinterpret_cast<ReadEntryFn*>(
                reinterpret_cast<uintptr_t>(hGameModule) + 0x824320
            );

        WriteEntry =
            *reinterpret_cast<WriteEntryFn*>(
                reinterpret_cast<uintptr_t>(hGameModule) + 0x824318
             );
    }
}
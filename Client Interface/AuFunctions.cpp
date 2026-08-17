#include "pch.h"
#include "AuFunctions.h"

// This file is used to centralize the game's existing exported Au functions

namespace Au {
    ReadEntryFn ReadEntry = reinterpret_cast<ReadEntryFn>(
        GetProcAddress(
            GetModuleHandleW(L"auglobal13.dll"),
            "?readEntry@AuSettings@@QEBA?AVQString@@AEBV2@0@Z"
        )
    );

    WriteEntryFn WriteEntry = reinterpret_cast<WriteEntryFn>(
        GetProcAddress(
            GetModuleHandleW(L"auglobal13.dll"),
            "?writeEntry@AuSettings@@QEAAXAEBVQString@@0@Z"
        )
    );
}

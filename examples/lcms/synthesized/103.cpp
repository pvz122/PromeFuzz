// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsIT8GetPatchName at cmscgats.c:2950:23 in lcms2.h
// cmsIT8SetComment at cmscgats.c:1517:19 in lcms2.h
// cmsIT8SetDataRowCol at cmscgats.c:2833:19 in lcms2.h
// cmsIT8SetPropertyUncooked at cmscgats.c:1558:19 in lcms2.h
// cmsstrcasecmp at cmserr.c:39:15 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <lcms2.h>
#include <stdint.h>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    cmsHANDLE hIT8 = cmsIT8Alloc(nullptr);
    if (!hIT8) return 0;

    // Ensure the input data is null-terminated
    char* safeData = new char[Size + 1];
    memcpy(safeData, Data, Size);
    safeData[Size] = '\0';

    // Fuzz cmsIT8GetPatchName
    int nPatch = Data[0] % 100;
    char buffer[256];
    cmsIT8GetPatchName(hIT8, nPatch, buffer);

    // Fuzz cmsIT8SetComment
    cmsIT8SetComment(hIT8, safeData);

    // Fuzz cmsIT8SetDataRowCol
    int row = Data[0] % 10;
    int col = Data[1] % 10;
    cmsIT8SetDataRowCol(hIT8, row, col, safeData);

    // Fuzz cmsIT8SetPropertyUncooked
    const char* key = "key";
    cmsIT8SetPropertyUncooked(hIT8, key, safeData);

    // Fuzz cmsstrcasecmp
    const char* s1 = "string1";
    cmsstrcasecmp(s1, safeData);

    delete[] safeData;
    cmsIT8Free(hIT8);
    return 0;
}
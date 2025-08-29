// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsIT8SaveToFile at cmscgats.c:2002:19 in lcms2.h
// cmsIT8SetDataFormat at cmscgats.c:1689:19 in lcms2.h
// cmsIT8SetPropertyHex at cmscgats.c:1548:19 in lcms2.h
// cmsIT8SetPropertyStr at cmscgats.c:1528:19 in lcms2.h
// cmsIT8SetPropertyMulti at cmscgats.c:1565:19 in lcms2.h
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
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>

extern "C" int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number)) return 0;

    cmsHANDLE hIT8 = cmsIT8Alloc(nullptr);
    if (!hIT8) return 0;

    // Use a dummy file for saving IT8 data
    const char* filename = "./dummy_file";

    // Fuzz cmsIT8SaveToFile
    cmsIT8SaveToFile(hIT8, filename);

    // Fuzz cmsIT8SetDataFormat
    if (Size > 0) {
        char* nullTerminatedData = new char[Size + 1];
        memcpy(nullTerminatedData, Data, Size);
        nullTerminatedData[Size] = '\0';
        cmsIT8SetDataFormat(hIT8, 0, nullTerminatedData);
        delete[] nullTerminatedData;
    }

    // Fuzz cmsIT8SetPropertyHex
    cmsUInt32Number hexValue;
    memcpy(&hexValue, Data, sizeof(cmsUInt32Number));
    cmsIT8SetPropertyHex(hIT8, "PropertyHex", hexValue);

    // Fuzz cmsIT8SetPropertyStr
    if (Size > 0) {
        char* nullTerminatedData = new char[Size + 1];
        memcpy(nullTerminatedData, Data, Size);
        nullTerminatedData[Size] = '\0';
        cmsIT8SetPropertyStr(hIT8, "PropertyStr", nullTerminatedData);
        delete[] nullTerminatedData;
    }

    // Fuzz cmsIT8SetPropertyMulti
    if (Size > 0) {
        char* nullTerminatedData = new char[Size + 1];
        memcpy(nullTerminatedData, Data, Size);
        nullTerminatedData[Size] = '\0';
        cmsIT8SetPropertyMulti(hIT8, "Key", "SubKey", nullTerminatedData);
        delete[] nullTerminatedData;
    }

    // Cleanup
    cmsIT8Free(hIT8);

    return 0;
}
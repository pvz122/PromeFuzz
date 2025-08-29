// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsIT8TableCount at cmscgats.c:2976:27 in lcms2.h
// cmsIT8EnumProperties at cmscgats.c:2660:27 in lcms2.h
// cmsIT8SetTable at cmscgats.c:1422:26 in lcms2.h
// cmsIT8SaveToMem at cmscgats.c:2042:19 in lcms2.h
// cmsIT8SaveToMem at cmscgats.c:2042:19 in lcms2.h
// cmsIT8EnumPropertyMulti at cmscgats.c:2695:27 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHANDLE hIT8 = cmsIT8Alloc(nullptr);
    if (!hIT8) return 0;

    // Fuzz cmsIT8TableCount
    cmsIT8TableCount(hIT8);

    // Fuzz cmsIT8EnumProperties
    char **PropertyNames = nullptr;
    cmsIT8EnumProperties(hIT8, &PropertyNames);
    if (PropertyNames) {
        for (cmsUInt32Number i = 0; PropertyNames[i]; ++i) {
            free(PropertyNames[i]);
        }
        free(PropertyNames);
    }

    // Fuzz cmsIT8SetTable
    cmsUInt32Number nTable = Data[0] % 10; // Arbitrary limit to keep it small
    cmsIT8SetTable(hIT8, nTable);

    // Fuzz cmsIT8SaveToMem
    cmsUInt32Number BytesNeeded = 0;
    cmsIT8SaveToMem(hIT8, nullptr, &BytesNeeded);
    if (BytesNeeded > 0) {
        void *MemPtr = malloc(BytesNeeded);
        if (MemPtr) {
            cmsIT8SaveToMem(hIT8, MemPtr, &BytesNeeded);
            free(MemPtr);
        }
    }

    // Fuzz cmsIT8EnumPropertyMulti
    const char *cProp = "SampleProperty";
    const char **SubpropertyNames = nullptr;
    cmsIT8EnumPropertyMulti(hIT8, cProp, &SubpropertyNames);
    if (SubpropertyNames) {
        for (cmsUInt32Number i = 0; SubpropertyNames[i]; ++i) {
            free((void *)SubpropertyNames[i]);
        }
        free(SubpropertyNames);
    }

    cmsIT8Free(hIT8);
    return 0;
}
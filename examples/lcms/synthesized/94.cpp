// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsIT8Alloc at cmscgats.c:1449:22 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
// cmsIT8Free at cmscgats.c:1165:16 in lcms2.h
// cmsIT8GetPropertyDbl at cmscgats.c:1586:28 in lcms2.h
// cmsIT8SetDataDbl at cmscgats.c:2935:19 in lcms2.h
// cmsIT8GetPatchName at cmscgats.c:2950:23 in lcms2.h
// cmsIT8SetPropertyDbl at cmscgats.c:1538:19 in lcms2.h
// cmsIT8GetDataDbl at cmscgats.c:2878:28 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_94(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cmsHANDLE hIT8 = cmsIT8Alloc(nullptr);
    if (!hIT8) return 0;

    // Randomly split the input data for different purposes
    size_t propNameSize = Size / 5;
    size_t patchNameSize = Size / 5;
    size_t sampleNameSize = Size / 5;
    size_t valSize = Size / 5;
    size_t patchIndexSize = Size / 5;

    // Ensure we have enough data for the double value
    if (Size < propNameSize + patchNameSize + sampleNameSize + sizeof(cmsFloat64Number)) {
        cmsIT8Free(hIT8);
        return 0;
    }

    // Extract property name
    char* propName = (char*)malloc(propNameSize + 1);
    if (!propName) {
        cmsIT8Free(hIT8);
        return 0;
    }
    memcpy(propName, Data, propNameSize);
    propName[propNameSize] = '\0';

    // Extract patch name
    char* patchName = (char*)malloc(patchNameSize + 1);
    if (!patchName) {
        free(propName);
        cmsIT8Free(hIT8);
        return 0;
    }
    memcpy(patchName, Data + propNameSize, patchNameSize);
    patchName[patchNameSize] = '\0';

    // Extract sample name
    char* sampleName = (char*)malloc(sampleNameSize + 1);
    if (!sampleName) {
        free(patchName);
        free(propName);
        cmsIT8Free(hIT8);
        return 0;
    }
    memcpy(sampleName, Data + propNameSize + patchNameSize, sampleNameSize);
    sampleName[sampleNameSize] = '\0';

    // Extract value
    cmsFloat64Number val = 0.0;
    if (Size >= propNameSize + patchNameSize + sampleNameSize + sizeof(cmsFloat64Number)) {
        val = *reinterpret_cast<const cmsFloat64Number*>(Data + propNameSize + patchNameSize + sampleNameSize);
    }

    // Extract patch index
    int patchIndex = 0;
    if (Size >= propNameSize + patchNameSize + sampleNameSize + sizeof(cmsFloat64Number) + sizeof(int)) {
        patchIndex = *reinterpret_cast<const int*>(Data + propNameSize + patchNameSize + sampleNameSize + sizeof(cmsFloat64Number)) % 100;
    }

    // Call target functions
    cmsIT8GetPropertyDbl(hIT8, propName);
    cmsIT8SetDataDbl(hIT8, patchName, sampleName, val);
    cmsIT8GetPatchName(hIT8, patchIndex, nullptr);
    cmsIT8SetPropertyDbl(hIT8, propName, val);
    cmsIT8GetDataDbl(hIT8, patchName, sampleName);

    // Clean up
    free(sampleName);
    free(patchName);
    free(propName);
    cmsIT8Free(hIT8);

    return 0;
}
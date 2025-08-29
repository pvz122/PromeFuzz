// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsGetTagCount at cmsio0.c:581:26 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsGetTagSignature at cmsio0.c:590:27 in lcms2.h
// cmsReadRawTag at cmsio0.c:1907:27 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy ICC profile in memory
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return 0;

    // Get the number of tags in the profile
    cmsInt32Number tagCount = cmsGetTagCount(hProfile);
    if (tagCount < 0) {
        cmsCloseProfile(hProfile);
        return 0;
    }

    // Iterate through tags and read raw data
    for (cmsUInt32Number i = 0; i < static_cast<cmsUInt32Number>(tagCount); ++i) {
        cmsTagSignature sig = cmsGetTagSignature(hProfile, i);
        if (sig == 0) continue;

        // Read raw tag data
        cmsUInt32Number bufferSize = 1024;
        void* buffer = malloc(bufferSize);
        if (!buffer) continue;

        cmsUInt32Number readSize = cmsReadRawTag(hProfile, sig, buffer, bufferSize);
        free(buffer);
    }

    cmsCloseProfile(hProfile);
    return 0;
}
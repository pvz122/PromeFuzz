// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsIsMatrixShaper at cmsio1.c:806:20 in lcms2.h
// cmsMD5computeID at cmsmd5.c:257:19 in lcms2.h
// cmsGetTagCount at cmsio0.c:581:26 in lcms2.h
// cmsSaveProfileToStream at cmsio0.c:1520:19 in lcms2.h
// cmsGetHeaderCreationDateTime at cmsio0.c:1062:20 in lcms2.h
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
#include <cstdio>
#include <ctime>

extern "C" int LLVMFuzzerTestOneInput_108(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy ICC profile
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return 0;

    // Fuzz cmsIsMatrixShaper
    cmsIsMatrixShaper(hProfile);

    // Fuzz cmsMD5computeID
    cmsMD5computeID(hProfile);

    // Fuzz cmsGetTagCount
    cmsGetTagCount(hProfile);

    // Fuzz cmsSaveProfileToStream
    FILE* stream = fopen("./dummy_file", "wb");
    if (stream) {
        cmsSaveProfileToStream(hProfile, stream);
        // Do not close the stream here, as it is handled by cmsSaveProfileToStream
    }

    // Fuzz cmsGetHeaderCreationDateTime
    struct tm dest;
    cmsGetHeaderCreationDateTime(hProfile, &dest);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}
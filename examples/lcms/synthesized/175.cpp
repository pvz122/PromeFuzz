// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsIsMatrixShaper at cmsio1.c:806:20 in lcms2.h
// cmsMD5computeID at cmsmd5.c:257:19 in lcms2.h
// cmsGetTagCount at cmsio0.c:581:26 in lcms2.h
// cmsDetectDestinationBlackPoint at cmssamp.c:352:19 in lcms2.h
// cmsGetEncodedCMMversion at cmserr.c:30:15 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_175(const uint8_t *Data, size_t Size) {
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

    // Fuzz cmsDetectDestinationBlackPoint
    cmsCIEXYZ BlackPoint;
    cmsDetectDestinationBlackPoint(&BlackPoint, hProfile, 0, 0);

    // Fuzz cmsGetEncodedCMMversion
    cmsGetEncodedCMMversion();

    // Cleanup
    cmsCloseProfile(hProfile);

    return 0;
}
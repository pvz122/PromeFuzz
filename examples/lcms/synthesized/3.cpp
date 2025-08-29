// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsPipelineFree at cmslut.c:1426:16 in lcms2.h
// cmsDetectDestinationBlackPoint at cmssamp.c:352:19 in lcms2.h
// cmsDetectTAC at cmsgmt.c:462:28 in lcms2.h
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
#include <stdint.h>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIEXYZ)) return 0;

    cmsCIEXYZ BlackPoint;
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    cmsUInt32Number Intent = INTENT_PERCEPTUAL;
    cmsUInt32Number dwFlags = 0;

    // Call cmsPipelineFree multiple times
    for (int i = 0; i < 12; ++i) {
        cmsPipelineFree(nullptr);
    }

    // Call cmsDetectDestinationBlackPoint multiple times
    for (int i = 0; i < 4; ++i) {
        cmsDetectDestinationBlackPoint(&BlackPoint, hProfile, Intent, dwFlags);
    }

    // Call cmsDetectTAC
    cmsDetectTAC(hProfile);

    cmsCloseProfile(hProfile);

    return 0;
}
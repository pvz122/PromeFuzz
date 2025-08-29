// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsFormatterForPCSOfProfile at cmspack.c:4044:27 in lcms2.h
// cmsFormatterForColorspaceOfProfile at cmspack.c:4025:27 in lcms2.h
// cmsIsCLUT at cmsio1.c:830:20 in lcms2.h
// cmsDetectDestinationBlackPoint at cmssamp.c:352:19 in lcms2.h
// cmsIsIntentSupported at cmsio1.c:864:20 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt32Number) * 4) return 0;

    cmsUInt32Number nBytes = *reinterpret_cast<const cmsUInt32Number*>(Data);
    cmsBool lIsFloat = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number)) & 1;
    cmsUInt32Number Intent = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 2);
    cmsUInt32Number UsedDirection = *reinterpret_cast<const cmsUInt32Number*>(Data + sizeof(cmsUInt32Number) * 3);

    // Create a dummy profile
    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    if (!hProfile) return 0;

    // Fuzz cmsFormatterForPCSOfProfile
    cmsFormatterForPCSOfProfile(hProfile, nBytes, lIsFloat);

    // Fuzz cmsFormatterForColorspaceOfProfile
    cmsFormatterForColorspaceOfProfile(hProfile, nBytes, lIsFloat);

    // Fuzz cmsIsCLUT
    cmsIsCLUT(hProfile, Intent, UsedDirection);

    // Fuzz cmsDetectDestinationBlackPoint
    cmsCIEXYZ BlackPoint;
    cmsDetectDestinationBlackPoint(&BlackPoint, hProfile, Intent, 0);

    // Fuzz cmsIsIntentSupported
    cmsIsIntentSupported(hProfile, Intent, UsedDirection);

    // Clean up
    cmsCloseProfile(hProfile);

    return 0;
}
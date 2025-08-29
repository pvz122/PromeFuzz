// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsChannelsOfColorSpace at cmspcs.c:877:26 in lcms2.h
// _cmsICCcolorSpace at cmspcs.c:764:34 in lcms2.h
// cmsCreate_sRGBProfile at cmsvirt.c:669:23 in lcms2.h
// cmsGetColorSpace at cmsio0.c:1081:34 in lcms2.h
// _cmsLCMScolorSpace at cmspcs.c:810:15 in lcms2.h
// cmsGetPCS at cmsio0.c:1069:34 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsColorSpaceSignature)) return 0;

    cmsColorSpaceSignature colorSpace;
    memcpy(&colorSpace, Data, sizeof(cmsColorSpaceSignature));

    cmsChannelsOfColorSpace(colorSpace);

    int ourNotation = *reinterpret_cast<const int*>(Data);
    _cmsICCcolorSpace(ourNotation);

    cmsHPROFILE hProfile = cmsCreate_sRGBProfile();
    cmsGetColorSpace(hProfile);
    _cmsLCMScolorSpace(colorSpace);
    cmsGetPCS(hProfile);
    cmsCloseProfile(hProfile);

    return 0;
}
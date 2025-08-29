// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateInkLimitingDeviceLink at cmsvirt.c:466:23 in lcms2.h
// cmsGetProfileVersion at cmsio0.c:1147:28 in lcms2.h
// cmsDetectRGBProfileGamma at cmsgmt.c:605:28 in lcms2.h
// cmsGetColorSpace at cmsio0.c:1081:34 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_99(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number)) return 0;

    cmsFloat64Number limit = *reinterpret_cast<const cmsFloat64Number*>(Data);
    cmsColorSpaceSignature colorSpace = cmsSigRgbData;

    cmsHPROFILE hProfile = cmsCreateInkLimitingDeviceLink(colorSpace, limit);
    if (hProfile) {
        cmsFloat64Number version = cmsGetProfileVersion(hProfile);
        cmsFloat64Number gamma = cmsDetectRGBProfileGamma(hProfile, limit);
        cmsColorSpaceSignature profileColorSpace = cmsGetColorSpace(hProfile);
        cmsColorSpaceSignature pcs = cmsGetPCS(hProfile);
        cmsCloseProfile(hProfile);
    }

    return 0;
}
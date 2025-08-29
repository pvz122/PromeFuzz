// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsSetAdaptationStateTHR at cmsxform.c:57:28 in lcms2.h
// cmsDupContext at cmsplugin.c:893:22 in lcms2.h
// cmsGetContextUserData at cmsplugin.c:1021:17 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreate_sRGBProfileTHR at cmsvirt.c:642:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateInkLimitingDeviceLinkTHR at cmsvirt.c:393:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    double threshold = *reinterpret_cast<const double*>(Data);
    cmsSetAdaptationStateTHR(context, threshold);

    cmsContext dupContext = cmsDupContext(context, nullptr);
    if (dupContext) {
        cmsGetContextUserData(dupContext);
        cmsDeleteContext(dupContext);
    }

    cmsHPROFILE sRGBProfile = cmsCreate_sRGBProfileTHR(context);
    if (sRGBProfile) {
        cmsCloseProfile(sRGBProfile);
    }

    double limit = *reinterpret_cast<const double*>(Data);
    cmsHPROFILE inkLimitProfile = cmsCreateInkLimitingDeviceLinkTHR(context, cmsSigCmykData, limit);
    if (inkLimitProfile) {
        cmsCloseProfile(inkLimitProfile);
    }

    cmsDeleteContext(context);
    return 0;
}
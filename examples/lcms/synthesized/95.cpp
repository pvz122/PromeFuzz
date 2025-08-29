// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateLab2ProfileTHR at cmsvirt.c:473:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateLab2ProfileTHR at cmsvirt.c:473:23 in lcms2.h
// cmsCreateMultiprofileTransformTHR at cmsxform.c:1279:25 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateBCHSWabstractProfileTHR at cmsvirt.c:850:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateRGBProfileTHR at cmsvirt.c:101:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateBCHSWabstractProfile at cmsvirt.c:936:32 in lcms2.h
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
#include "lcms2.h"
#include <stdint.h>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *Data, size_t Size) {
    if (Size < 6) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);

    // Fuzz cmsCreateLab2ProfileTHR
    cmsCIExyY whitePoint;
    if (Size >= sizeof(cmsCIExyY)) {
        memcpy(&whitePoint, Data, sizeof(cmsCIExyY));
        cmsHPROFILE labProfile = cmsCreateLab2ProfileTHR(context, &whitePoint);
        if (labProfile) cmsCloseProfile(labProfile);
    }

    // Fuzz cmsCreateMultiprofileTransformTHR
    cmsHPROFILE profiles[1];
    profiles[0] = cmsCreateLab2ProfileTHR(context, nullptr);
    if (profiles[0]) {
        cmsHTRANSFORM transform = cmsCreateMultiprofileTransformTHR(context, profiles, 1, TYPE_Lab_8, TYPE_Lab_8, INTENT_PERCEPTUAL, 0);
        if (transform) cmsDeleteTransform(transform);
        cmsCloseProfile(profiles[0]);
    }

    // Fuzz cmsCreateBCHSWabstractProfileTHR
    cmsFloat64Number bright = static_cast<cmsFloat64Number>(Data[0]) / 255.0;
    cmsFloat64Number contrast = static_cast<cmsFloat64Number>(Data[1]) / 255.0;
    cmsFloat64Number hue = static_cast<cmsFloat64Number>(Data[2]) / 255.0;
    cmsFloat64Number saturation = static_cast<cmsFloat64Number>(Data[3]) / 255.0;
    cmsUInt32Number tempSrc = static_cast<cmsUInt32Number>(Data[4]);
    cmsUInt32Number tempDest = static_cast<cmsUInt32Number>(Data[5]);
    cmsHPROFILE bchswProfile = cmsCreateBCHSWabstractProfileTHR(context, 256, bright, contrast, hue, saturation, tempSrc, tempDest);
    if (bchswProfile) cmsCloseProfile(bchswProfile);

    // Fuzz cmsCreateRGBProfileTHR
    cmsCIExyY rgbWhitePoint;
    cmsCIExyYTRIPLE primaries;
    if (Size >= sizeof(cmsCIExyY) + sizeof(cmsCIExyYTRIPLE)) {
        memcpy(&rgbWhitePoint, Data, sizeof(cmsCIExyY));
        memcpy(&primaries, Data + sizeof(cmsCIExyY), sizeof(cmsCIExyYTRIPLE));
        cmsToneCurve* transferFunction[3] = { nullptr, nullptr, nullptr };
        cmsHPROFILE rgbProfile = cmsCreateRGBProfileTHR(context, &rgbWhitePoint, &primaries, transferFunction);
        if (rgbProfile) cmsCloseProfile(rgbProfile);
    }

    // Fuzz cmsCreateBCHSWabstractProfile
    cmsHPROFILE bchswProfile2 = cmsCreateBCHSWabstractProfile(256, bright, contrast, hue, saturation, tempSrc, tempDest);
    if (bchswProfile2) cmsCloseProfile(bchswProfile2);

    cmsDeleteContext(context);

    return 0;
}
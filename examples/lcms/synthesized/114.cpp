// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsBuildGamma at cmsgamma.c:909:25 in lcms2.h
// cmsCreateLab2Profile at cmsvirt.c:513:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateRGBProfileTHR at cmsvirt.c:101:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsCreateRGBProfile at cmsvirt.c:217:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateGrayProfile at cmsvirt.c:280:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateGrayProfileTHR at cmsvirt.c:227:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
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
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_114(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY) + sizeof(cmsCIExyYTRIPLE)) {
        return 0;
    }

    cmsCIExyY whitePoint;
    cmsCIExyYTRIPLE primaries;

    // Initialize whitePoint
    memcpy(&whitePoint, Data, sizeof(cmsCIExyY));
    Data += sizeof(cmsCIExyY);
    Size -= sizeof(cmsCIExyY);

    // Initialize primaries
    memcpy(&primaries, Data, sizeof(cmsCIExyYTRIPLE));
    Data += sizeof(cmsCIExyYTRIPLE);
    Size -= sizeof(cmsCIExyYTRIPLE);

    // Create a simple tone curve
    cmsToneCurve* transferFunction[3];
    for (int i = 0; i < 3; i++) {
        transferFunction[i] = cmsBuildGamma(nullptr, 2.2);
        if (!transferFunction[i]) {
            return 0;
        }
    }

    // Fuzz cmsCreateLab2Profile
    cmsHPROFILE labProfile = cmsCreateLab2Profile(&whitePoint);
    if (labProfile) {
        cmsCloseProfile(labProfile);
    }

    // Fuzz cmsCreateRGBProfileTHR
    cmsContext contextID = cmsCreateContext(nullptr, nullptr);
    cmsHPROFILE rgbProfileTHR = cmsCreateRGBProfileTHR(contextID, &whitePoint, &primaries, transferFunction);
    if (rgbProfileTHR) {
        cmsCloseProfile(rgbProfileTHR);
    }
    cmsDeleteContext(contextID);

    // Fuzz cmsCreateRGBProfile
    cmsHPROFILE rgbProfile = cmsCreateRGBProfile(&whitePoint, &primaries, transferFunction);
    if (rgbProfile) {
        cmsCloseProfile(rgbProfile);
    }

    // Fuzz cmsCreateGrayProfile
    cmsHPROFILE grayProfile = cmsCreateGrayProfile(&whitePoint, transferFunction[0]);
    if (grayProfile) {
        cmsCloseProfile(grayProfile);
    }

    // Fuzz cmsCreateGrayProfileTHR
    contextID = cmsCreateContext(nullptr, nullptr);
    cmsHPROFILE grayProfileTHR = cmsCreateGrayProfileTHR(contextID, &whitePoint, transferFunction[0]);
    if (grayProfileTHR) {
        cmsCloseProfile(grayProfileTHR);
    }
    cmsDeleteContext(contextID);

    // Clean up tone curves
    for (int i = 0; i < 3; i++) {
        if (transferFunction[i]) {
            cmsFreeToneCurve(transferFunction[i]);
        }
    }

    return 0;
}
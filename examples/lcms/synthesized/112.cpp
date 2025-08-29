// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsBuildGamma at cmsgamma.c:909:25 in lcms2.h
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateLab2Profile at cmsvirt.c:513:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateRGBProfileTHR at cmsvirt.c:101:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateRGBProfile at cmsvirt.c:217:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateGrayProfile at cmsvirt.c:280:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateGrayProfileTHR at cmsvirt.c:227:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
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
#include <stdint.h>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_112(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY) + sizeof(cmsCIExyYTRIPLE) + 3 * sizeof(cmsToneCurve*)) {
        return 0;
    }

    cmsCIExyY whitePoint;
    memcpy(&whitePoint, Data, sizeof(cmsCIExyY));
    Data += sizeof(cmsCIExyY);
    Size -= sizeof(cmsCIExyY);

    cmsCIExyYTRIPLE primaries;
    memcpy(&primaries, Data, sizeof(cmsCIExyYTRIPLE));
    Data += sizeof(cmsCIExyYTRIPLE);
    Size -= sizeof(cmsCIExyYTRIPLE);

    cmsToneCurve* transferFunction[3];
    for (int i = 0; i < 3; ++i) {
        transferFunction[i] = cmsBuildGamma(nullptr, 2.2);
    }

    cmsContext contextID = cmsCreateContext(nullptr, nullptr);

    cmsHPROFILE labProfile = cmsCreateLab2Profile(&whitePoint);
    if (labProfile) {
        cmsCloseProfile(labProfile);
    }

    cmsHPROFILE rgbProfileTHR = cmsCreateRGBProfileTHR(contextID, &whitePoint, &primaries, transferFunction);
    if (rgbProfileTHR) {
        cmsCloseProfile(rgbProfileTHR);
    }

    cmsHPROFILE rgbProfile = cmsCreateRGBProfile(&whitePoint, &primaries, transferFunction);
    if (rgbProfile) {
        cmsCloseProfile(rgbProfile);
    }

    cmsHPROFILE grayProfile = cmsCreateGrayProfile(&whitePoint, transferFunction[0]);
    if (grayProfile) {
        cmsCloseProfile(grayProfile);
    }

    cmsHPROFILE grayProfileTHR = cmsCreateGrayProfileTHR(contextID, &whitePoint, transferFunction[0]);
    if (grayProfileTHR) {
        cmsCloseProfile(grayProfileTHR);
    }

    for (int i = 0; i < 3; ++i) {
        cmsFreeToneCurve(transferFunction[i]);
    }

    cmsDeleteContext(contextID);

    return 0;
}
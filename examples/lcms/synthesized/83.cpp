// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsCreateLab2ProfileTHR at cmsvirt.c:473:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateLab2Profile at cmsvirt.c:513:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateGrayProfileTHR at cmsvirt.c:227:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateRGBProfileTHR at cmsvirt.c:101:23 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsCreateLab4ProfileTHR at cmsvirt.c:520:23 in lcms2.h
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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY) + sizeof(cmsCIExyYTRIPLE)) {
        return 0;
    }

    cmsContext context = cmsCreateContext(NULL, NULL);
    if (!context) {
        return 0;
    }

    const cmsCIExyY* whitePoint = reinterpret_cast<const cmsCIExyY*>(Data);
    const cmsCIExyYTRIPLE* primaries = reinterpret_cast<const cmsCIExyYTRIPLE*>(Data + sizeof(cmsCIExyY));
    cmsToneCurve* transferFunction[3] = { nullptr, nullptr, nullptr };

    cmsHPROFILE lab2ProfileTHR = cmsCreateLab2ProfileTHR(context, whitePoint);
    if (lab2ProfileTHR) {
        cmsCloseProfile(lab2ProfileTHR);
    }

    cmsHPROFILE lab2Profile = cmsCreateLab2Profile(whitePoint);
    if (lab2Profile) {
        cmsCloseProfile(lab2Profile);
    }

    cmsHPROFILE grayProfileTHR = cmsCreateGrayProfileTHR(context, whitePoint, transferFunction[0]);
    if (grayProfileTHR) {
        cmsCloseProfile(grayProfileTHR);
    }

    cmsHPROFILE rgbProfileTHR = cmsCreateRGBProfileTHR(context, whitePoint, primaries, transferFunction);
    if (rgbProfileTHR) {
        cmsCloseProfile(rgbProfileTHR);
    }

    cmsHPROFILE lab4ProfileTHR = cmsCreateLab4ProfileTHR(context, whitePoint);
    if (lab4ProfileTHR) {
        cmsCloseProfile(lab4ProfileTHR);
    }

    cmsDeleteContext(context);
    return 0;
}
// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsBuildGamma at cmsgamma.c:909:25 in lcms2.h
// cmsCreateRGBProfileTHR at cmsvirt.c:101:23 in lcms2.h
// cmsCreateTransform at cmsxform.c:1348:32 in lcms2.h
// cmsGetTransformContextID at cmsxform.c:1413:22 in lcms2.h
// cmsDeleteTransform at cmsxform.c:147:16 in lcms2.h
// cmsCloseProfile at cmsio0.c:1582:20 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsUnregisterPluginsTHR at cmsplugin.c:780:16 in lcms2.h
// cmsUnregisterPlugins at cmsplugin.c:627:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_162(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsCIExyY) + sizeof(cmsCIExyYTRIPLE)) {
        return 0;
    }

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) {
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

    cmsToneCurve* transferFunction[3] = {nullptr, nullptr, nullptr};
    for (int i = 0; i < 3; ++i) {
        if (Size >= sizeof(cmsToneCurve*)) {
            memcpy(&transferFunction[i], Data, sizeof(cmsToneCurve*));
            Data += sizeof(cmsToneCurve*);
            Size -= sizeof(cmsToneCurve*);
        } else {
            transferFunction[i] = cmsBuildGamma(context, 2.2);
        }
    }

    cmsHPROFILE profile = cmsCreateRGBProfileTHR(context, &whitePoint, &primaries, transferFunction);
    if (profile) {
        cmsHTRANSFORM transform = cmsCreateTransform(profile, TYPE_RGB_8, profile, TYPE_RGB_8, INTENT_PERCEPTUAL, 0);
        if (transform) {
            cmsContext transformContext = cmsGetTransformContextID(transform);
            cmsDeleteTransform(transform);
        }
        cmsCloseProfile(profile);
    }

    for (int i = 0; i < 3; ++i) {
        if (transferFunction[i]) {
            cmsFreeToneCurve(transferFunction[i]);
        }
    }

    cmsUnregisterPluginsTHR(context);
    cmsUnregisterPlugins();
    cmsDeleteContext(context);

    return 0;
}
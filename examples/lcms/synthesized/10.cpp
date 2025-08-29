// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsBuildTabulatedToneCurveFloat at cmsgamma.c:832:25 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsDupToneCurve at cmsgamma.c:968:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsReverseToneCurve at cmsgamma.c:1137:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsEvalToneCurveFloat at cmsgamma.c:1417:28 in lcms2.h
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
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float)) return 0;

    cmsContext context = cmsCreateContext(NULL, NULL);
    if (!context) return 0;

    cmsFloat32Number values[256];
    size_t numEntries = Size / sizeof(float);
    if (numEntries > 256) numEntries = 256;

    for (size_t i = 0; i < numEntries; ++i) {
        values[i] = *reinterpret_cast<const float*>(Data + i * sizeof(float));
    }

    cmsToneCurve* curve = cmsBuildTabulatedToneCurveFloat(context, numEntries, values);
    if (!curve) {
        cmsDeleteContext(context);
        return 0;
    }

    cmsToneCurve* dupCurve = cmsDupToneCurve(curve);
    if (dupCurve) {
        cmsFreeToneCurve(dupCurve);
    }

    cmsToneCurve* reversedCurve = cmsReverseToneCurve(curve);
    if (reversedCurve) {
        cmsFreeToneCurve(reversedCurve);
    }

    for (size_t i = 0; i < numEntries; ++i) {
        cmsEvalToneCurveFloat(curve, values[i]);
    }

    cmsFreeToneCurve(curve);
    cmsDeleteContext(context);

    return 0;
}
// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsGetToneCurveParametricType at cmsgamma.c:1408:27 in lcms2.h
// cmsIsToneCurveLinear at cmsgamma.c:1328:19 in lcms2.h
// cmsGetToneCurveSegment at cmsgamma.c:1506:34 in lcms2.h
// cmsIsToneCurveMonotonic at cmsgamma.c:1346:20 in lcms2.h
// cmsIsToneCurveDescending at cmsgamma.c:1392:20 in lcms2.h
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
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_77(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt16Number) * 256) return 0;

    cmsUInt16Number table[256];
    for (int i = 0; i < 256; ++i) {
        table[i] = reinterpret_cast<const cmsUInt16Number*>(Data)[i];
    }

    cmsToneCurve* curve = cmsBuildTabulatedToneCurve16(nullptr, 256, table);
    if (!curve) return 0;

    cmsGetToneCurveParametricType(curve);
    cmsIsToneCurveLinear(curve);
    cmsGetToneCurveSegment(0, curve);
    cmsIsToneCurveMonotonic(curve);
    cmsIsToneCurveDescending(curve);

    cmsFreeToneCurve(curve);
    return 0;
}
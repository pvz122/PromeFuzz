// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsGetToneCurveParametricType at cmsgamma.c:1408:27 in lcms2.h
// cmsIsToneCurveLinear at cmsgamma.c:1328:19 in lcms2.h
// cmsIsToneCurveMonotonic at cmsgamma.c:1346:20 in lcms2.h
// cmsIsToneCurveMultisegment at cmsgamma.c:1401:20 in lcms2.h
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
#include <stdint.h>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsUInt16Number) * 2) return 0;

    cmsUInt16Number* table = (cmsUInt16Number*) malloc(Size);
    if (!table) return 0;

    memcpy(table, Data, Size);
    size_t tableSize = Size / sizeof(cmsUInt16Number);

    cmsToneCurve* curve = cmsBuildTabulatedToneCurve16(nullptr, tableSize, table);
    if (!curve) {
        free(table);
        return 0;
    }

    cmsGetToneCurveParametricType(curve);
    cmsIsToneCurveLinear(curve);
    cmsIsToneCurveMonotonic(curve);
    cmsIsToneCurveMultisegment(curve);
    cmsIsToneCurveDescending(curve);

    cmsFreeToneCurve(curve);
    free(table);

    return 0;
}
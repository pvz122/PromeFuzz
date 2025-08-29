// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsDeleteContext at cmsplugin.c:963:16 in lcms2.h
// cmsGetToneCurveEstimatedTable at cmsgamma.c:774:34 in lcms2.h
// cmsEvalToneCurve16 at cmsgamma.c:1436:27 in lcms2.h
// cmsReverseToneCurve at cmsgamma.c:1137:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
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

extern "C" int LLVMFuzzerTestOneInput_169(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    cmsUInt32Number nEntries = 256;
    cmsUInt16Number values[256];
    for (size_t i = 0; i < nEntries && i * 2 + 1 < Size; ++i) {
        values[i] = (Data[i * 2] << 8) | Data[i * 2 + 1];
    }

    cmsToneCurve* curve = cmsBuildTabulatedToneCurve16(context, nEntries, values);
    if (!curve) {
        cmsDeleteContext(context);
        return 0;
    }

    const cmsUInt16Number* table = cmsGetToneCurveEstimatedTable(curve);
    if (table) {
        for (size_t i = 0; i < nEntries; ++i) {
            cmsUInt16Number v = table[i];
            cmsEvalToneCurve16(curve, v);
        }
    }

    cmsToneCurve* reversedCurve = cmsReverseToneCurve(curve);
    if (reversedCurve) {
        cmsFreeToneCurve(reversedCurve);
    }

    cmsToneCurve* curveTriple[3] = {curve, nullptr, nullptr};
    cmsFreeToneCurveTriple(curveTriple);

    cmsDeleteContext(context);
    return 0;
}
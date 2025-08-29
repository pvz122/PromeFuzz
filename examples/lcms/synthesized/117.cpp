// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsCreateContext at cmsplugin.c:824:22 in lcms2.h
// cmsBuildTabulatedToneCurveFloat at cmsgamma.c:832:25 in lcms2.h
// cmsGetToneCurveEstimatedTableEntries at cmsgamma.c:768:27 in lcms2.h
// cmsReverseToneCurveEx at cmsgamma.c:1070:25 in lcms2.h
// cmsJoinToneCurve at cmsgamma.c:980:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsBuildSegmentedToneCurve at cmsgamma.c:797:25 in lcms2.h
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
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_117(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat32Number)) return 0;

    cmsContext context = cmsCreateContext(nullptr, nullptr);
    if (!context) return 0;

    // Fuzz cmsBuildTabulatedToneCurveFloat
    cmsUInt32Number nEntries = Size / sizeof(cmsFloat32Number);
    const cmsFloat32Number* values = reinterpret_cast<const cmsFloat32Number*>(Data);
    cmsToneCurve* curve = cmsBuildTabulatedToneCurveFloat(context, nEntries, values);
    if (curve) {
        // Fuzz cmsGetToneCurveEstimatedTableEntries
        cmsUInt32Number entries = cmsGetToneCurveEstimatedTableEntries(curve);

        // Fuzz cmsReverseToneCurveEx
        cmsToneCurve* reversedCurve = cmsReverseToneCurveEx(entries, curve);
        if (reversedCurve) {
            // Fuzz cmsJoinToneCurve
            cmsToneCurve* joinedCurve = cmsJoinToneCurve(context, curve, reversedCurve, entries);
            if (joinedCurve) {
                cmsFreeToneCurve(joinedCurve);
            }
            cmsFreeToneCurve(reversedCurve);
        }
        cmsFreeToneCurve(curve);
    }

    // Fuzz cmsBuildSegmentedToneCurve
    cmsCurveSegment segments[1];
    segments[0].Type = 1;
    segments[0].Params[0] = 1.0;
    cmsToneCurve* segmentedCurve = cmsBuildSegmentedToneCurve(context, 1, segments);
    if (segmentedCurve) {
        cmsFreeToneCurve(segmentedCurve);
    }

    cmsDeleteContext(context);
    return 0;
}
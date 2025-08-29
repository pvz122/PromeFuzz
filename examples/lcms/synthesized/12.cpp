// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// cmsBuildTabulatedToneCurve16 at cmsgamma.c:783:25 in lcms2.h
// cmsReverseToneCurve at cmsgamma.c:1137:25 in lcms2.h
// cmsDupToneCurve at cmsgamma.c:968:25 in lcms2.h
// cmsJoinToneCurve at cmsgamma.c:980:25 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsFreeToneCurve at cmsgamma.c:916:16 in lcms2.h
// cmsDupToneCurve at cmsgamma.c:968:25 in lcms2.h
// cmsDupToneCurve at cmsgamma.c:968:25 in lcms2.h
// cmsDupToneCurve at cmsgamma.c:968:25 in lcms2.h
// cmsFreeToneCurveTriple at cmsgamma.c:954:16 in lcms2.h
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
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Create a dummy tone curve
    cmsUInt16Number table[256];
    for (int i = 0; i < 256; i++) {
        table[i] = (Data[i % Size] << 8) | Data[(i + 1) % Size];
    }
    cmsToneCurve* curve = cmsBuildTabulatedToneCurve16(NULL, 256, table);
    if (!curve) return 0;

    // Test cmsReverseToneCurve
    cmsToneCurve* reversedCurve = cmsReverseToneCurve(curve);
    if (reversedCurve) {
        // Test cmsDupToneCurve
        cmsToneCurve* dupCurve = cmsDupToneCurve(reversedCurve);
        if (dupCurve) {
            // Test cmsJoinToneCurve
            cmsToneCurve* joinedCurve = cmsJoinToneCurve(NULL, curve, reversedCurve, 256);
            if (joinedCurve) {
                cmsFreeToneCurve(joinedCurve);
            }
            cmsFreeToneCurve(dupCurve);
        }
        cmsFreeToneCurve(reversedCurve);
    }

    // Test cmsFreeToneCurveTriple
    cmsToneCurve* triple[3] = {cmsDupToneCurve(curve), cmsDupToneCurve(curve), cmsDupToneCurve(curve)};
    cmsFreeToneCurveTriple(triple);

    // Cleanup
    cmsFreeToneCurve(curve);

    return 0;
}